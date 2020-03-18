
#include <gtest/gtest.h>
#include "Graphe.h"

using namespace std;
using namespace TP2;
class Studs : public ::testing::Test
{
protected:
    size_t nb_sommet_graph_vide = 5;

    size_t source1 = 1;
    size_t destination1 = 4;
    float duree1 = 2.1;
    float cout1 = 3.2;
    float ns1 = 2;

    size_t source2 = 1;
    size_t destination2 = 2;
    float duree2 = 2.1;
    float cout2 = 3.2;
    float ns2 = 2;

    Graphe *graphVide;
    Graphe *graph_1_Arc;
    Graphe *graphe_2_Arc;

    virtual void SetUp()
    {
        graphVide = new Graphe(nb_sommet_graph_vide);

        graph_1_Arc = new Graphe(nb_sommet_graph_vide);
        graph_1_Arc->ajouterArc(source1, destination1, duree1, cout1, ns1);

        graphe_2_Arc = new Graphe(nb_sommet_graph_vide);
        graphe_2_Arc->ajouterArc(source1, destination1, duree1, cout1, ns1);
        graphe_2_Arc->ajouterArc(source2, destination2, duree2, cout2, ns2);
    }
    virtual void TearDown()
    {
        graphVide = nullptr;
        delete graphVide;

        graph_1_Arc = nullptr;
        delete graph_1_Arc;

        graphe_2_Arc = nullptr;
        delete graphe_2_Arc;
    }
};
class Studs2 : public ::testing::Test
{
protected:
    size_t nb_sommet_graph = 11;

    size_t source1 = 1;
    size_t destination1 = 2;
    float duree1 = 1.1;
    float cout1 = 1.1;
    float ns1 = -1;

    size_t source2 = 2;
    size_t destination2 = 4;
    float duree2 = 2.2;
    float cout2 = 2.2;
    float ns2 = 2;

    size_t source3 = 3;
    size_t destination3 = 6;
    float duree3 = 3.3;
    float cout3 = 3.3;
    float ns3 = 3;

    size_t source4 = 4;
    size_t destination4 = 8;
    float duree4 = 4.4;
    float cout4 = 4.4;
    float ns4 = -4;

    size_t source5 = 5;
    size_t destination5 = 9;
    float duree5 = 5.5;
    float cout5 = 5.5;
    float ns5 = 5;

    Graphe *graph_0_Arc;
    Graphe *graph_1_Arc;
    Graphe *graph_2_Arc;
    Graphe *graph_n_Arc;

    virtual void SetUp()
    {
        graph_0_Arc = new Graphe(nb_sommet_graph);

        graph_1_Arc = new Graphe(nb_sommet_graph);
        graph_1_Arc->ajouterArc(source1, destination1, duree1, cout1, ns1);
        graph_1_Arc->ajouterArc(source2, destination2, duree2, cout2, ns2);

        graph_2_Arc = new Graphe(nb_sommet_graph);
        graph_2_Arc->ajouterArc(source1, destination1, duree1, cout1, ns1);
        graph_2_Arc->ajouterArc(source2, destination2, duree2, cout2, ns2);

        graph_n_Arc = new Graphe(nb_sommet_graph);
        graph_n_Arc->ajouterArc(source1, destination1, duree1, cout1, ns1);
        graph_n_Arc->ajouterArc(source2, destination2, duree2, cout2, ns2);
        graph_n_Arc->ajouterArc(source3, destination3, duree3, cout3, ns3);
        graph_n_Arc->ajouterArc(source4, destination4, duree4, cout4, ns4);
    }
    virtual void TearDown()
    {
        graph_0_Arc = nullptr;
        delete graph_0_Arc;

        graph_1_Arc = nullptr;
        delete graph_1_Arc;

        graph_2_Arc = nullptr;
        delete graph_2_Arc;

        graph_n_Arc = nullptr;
        delete graph_n_Arc;
    }
};
TEST_F(Studs, GivenNothingWhenConstructingAGraphThenItShouldHave0ArcAndTheSameNumberOfSommetAsConstructed)
{
    ASSERT_EQ(graphVide->getNombreSommets(), nb_sommet_graph_vide);
    ASSERT_EQ(graphVide->getNombreArcs(), 0);
}
TEST_F(Studs, GivenAGraphWhenResizingItShouldHaveTheSameNumberOfSommetAsResized)
{
    const size_t nouvelle_taille = 1;
    graphVide->resize(nouvelle_taille);
    ASSERT_EQ(graphVide->getNombreSommets(), nouvelle_taille);
}

