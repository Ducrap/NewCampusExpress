# 取件模块库（您负责的部分）
add_library(PickupModule STATIC
    PickupQueue.cpp
    PickupScheduler.cpp
    PickupService.cpp
)

target_include_directories(PickupModule PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/pickup
)

target_link_libraries(PickupModule PRIVATE
    CoreModule
    Qt6::Core
    Qt6::Concurrent
)