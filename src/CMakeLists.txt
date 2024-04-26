set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_executable(
    md
    main.cpp
    particle.cpp
    integrate.cpp
)