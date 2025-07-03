# GUI模块库
add_library(GuiModule STATIC
    LoginWindow.cpp
    UserWindow.cpp
    StaffWindow.cpp
    DialogManager.cpp
)

target_include_directories(GuiModule PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/gui
)

target_link_libraries(GuiModule PRIVATE
    CoreModule
    PickupModule
    StaffModule
    Qt6::Widgets
    Qt6::Gui
)