add_executable(reconstruct3d reconstruct3d.cpp)
add_dependencies(reconstruct3d cisTEM_core)

target_link_libraries(reconstruct3d cisTEM_core)

install(TARGETS reconstruct3d
        RUNTIME DESTINATION bin)