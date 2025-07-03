# GUI模块库
# 确保所有QObject派生类都启用了moc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(GUI_SOURCES
    UserWindow.cpp
    StaffWindow.cpp
    LoginWindow.cpp
)

add_library(GuiModule ${GUI_SOURCES})

target_include_directories(GuiModule PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/gui
)
# 明确列出需要moc处理的头文件
qt_wrap_cpp(GUI_MOC_HDRS
    LoginWindow.h
    UserWindow.h
    StaffWindow.h
)

target_link_libraries(GuiModule PRIVATE
    CoreModule
    PickupModule
    StaffModule
    Qt6::Widgets
    Qt6::Gui
)