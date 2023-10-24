add_executable(local_merge3d local_merge3d.cpp)
add_dependencies(local_merge3d cisTEM_core)

target_link_libraries(local_merge3d cisTEM_core)

install(TARGETS local_merge3d
        RUNTIME DESTINATION bin)