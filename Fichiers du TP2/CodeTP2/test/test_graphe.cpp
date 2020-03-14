
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
    Graphe *graphAvecUnArc;
    Graphe *graphAvecDeuxArc;

    virtual void SetUp()
    {
        graphVide = new Graphe(nb_sommet_graph_vide);

        graphAvecUnArc = new Graphe(nb_sommet_graph_vide);
        graphAvecUnArc->ajouterArc(source1, destination1, duree1, cout1, ns1);

        graphAvecDeuxArc = new Graphe(nb_sommet_graph_vide);
        graphAvecDeuxArc->ajouterArc(source1, destination1, duree1, cout1, ns1);
        graphAvecDeuxArc->ajouterArc(source2, destination2, duree2, cout2, ns2);
    }
    virtual void TearDown()
    {
        graphVide = nullptr;
        delete graphVide;

        graphAvecUnArc = nullptr;
        delete graphAvecUnArc;

        graphAvecDeuxArc = nullptr;
        delete graphAvecDeuxArc;
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
    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).cout, cout);
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
    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).cout, cout);
    ASSERT_EQ(graphVide->getPonderationsArc(source, destination).ns, ns);
}
TEST_F(Studs, GivenAGraphWithAnArcWhenEnleverAnArchThenArcShouldBeRemove)
{
    graphAvecUnArc->enleverArc(source1, destination1);

    ASSERT_EQ(graphAvecUnArc->getNombreArcs(), 0);
    ASSERT_FALSE(graphAvecUnArc->arcExiste(source1, destination1));
}
TEST_F(Studs, GivenAGraphWithTwoArcWhenEnleverAnArchThenArcShouldBeRemove)
{
    graphAvecDeuxArc->enleverArc(source2, destination2);

    ASSERT_EQ(graphAvecDeuxArc->getNombreArcs(), 1);
    ASSERT_FALSE(graphAvecDeuxArc->arcExiste(source2, destination2));
    ASSERT_TRUE(graphAvecDeuxArc->arcExiste(source1, destination1));
}
TEST_F(Studs, GivenAGraphWithANArcWhenEnleverAnArchThatDoesntExistThenItShouldThrowError)
{

    const size_t source_sujet = 1;
    const size_t destionation_sujet = 1;
    ASSERT_THROW(graphAvecUnArc->enleverArc(source_sujet, destionation_sujet), logic_error);
    ASSERT_EQ(graphAvecUnArc->getNombreArcs(), 1);
}
TEST_F(Studs, GivenAGraphWithANArcWhenEnleverAnArchOutOfIndexThenItShouldThrowError)
{
    const size_t source = nb_sommet_graph_vide + 100;
    const size_t destionation = nb_sommet_graph_vide + 10;
    ASSERT_THROW(graphAvecUnArc->enleverArc(source, destionation), logic_error);
    ASSERT_EQ(graphAvecUnArc->getNombreArcs(), 1);
}