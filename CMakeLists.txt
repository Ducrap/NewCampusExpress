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

# Qt配置（添加工具路径）
set(QT_DIR "E:/Qt/6.9.1/mingw_64")
set(CMAKE_PREFIX_PATH ${QT_DIR})
set(QT_BIN_DIR "${QT_DIR}/bin")
set(QT_MOC_EXECUTABLE "${QT_BIN_DIR}/moc.exe")
set(QT_UIC_EXECUTABLE "${QT_BIN_DIR}/uic.exe")
set(QT_RCC_EXECUTABLE "${QT_BIN_DIR}/rcc.exe")

# 查找Qt组件
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Sql
    Network
    Concurrent
)

# MySQL配置# 在MySQL配置部分添加完整导入目标定义
set(MYSQL_CONNECTOR_DIR "D:/MySQL/MySQL_Connector_C++_9.3")
set(MySQL_INCLUDE_DIR "${MYSQL_CONNECTOR_DIR}/include/jdbc")
set(MySQL_LIBRARY "${MYSQL_CONNECTOR_DIR}/lib64/vs14/mysqlcppconn.lib")
set(MySQL_DLL "${MYSQL_CONNECTOR_DIR}/lib64/vs14/mysqlcppconn-10-vs14.dll")

# 定义导入目标（完整版本）
add_library(MySQL::MySQL SHARED IMPORTED)
set_target_properties(MySQL::MySQL PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${MySQL_INCLUDE_DIR}"
    IMPORTED_LOCATION "${MySQL_DLL}"
    IMPORTED_IMPLIB "${MySQL_LIBRARY}"
)

# 添加子目录（仅保留一组）
add_subdirectory(src/core)
add_subdirectory(src/pickup)  
add_subdirectory(src/staff)   
add_subdirectory(src/gui)

# 主可执行文件
add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
)

# 处理UI和资源文件（原代码中UI_FILES和QRC_FILES未定义，需修正）
set(UI_FILES
    src/gui/LoginWindow.ui
    src/gui/UserWindow.ui
    src/gui/StaffWindow.ui
)
qt6_wrap_ui(UI_FILES ${UI_FILES})  # 使用qt6_wrap_ui替代qt_wrap_ui

# 添加UI和资源文件到可执行目标
target_sources(${PROJECT_NAME} PRIVATE
    ${UI_FILES}
)

# 设置包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/core
    ${PROJECT_SOURCE_DIR}/include/gui
    ${PROJECT_SOURCE_DIR}/include/staff
    ${QT_DIR}/include
    ${MySQL_INCLUDE_DIR}
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

# 静态链接定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
    CPPCONN_PUBLIC_FUNC=
    STATIC_CONCPP
)

# 复制MySQL DLL
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${MYSQL_CONNECTOR_DIR}/lib64/vs14/mysqlcppconn-10-vs14.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/
        COMMENT "Copying MySQL DLL to output directory"
    )
endif()

# 安装目标
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)
