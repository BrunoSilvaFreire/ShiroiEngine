set(UI_ALL
        include/shiroi/ui/panel.h
        include/shiroi/ui/rect.h
        src/shiroi/ui/rect.cpp
        )
AddModule(ui "${UI_ALL}" "core")