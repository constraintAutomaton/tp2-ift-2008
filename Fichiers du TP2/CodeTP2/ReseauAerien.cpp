/**
 * \file ReseauAerien.cpp
 * \brief Implémentattion de la classe ReseauAerien.
 * \author Étudiant(e)
 * \version 0.1
 * \date mars 2020
 *
 *  Travail pratique numéro 2
 *
 */

#include "ReseauAerien.h"
#include <sstream>
#include <fstream>
#include <climits>
//vous pouvez inclure d'autres librairies si c'est nécessaire
 
namespace TP2
{
/**
 * \fn ReseauAerien::ReseauAerien(std::string nomReseau, size_t nbVilles)
 * \param nomReseau nom du reseau
 * \param nbVilles nombre de ville
 * constructeur du reseau aerien
 */
ReseauAerien::ReseauAerien(std::string nomReseau, size_t nbVilles) : unReseau(Graphe(nbVilles)), nomReseau(nomReseau)
{
}
/**
 * \fn ReseauAerien::~ReseauAerien()
 * destructeur de la classe
 */
ReseauAerien::~ReseauAerien()
{
}
/**
 * \fn void ReseauAerien::resize(size_t nouvelleTaille)
 * \param nouvelleTaille
 * change la taille du reseau. il est suppose que celui-ci est vide
 */
void ReseauAerien::resize(size_t nouvelleTaille)
{
    unReseau.resize(nouvelleTaille);
}
/**
 * \fn  float ReseauAerien::relachement(float ponderationSource,float ponderationTrajet,float ponderationDestination) const
 * \param ponderationSource ponderation du noeud source
 * \param ponderationTrajet ponderation du trajet
 * \param ponderationDestination ponderation de la destination
 * execute un relachement sur un arc
 */
float ReseauAerien::relachement(float ponderationSource, float ponderationTrajet, float ponderationDestination) const
{
    return ponderationSource + ponderationTrajet < ponderationDestination ? ponderationSource + ponderationTrajet : ponderationDestination;
}
/**
 * \fn Chemin ReseauAerien::rechercheCheminBellManFord(const std::string &origine, const std::string &destination, int dureeCoutNiveau) const
 * \param origine nom du noeud d'origine
 * \param destination nom du noeud de destination
 * \param dureeCoutNiveau parametre du chemin le plus cours
 * retourne le plus cours chemin a l'aide de l'algorithme de BellManFord, selon une critere qui est definie par dureeCoutNiveau
 * si sa valeur est de 1 on utilise la duree du vol, 2 le cout du vol et 3 le niveau de securite
 */
Chemin ReseauAerien::rechercheCheminBellManFord(const std::string &origine, const std::string &destination, int dureeCoutNiveau) const
{
    switch (dureeCoutNiveau)
    {
    case 1:
        return bellManFord(origine, destination, AttributPonderations::duree);
    case 2:
        return bellManFord(origine, destination, AttributPonderations::coutt);
    case 3:
        return bellManFord(origine, destination, AttributPonderations::ns);
    default:
        throw std::logic_error("type de trajet mal definie");
    }
}
Chemin ReseauAerien::rechercheCheminDijkstra(const std::string &origine, const std::string &destination, bool dureeCout) const
{
    AttributPonderations attribut;
    if(dureeCout)
    {
    attribut = duree;
    }
    else
    {
        attribut= coutt;
    }
    int index_max= unReseau.getNombreSommets(); 
    const size_t index_source = unReseau.getNumeroSommet(origine);
    std::vector<std::pair<size_t, float>> y(unReseau.getNombreSommets(), std::make_pair(std::numeric_limits<size_t>::infinity(), std::numeric_limits<float>::infinity()));
    y.at(index_source).second = 0;
    int k = 1;
    bool connue = true;
    const int n_arc = unReseau.getNombreArcs();
   do
   {
       connue = true;
        for (int sommet = 0; sommet < index_max; sommet++)
        {
            for (auto arrive : unReseau.listerSommetsAdjacents(sommet))
            {
                const float ponderation = unReseau.getPonderationsArc(sommet, arrive).getAttribute(attribut);
                const float valPrecedente = y.at(arrive).second;
                y.at(arrive).second = relachement(y.at(sommet).second, y.at(arrive).second, ponderation);
                if (y.at(arrive).second != valPrecedente)
                {
                    y.at(arrive).first = y.at(sommet).first;
                }
                connue = y.at(arrive).second < (y.at(sommet).second + ponderation);
            }
        }

        k++;
   } while (connue == false && k < n_arc + 1);
   const size_t indexDestination = unReseau.getNumeroSommet(destination);
    return makeChemin(y, index_source, indexDestination, connue);
}
/**
 * \fn Chemin ReseauAerien::bellManFord(const std::string &origine, const std::string &destination, AttributPonderations attribut) const
 * \param origine nom du noeud d'origine
 * \param destination nom du noeud de destination
 * \param attribut
 * execute bellmanFord selon l'attribut specifie
 */
Chemin ReseauAerien::bellManFord(const std::string &origine, const std::string &destination, AttributPonderations attribut) const
{
    const size_t indexSource = unReseau.getNumeroSommet(origine);
    std::vector<std::pair<size_t, float>> y (unReseau.getNombreSommets(), std::make_pair(std::numeric_limits<size_t>::infinity(), std::numeric_limits<float>::infinity()));
    y.at(indexSource).second = 0;
    int k = 1;
    bool stable = true;
    const int n = unReseau.getNombreArcs();
    do
    {
        stable = true;
        for (int sommet = 0; sommet < n; sommet++)
        {
            for (auto arrive : unReseau.listerSommetsAdjacents(sommet))
            {
                const float ponderation = unReseau.getPonderationsArc(sommet, arrive).getAttribute(attribut);
                const float valPrecedente = y.at(arrive).second;
                y.at(arrive).second = relachement(y.at(sommet).second, y.at(arrive).second, ponderation);
                if (y.at(arrive).second != valPrecedente)
                {
                    y.at(arrive).first = y.at(sommet).first;
                }
                stable = y.at(arrive).second < (y.at(sommet).second + ponderation);
            }
        }

        k++;
    } while (stable == false && k < n + 1);
    const size_t indexDestination = unReseau.getNumeroSommet(destination);
    return makeChemin(y, indexSource, indexDestination, stable);
}
/**
 * \fn Chemin ReseauAerien::makeChemin(const std::vector<std::pair<size_t, float>> y, size_t indexOrigin, size_t indexDestination, bool stable) const
 * \param y valeur des noeud a la suite d'un algorithme plus cours chemin
 * \param indexOrigin index de la source
 * \param indexDestination index de la destination
 * \param stable indique si l'algorithme a ete stable
 * cree un chemin a partir des resultat des diferent relachement
 */
Chemin ReseauAerien::makeChemin(const std::vector<std::pair<size_t, float>> y, size_t indexOrigin, size_t indexDestination, bool stable) const
{
    Chemin chemin;
    chemin.listeVilles = {};
    chemin.listeVilles.reserve(y.size());
    chemin.dureeTotale = 0;
    chemin.coutTotal = 0;
    chemin.nsTotal = 0;
    chemin.reussi = stable;

    size_t origineCourante = indexDestination;
    int i = 0;
    while (origineCourante != indexOrigin)
    {
        chemin.listeVilles.push_back(unReseau.getNomSommet(origineCourante));

        const size_t destinationCourante = y[origineCourante].first;
        // on inverse,car on marche a reculons
        const Ponderations ponderation = unReseau.getPonderationsArc(destinationCourante, origineCourante);
        // construction du chemin
        chemin.dureeTotale += ponderation.duree;
        chemin.coutTotal += ponderation.coutt;
        chemin.nsTotal += ponderation.ns;
        //suivant
        origineCourante = y.at(origineCourante).first;
        i++;
        if (i > y.size())
        {
            throw std::logic_error("Il y a eu un probleme inconnue");
        }
    }
    chemin.listeVilles.push_back(unReseau.getNomSommet(indexOrigin));
    std::reverse(std::begin(chemin.listeVilles), std::end(chemin.listeVilles));
    return chemin;
}
// Méthode fournie
/**
 * \fn void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
 * \param[in] le fichier contenant l'information sur le réseau
 */
void ReseauAerien::chargerReseau(std::ifstream &fichierEntree)
{
    if (!fichierEntree.is_open())
        throw std::logic_error("ReseauAerien::chargerReseau: Le fichier n'est pas ouvert !");

    std::string buff;
    getline(fichierEntree, nomReseau);
    nomReseau.erase(0, 15);

    int nbVilles;

    fichierEntree >> nbVilles;
    getline(fichierEntree, buff); //villes

    unReseau.resize(nbVilles);

    getline(fichierEntree, buff); //Liste des villes

    size_t i = 0;

    getline(fichierEntree, buff); //Premiere ville

    while (buff != "Liste des trajets:")
    {
        std::string ville = buff;

        unReseau.nommer(i, ville);

        getline(fichierEntree, buff);
        i++;
    }

    while (!fichierEntree.eof())
    {
        getline(fichierEntree, buff);
        std::string source = buff;

        getline(fichierEntree, buff);
        std::string destination = buff;

        getline(fichierEntree, buff);
        std::istringstream iss(buff);

        float duree;
        iss >> duree;

        float cout;
        iss >> cout;

        int ns;
        iss >> ns;

        unReseau.ajouterArc(unReseau.getNumeroSommet(source), unReseau.getNumeroSommet(destination), duree, cout, ns);
    }
}

//À compléter par l'implémentation des autres méthodes demandées

} // namespace TP2
