add_library(StaffModule
    StaffService.cpp
    PackageManager.cpp
    UserManager.cpp
)

# 关键添加：设置头文件搜索路径
target_include_directories(StaffModule PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../.. 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/staff
)

target_link_libraries(StaffModule PRIVATE
    CoreModule
    Qt6::Core
)