TEST_F(Studs, GivenAGraphWhenNommerASommetThenTheSommetShouldHaveTheGivenName)
{
    const string nom = "FOO";
    const size_t index_noeud = 0;
    graphVide->nommer(index_noeud, nom);
    ASSERT_EQ(graphVide->getNomSommet(index_noeud), nom);
}
TEST_F(Studs, GivenAGraphWhenAjouterArcOnTheSourceItSelfThisArcShouldExistWithTheRightParameter)
{
    const size_t source = 1;
    const size_t destination = source;
    const float duree = 1.1;
    const float cout = 1.1;
    const int ns = 1;

    graphVide->ajouterArc(source, destination, duree, cout, ns);

    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).duree, duree);
    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).coutt, cout);
    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).ns, ns);
}
TEST_F(Studs, GivenAGraphWhenAjouterArcThisArcShouldExistWithTheRightParameter)
{
    const size_t source = 1;
    const size_t destination = 2;
    const float duree = 1.1;
    const float cout = 1.1;
    const int ns = 1;

    graphVide->ajouterArc(source, destination, duree, cout, ns);

    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).duree, duree);
    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).coutt, cout);
    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).ns, ns);

    ASSERT_EQ(graphVide->arcExiste(source, destination), true);
}
TEST_F(Studs, GivenAGraphWithAnArcWhenEnleverAnArchThenArcShouldBeRemove)
{
    graph_1_Arc->enleverArc(source1, destination1);

    ASSERT_EQ(graph_1_Arc->getNombreArcs(), 0);
    ASSERT_FALSE(graph_1_Arc->arcExiste(source1, destination1));
}
TEST_F(Studs, GivenAGraphWithTwoArcWhenEnleverAnArchThenArcShouldBeRemove)
{
    graphe_2_Arc->enleverArc(source2, destination2);

    ASSERT_EQ(graphe_2_Arc->getNombreArcs(), 1);
    ASSERT_FALSE(graphe_2_Arc->arcExiste(source2, destination2));
    ASSERT_TRUE(graphe_2_Arc->arcExiste(source1, destination1));
}
TEST_F(Studs, GivenAGraphWithANArcWhenEnleverAnArchThatDoesntExistThenItShouldThrowError)
{

    const size_t source_sujet = 1;
    const size_t destionation_sujet = 1;
    ASSERT_THROW(graph_1_Arc->enleverArc(source_sujet, destionation_sujet), logic_error);
    ASSERT_EQ(graph_1_Arc->getNombreArcs(), 1);
}
TEST_F(Studs, GivenAGraphWithANArcWhenEnleverAnArchOutOfIndexThenItShouldThrowError)
{
    const size_t source = nb_sommet_graph_vide + 100;
    const size_t destionation = nb_sommet_graph_vide + 10;
    ASSERT_THROW(graph_1_Arc->enleverArc(source, destionation), logic_error);
    ASSERT_EQ(graph_1_Arc->getNombreArcs(), 1);
}

TEST_F(Studs2, ArcExisteInGraph)
{
    ASSERT_FALSE(graph_0_Arc->arcExiste(source1, destination1));

    ASSERT_TRUE(graph_1_Arc->arcExiste(source1, destination1));

    ASSERT_TRUE(graph_1_Arc->arcExiste(source1, destination1));
    ASSERT_TRUE(graph_2_Arc->arcExiste(source2, destination2));

    ASSERT_TRUE(graph_n_Arc->arcExiste(source1, destination1));
    ASSERT_TRUE(graph_n_Arc->arcExiste(source2, destination2));
    ASSERT_TRUE(graph_n_Arc->arcExiste(source3, destination3));
}

