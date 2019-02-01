#ifndef SHIROIENGINE_SERVICE_MANAGER_H
#define SHIROIENGINE_SERVICE_MANAGER_H

#include <services/service.h>
#include <services/builtin/embed_shapes.h>

class ServiceManager {
private:
    std::vector<IService *> registeredServices;
public:
    ServiceManager() {
        registeredServices.push_back(new EmbedShapes());
    };

    template<typename T>
    T *getService();

    void registerService(IService *service);
};


template<typename T>
T *ServiceManager::getService() {
    for (auto i : registeredServices) {
        auto found = dynamic_cast<T *>(i);
        if (found != nullptr) {
            return found;
        }
    }

    return nullptr;
}

#endif
