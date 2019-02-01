#include <services/service_manager.h>
void ServiceManager::registerService(IService *srv) {
    registeredServices.push_back(srv);
}
