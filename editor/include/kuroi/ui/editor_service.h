#ifndef SHIROIENGINE_EDITOR_ECOSYSTEM_H
#define SHIROIENGINE_EDITOR_ECOSYSTEM_H
#define GLM_ENABLE_EXPERIMENTAL

#include <services/service.h>
#include <kuroi/ui/dock.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace kuroi {
    class EditorService : public IService {
    private:
        WindowHost windowHost;
        Event<float32>::EventListener listener;
    public:
        static constexpr float32 kOrthoHeight = 5;

        explicit EditorService(Application *app) : windowHost(app) {
            listener = [&](float dt) {
                //Draw stuff
                int width, height;
                glfwGetWindowSize(app->getContext()->getWindow(), &width, &height);
                float32 aspect = (float32) width / height;
                float32 horizontal = kOrthoHeight * aspect;
                glm::mat4 mat = glm::ortho(horizontal, horizontal, kOrthoHeight, kOrthoHeight);
                LOG(INFO) << "Drawing @ " << glm::to_string(mat);
                windowHost.draw(mat);
            };
            app->getMainStepFunction().getLateStep() += &listener;
        }


        const WindowHost &getWindowHost() const {
            return windowHost;
        }
    };
}
#endif
