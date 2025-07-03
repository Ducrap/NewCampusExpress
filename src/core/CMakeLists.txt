# 核心数据结构库
add_library(CoreModule STATIC
    DatabaseConnector.cpp
    AVLTree.cpp
    User.cpp
    Package.cpp
    Config.cpp
)

target_include_directories(CoreModule PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/core
    ${MySQL_INCLUDE_DIR}
)

target_link_libraries(CoreModule PRIVATE
    Qt6::Core
    Qt6::Sql
    MySQL::MySQL
)