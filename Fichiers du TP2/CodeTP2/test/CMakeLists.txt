add_executable(test_graphe test_graphe.cpp)
add_test(test_graphe test_graphe)
target_link_libraries(test_graphe  ${GTEST_LIBRARIES} graphe)
