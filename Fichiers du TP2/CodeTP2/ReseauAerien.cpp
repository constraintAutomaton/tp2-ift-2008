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
#include <algorithm>
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
        return bellManFord(origine, destination, AttributPonderations::attributCout);
    case 3:
        return bellManFord(origine, destination, AttributPonderations::ns);
    default:
        throw std::logic_error("type de trajet mal definie");
    }
}
/**
 * \fn Chemin ReseauAerien::rechercheCheminDijkstra(const std::string &origine, const std::string &destination, bool dureeCout) const
 * \param origine nom du noeud d'origine
 * \param destination nom du noeud de destination
 * \param dureeCout indique la metric du plus court chemin
 * retourne le plus cours chemin avec l'algorithme de dijkstra, si dureeCout est vrai la ponderation
 * est sur la duree sinon sur le cout
 */
Chemin ReseauAerien::rechercheCheminDijkstra(const std::string &origine, const std::string &destination, bool dureeCout) const
{
    if (dureeCout)
    {
        return dijkstra(origine, destination, AttributPonderations::duree);
    }
    else
    {
        return dijkstra(origine, destination, AttributPonderations::attributCout);
    }
}
/**
 * \fn std::vector<size_t> ReseauAerien::intialiseTDijkstra(size_t taille) const
 * \param taille taille de t
 * initialise le vecteur t de dijsktra
 */
std::vector<size_t> ReseauAerien::intialiseTDijkstra(size_t taille) const
{
    std::vector<size_t> t;
    t.reserve(taille);
    for (int i = 0; i < taille; i++)
    {
        t.push_back(i);
    }
    return t;
}
/**
 * \fn void miseAjourTDijkstra(std::vector<size_t> &t, const std::vector<std::pair<size_t, float>> &y) const
 * \param t vecteur t de dijsktra afin de sommet non analyser
 * \param y valeur des noeud a la suite d'un algorithme plus cours chemin
 * retourn le prochain chemin a analyser et enleve ce chemin du vecteur
 */
size_t ReseauAerien::miseAjourTDijkstra(std::vector<size_t> &t, const std::vector<std::pair<size_t, float>> &y) const
{
    if (t.size() == 1)
    {
        const size_t returnedValue = t.at(0);
        t.erase(t.end() - 1);
        return returnedValue;
    }
    std::pair<size_t, float> min = std::make_pair(std::numeric_limits<size_t>::infinity(),
                                                  std::numeric_limits<float>::infinity());
    for (size_t i = 0; i < y.size(); i++)
    {
        // on regarde si le sommet n'a pas ete analyser
        if (std::find(t.begin(), t.end(), i) != t.end())
        {
            if (y.at(i).second < min.second)
            {
                min.second = y.at(i).second;
                min.first = i;
            }
        }
    }
    if (min.first == std::numeric_limits<float>::infinity())
    {
        const size_t returnedValue = t.at(0);
        t.erase(t.begin());
        return returnedValue;
    }
    t.erase(std::find(t.begin(), t.end(), min.first));
    return min.first;
}
/**
 * \fn Chemin ReseauAerien::dijkstra(const std::string &origine, const std::string &destination, AttributPonderations attribut) const
 * \param origine nom du noeud d'origine
 * \param destination nom du noeud de destination
 * \param attribut
 * execute dijkstra selon l'attribut specifie
 */