TEST_F(Studs2, ArcExisteNotInGraph)
{
    ASSERT_FALSE(graph_1_Arc->arcExiste(source3, destination3));
    ASSERT_FALSE(graph_2_Arc->arcExiste(source3, destination3));
    ASSERT_FALSE(graph_2_Arc->arcExiste(source4, destination4));
    ASSERT_FALSE(graph_n_Arc->arcExiste(source5, destination5));

    ASSERT_FALSE(graph_2_Arc->arcExiste(source3, destination3));
    ASSERT_FALSE(graph_2_Arc->arcExiste(source4, destination4));
    ASSERT_FALSE(graph_n_Arc->arcExiste(source5, destination5));

    ASSERT_FALSE(graph_n_Arc->arcExiste(source5, destination5));
}

TEST_F(Studs2, ArcExistOutOfIndex)
{
    size_t source_test = 12;
    size_t destination_test = 15;

    ASSERT_THROW(graph_1_Arc->arcExiste(source_test, destination_test), logic_error);

    ASSERT_THROW(graph_2_Arc->arcExiste(source_test, destination_test), logic_error);

    ASSERT_THROW(graph_n_Arc->arcExiste(source_test, destination_test), logic_error);
}

TEST_F(Studs2, Studs2_listerSommetsAdjacents_Test)
{
    std::vector<size_t> vecteur_test;
    size_t sommet_test_1 = 1;
    size_t sommet_test_2 = 2;
    vecteur_test.push_back(sommet_test_2);

    ASSERT_EQ(graph_1_Arc->listerSommetsAdjacents(sommet_test_1), vecteur_test);
}

TEST_F(Studs2, Studs2_getNomSommet_Test)

{
    graph_1_Arc->nommer(0, "Test_1");
    graph_1_Arc->nommer(1, "Test_2");
    graph_1_Arc->nommer(2, "Test_3");
    graph_1_Arc->nommer(3, "Test_4");
    ASSERT_EQ(graph_1_Arc->getNomSommet(0), "Test_1");
    ASSERT_EQ(graph_1_Arc->getNomSommet(1), "Test_2");
    ASSERT_EQ(graph_1_Arc->getNomSommet(2), "Test_3");
    ASSERT_EQ(graph_1_Arc->getNomSommet(3), "Test_4");
}

TEST_F(Studs2, Studs2_getNumeroSommet_Test)
{
    graph_2_Arc->nommer(0, "Test_1");
    graph_2_Arc->nommer(1, "Test_2");
    graph_2_Arc->nommer(2, "Test_3");
    graph_2_Arc->nommer(3, "Test_4");
    ASSERT_EQ(graph_2_Arc->getNumeroSommet("Test_1"), 0);
    ASSERT_EQ(graph_2_Arc->getNumeroSommet("Test_2"), 1);
    ASSERT_EQ(graph_2_Arc->getNumeroSommet("Test_3"), 2);
    ASSERT_EQ(graph_2_Arc->getNumeroSommet("Test_4"), 3);
}

TEST_F(Studs2, Studs2_getNombreSommets_TEST)
{
    ASSERT_EQ(graph_0_Arc->getNombreSommets(), nb_sommet_graph);
    ASSERT_EQ(graph_1_Arc->getNombreSommets(), nb_sommet_graph);
    ASSERT_EQ(graph_2_Arc->getNombreSommets(), nb_sommet_graph);
    ASSERT_EQ(graph_n_Arc->getNombreSommets(), nb_sommet_graph);
}

TEST_F(Studs2, Studs2_getNombreArcs_TEST)
{
    size_t arc_test_1 = 0;
    size_t arc_test_2 = 2;
    size_t arc_test_3 = 2;
    size_t arc_test_4 = 4;
    ASSERT_EQ(graph_0_Arc->getNombreArcs(), arc_test_1);
    ASSERT_EQ(graph_1_Arc->getNombreArcs(), arc_test_2);
    ASSERT_EQ(graph_2_Arc->getNombreArcs(), arc_test_3);
    ASSERT_EQ(graph_n_Arc->getNombreArcs(), arc_test_4);
}