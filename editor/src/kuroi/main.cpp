
#include <application/application.h>
#include <kuroi/ui/editor_service.h>
int main() {
    Application editorApplication("KuroiEditor");
    auto srvc = new kuroi::EditorService(&editorApplication);
    auto toolbar = Dock((ContentHost *) &srvc->getWindowHost(), DockingDirection::Up, 32.0F);
    editorApplication.getServiceManager()->registerService(srvc);
    editorApplication.run();
}