Chemin ReseauAerien::dijkstra(const std::string &origine, const std::string &destination, AttributPonderations attribut) const
{

    const size_t index_source = unReseau.getNumeroSommet(origine);
    // ponderation des sommet
    std::vector<std::pair<size_t, float>> y(unReseau.getNombreSommets(), std::make_pair(std::numeric_limits<size_t>::infinity(), std::numeric_limits<float>::infinity()));
    // met la valeur de la source a 0
    y.at(index_source).second = 0;
    // nombre d'iteration
    std::vector<size_t> t = intialiseTDijkstra(y.size());
    do
    {
        const size_t sommet = miseAjourTDijkstra(t, y);
        for (auto arrive : unReseau.listerSommetsAdjacents(sommet))
        {
            iterationTrouverPlusCoursChemin(sommet, arrive, y, attribut);
        }
    } while ((!t.empty()));
    const size_t index_destination = unReseau.getNumeroSommet(destination);
    return makeChemin(y, index_source, index_destination);
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
    // ponderation des sommet
    std::vector<std::pair<size_t, float>> y(unReseau.getNombreSommets(), std::make_pair(std::numeric_limits<size_t>::infinity(), std::numeric_limits<float>::infinity()));
    // met la valeur de la source a 0
    y.at(indexSource).second = 0;
    // nombre d'iteration
    int k = 1;
    bool stable = true;
    const int n = unReseau.getNombreSommets();
    do
    {
        stable = true;
        for (int sommet = 0; sommet < n; sommet++)
        {
            for (auto arrive : unReseau.listerSommetsAdjacents(sommet))
            {
                stable = iterationTrouverPlusCoursChemin(sommet, arrive, y, attribut);
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
Chemin ReseauAerien::makeChemin(const std::vector<std::pair<size_t, float>> &y, size_t indexOrigin, size_t indexDestination, bool stable) const
{
    Chemin chemin = initialiseChemin(y.size());
    chemin.reussi = stable;

    size_t origineCourante = indexDestination;
    int i = 0;
    while (origineCourante != indexOrigin)
    {
        const size_t destinationCourante = y.at(origineCourante).first;
        // on inverse,car on marche a reculons
        const Ponderations ponderation = unReseau.getPonderationsArc(destinationCourante, origineCourante);
        // ajoute la ville et ses ponderation au chemin
        ajoutUneVilleAunChemin(chemin, ponderation, unReseau.getNomSommet(origineCourante));
        //suivant
        origineCourante = y.at(origineCourante).first;
        i++;
        if (i > y.size())
        {
            throw std::logic_error("Il y a eu un probleme inconnue");
        }
    }
    chemin.listeVilles.push_back(unReseau.getNomSommet(indexOrigin));
    // on a procede a reculon, donc on inverse la le vecteur
    std::reverse(std::begin(chemin.listeVilles), std::end(chemin.listeVilles));
    return chemin;
}
/**
 * \fn void ReseauAerien::ajoutUneVilleAunChemin(Chemin &chemin, const Ponderations &ponderation, const std::string &ville) const
 * \param chemin chemin sujet
 * \param ponderation a ajouter
 * \param ville ville a ajouter
 * met a jour un chemin a partir d'une ville et une ponderation
 */
void ReseauAerien::ajoutUneVilleAunChemin(Chemin &chemin, const Ponderations &ponderation, const std::string &ville) const
{
    chemin.dureeTotale += ponderation.duree;
    chemin.coutTotal += ponderation.attributCout;
    chemin.nsTotal += ponderation.ns;
    chemin.listeVilles.push_back(ville);
}
/**
 * \fn Chemin ReseauAerien::initialiseChemin() const
 * retourn un chemin vide
 */
Chemin ReseauAerien::initialiseChemin(int tailleListeVide) const
{
    Chemin chemin;
    chemin.listeVilles = {};
    chemin.listeVilles.reserve(tailleListeVide);
    chemin.dureeTotale = 0;
    chemin.coutTotal = 0;
    chemin.nsTotal = 0;
    chemin.reussi = true;
    return chemin;
}
/**
 * \fn void ReseauAerien::iterationTrouverPlusCoursChemin(size_t source, size_t arrivee, std::vector<std::pair<size_t, float>> &y) const;
 * \param source index du sommet source
 * \param arrice index du sommet d'arrivee
 * \param y ponderation ainsi que successeur
 * modifie la valeur de y a l'aide d'un relachement pour une itteration retourne si l'iteration est stable(fait du sens seulement pour Bellmanford)
 */
bool ReseauAerien::iterationTrouverPlusCoursChemin(size_t source, size_t arrive, std::vector<std::pair<size_t, float>> &y, AttributPonderations attribut) const
{
    const float ponderation = unReseau.getPonderationsArc(source, arrive).getAttribute(attribut);
    const float valPrecedente = y.at(arrive).second;
    y.at(arrive).second = relachement(y.at(source).second, ponderation, y.at(arrive).second);
    // on change le predecesseur si le relachement a fait changer une valeur
    if (y.at(arrive).second != valPrecedente)
    {
        y.at(arrive).first = source;
    }
    return !(y.at(arrive).second > (y.at(source).second + ponderation));
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
