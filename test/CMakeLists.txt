
add_executable(
    test_interaction 
    test_Lennard_Jones.cpp
)

target_link_libraries(test_interaction
  GTest::gtest_main
  )

include(GoogleTest)

add_test(Lennard_Jones test_interaction)