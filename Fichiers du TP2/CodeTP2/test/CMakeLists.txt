add_executable(test_graphe test_graphe.cpp)
add_test(test_graphe test_graphe)
target_link_libraries(test_graphe ${GTEST_LIBRARIES})

add_executable(test_reseauaerien test_reseauaerien.cpp)
add_test(test_reseauaerien test_reseauaerien)
target_link_libraries(test_reseauaerien ${GTEST_LIBRARIES})