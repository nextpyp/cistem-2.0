add_executable(unblur_gain unblur_gain.cpp)
add_dependencies(unblur_gain cisTEM_core)

target_link_libraries(unblur_gain cisTEM_core)

install(TARGETS unblur_gain
        RUNTIME DESTINATION bin)
