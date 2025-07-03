cmake_minimum_required(VERSION 3.20)
project(CampusExpress LANGUAGES CXX)

# 基础配置
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Qt配置（路径根据实际安装位置调整）
set(QT_DIR "E:/Qt/6.9.1/mingw_64")
set(CMAKE_PREFIX_PATH ${QT_DIR})

# 查找Qt组件
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Sql
    Network
    Concurrent
)

# MySQL配置（路径根据实际安装位置调整）
set(MYSQL_CONNECTOR_DIR "D:/MySQL/MySQL Connector C++ 9.3")
set(MySQL_INCLUDE_DIR "${MYSQL_CONNECTOR_DIR}/include")
set(MySQL_LIBRARY "${MYSQL_CONNECTOR_DIR}/lib64/vs14/mysqlcppconn.lib")

add_library(MySQL::MySQL SHARED IMPORTED)
set_target_properties(MySQL::MySQL PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${MySQL_INCLUDE_DIR}"
    IMPORTED_IMPLIB "${MySQL_LIBRARY}"
    IMPORTED_LOCATION "${MYSQL_CONNECTOR_DIR}/lib64/mysqlcppconn-10-vs14.dll"
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/gui
    ${PROJECT_SOURCE_DIR}/include/staff
    E:/Qt/6.9.1/mingw_64/include
)

# 添加子目录（模块化构建）
add_subdirectory(src/core)
add_subdirectory(src/pickup)  
add_subdirectory(src/staff)   
add_subdirectory(src/gui)

# 主可执行文件
add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
)

# 处理UI和资源文件
qt_wrap_ui(UI_FILES
    src/gui/LoginWindow.ui
    src/gui/UserWindow.ui
    src/gui/StaffWindow.ui
)

qt_add_resources(QRC_FILES
    resources/icons.qrc
    resources/styles.qrc
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    CoreModule
    PickupModule 
    StaffModule   
    GuiModule
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::Concurrent
    MySQL::MySQL
)

# 复制MySQL DLL（Windows平台）
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${MYSQL_CONNECTOR_DIR}/lib64/mysqlcppconn-10-vs14.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/
        COMMENT "Copying MySQL DLL to output directory"
    )
endif()

# 安装目标（可选）
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)