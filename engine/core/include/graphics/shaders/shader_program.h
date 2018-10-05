#ifndef SHIROIENGINE_SHADER_PROGRAM_H
#define SHIROIENGINE_SHADER_PROGRAM_H

#include <types.h>
#include <GL/glew.h>
#include <utility/graphic_utilities.h>
#include <fstream>
#include <filesystem>

class ShaderSource {
private:
    std::string src;
public:
    static ShaderSource *fromStream(std::istream &stream) {
        std::ostringstream result;
        int8 currentByte;
        while (stream.get(currentByte)) {
            result << currentByte;
        }
        return new ShaderSource(result);
    }

    explicit ShaderSource(std::ostringstream &stream) : src(stream.str()) {}

    std::string getSource() const {
        return src;
    }
};

class ShaderProgram : public IGLBindable {
private:
    uint32 programID;

    static bool tryUploadShader(uint32 programId, uint32 shaderType, ShaderSource *source, uint32 *const resultId) {
        uint32 shaderId = glCreateShader(shaderType);
        auto str = source->getSource();
        auto src = str.c_str();
        if (str.length() <= 0) {
            LOG(ERROR) << "Shader source is empty!";
            return false;
        }
        glCall(glShaderSource(shaderId, 1, &src, nullptr));
        glCall(glCompileShader(shaderId));
        auto status = checkCompileStatus(shaderId);
        if (!status) {
            showCompileError(shaderId);
            glCall(glDeleteShader(shaderId));
            shaderId = 0;
        } else {
            glCall(glAttachShader(programId, shaderId));
        }
        *resultId = shaderId;
        return status;
    }

    static bool tryUploadShaders(
            uint32 programId,
            ShaderSource *vertexSource, uint32 *const vertexId,
            ShaderSource *fragmentSource, uint32 *const fragmentId
    ) {
        return tryUploadShader(programId, GL_VERTEX_SHADER, vertexSource, vertexId) &&
               tryUploadShader(programId, GL_FRAGMENT_SHADER, fragmentSource, fragmentId);
    }

    static bool checkCompileStatus(uint32 id) {
        int result;
        glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        return result == GL_TRUE;
    }

    static void showCompileError(uint32 id) {
        int32 length;
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        if (length <= 0) {
            LOG(ERROR) << "Error while compiling shader @ " << id << ", no message given";
        } else {
            char *message = new char[length];
            glCall(glGetShaderInfoLog(id, length, &length, message));
            LOG(ERROR) << "Error while compiling shader @ " << id << ": \"" << message << "\"";
            delete[] message;
        }
    }

public:
    static constexpr string kDefaultVertexName = "/stdvertex.vs";
    static constexpr string kDefaultFragmentName = "/stdfragment.fs";

    inline static ShaderProgram *fromStreams(std::istream &fragmentShader, std::istream &vertexShader) {
        ShaderSource *fragmentSource;
        ShaderSource *vertexSource;
        fragmentSource = ShaderSource::fromStream(fragmentShader);
        vertexSource = ShaderSource::fromStream(vertexShader);
        auto program = new ShaderProgram(fragmentSource, vertexSource);
        delete fragmentSource, delete vertexSource;
        return program;

    }

    static ShaderProgram *defaultProgram(string const path) {
        std::string fragmentPath = path;
        std::string vertexPath = path;
        fragmentPath += kDefaultFragmentName;
        vertexPath += kDefaultVertexName;
        auto fPath = std::filesystem::absolute(fragmentPath);
        auto vPath = std::filesystem::absolute(vertexPath);
        LOG(INFO) << "Using default shaders: Fragment: '" << fPath << "', Vertex: '" << vPath << "'";
        std::ifstream fStream(fPath);
        std::ifstream vStream(vPath);
        if (!fStream.good()) {
            throw std::runtime_error("Couldn't find default fragment shader @ " + fPath.string());
        }
        if (!vStream.good()) {
            throw std::runtime_error("Couldn't find default vertex shader @ " + vPath.string());
        }
        return ShaderProgram::fromStreams(fStream, vStream);
    }

    ShaderProgram(ShaderSource *fragment, ShaderSource *vertex) {
        programID = glCreateProgram();
        uint32 fragmentShaderID, vertexShaderID;
        if (!tryUploadShaders(programID, vertex, &vertexShaderID, fragment, &fragmentShaderID)) {
            glCall(glDeleteProgram(programID));
            throw std::runtime_error("Shader compilation failed!");
        }
        glCall(glLinkProgram(programID));
        int32 result;
        glCall(glGetProgramiv(programID, GL_LINK_STATUS, &result));
        if (result == GL_FALSE) {
            int32 length;
            glCall(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length));
            if (length <= 0) {
                LOG(ERROR) << "Error while linking program @ " << programID << ", no message given";
            } else {
                char *linkError = new char[length];
                glCall(glGetProgramInfoLog(programID, length, &length, linkError));
                LOG(ERROR) << "Error while linking program @ " << programID << ": \"" << linkError << "\"";
                delete[] linkError;
                glCall(glDeleteProgram(programID));
                throw std::runtime_error("Program linking failed!");
            }


        }
        glCall(glValidateProgram(programID));
        glCall(glDeleteShader(fragmentShaderID));
        glCall(glDeleteShader(vertexShaderID));
    }

    ~ShaderProgram() {
        glCall(glDeleteProgram(programID));
    }

    void bind() override {
        if (glIsProgram(programID) != GL_TRUE) {
            LOG(ERROR) << "Attempted to bing invalid program @ " << programID;
            return;
        }
        glCall(glUseProgram(programID));
    }

    void unbind() override {
        glCall(glUseProgram(0))
    }
};


#endif