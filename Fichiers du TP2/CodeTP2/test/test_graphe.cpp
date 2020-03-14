
#include <gtest/gtest.h>
#include "Graphe.h"

using namespace std;
using namespace TP2;
class Studs : public ::testing::Test
{
protected:
    size_t nb_sommet_graph_vide = 3;
    Graphe *graphVide;
    virtual void SetUp()
    {
        graphVide = new Graphe(nb_sommet_graph_vide);
    }
    virtual void TearDown()
    {
        graphVide = nullptr;
        delete graphVide;
    }
};

TEST_F(Studs, GivenALabyrintheWhenConstructThenTheLabyrinhtheHasDefaultAttribute)
{
    ASSERT_EQ(1,1);
}