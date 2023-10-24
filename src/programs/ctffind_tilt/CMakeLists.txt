add_executable(ctffind_tilt ctffind_tilt.cpp)
add_dependencies(ctffind_tilt cisTEM_core)

target_link_libraries(ctffind_tilt cisTEM_core)

install(TARGETS ctffind_tilt
        RUNTIME DESTINATION bin)
