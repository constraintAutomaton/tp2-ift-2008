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
 * \brief constructeur du reseau aerien
 * \param[in] nomReseau nom du reseau
 * \param[in] nbVilles nombre de ville
 */
ReseauAerien::ReseauAerien(std::string nomReseau, size_t nbVilles) : unReseau(Graphe(nbVilles)), nomReseau(nomReseau)
{
}
/**
 * \fn ReseauAerien::~ReseauAerien()
 * \brief destructeur de la classe ReseauAerien
 */
ReseauAerien::~ReseauAerien()
{
}
/**
 * \fn void ReseauAerien::resize(size_t nouvelleTaille)
 * \brief change la taille du reseau. Il est supposé que celui-ci est vide
 * \param[in] nouvelleTaille nouvelle taille du réseau aérien
 * 
 */
void ReseauAerien::resize(size_t nouvelleTaille)
{
    unReseau.resize(nouvelleTaille);
}
/**
 * \fn  float ReseauAerien::relachement(float ponderationSource,float ponderationTrajet,float ponderationDestination) const
 * \brief execute un relachement sur un arc donné
 * \param[in] ponderationSource ponderation du noeud source
 * \param[in] ponderationTrajet ponderation de l'arc du trajet 
 * \param[in] ponderationDestination ponderation de la destination
 */
float ReseauAerien::relachement(float ponderationSource, float ponderationTrajet, float ponderationDestination) const
{
    return ponderationSource + ponderationTrajet < ponderationDestination ? ponderationSource + ponderationTrajet : ponderationDestination;
}
/**
 * \fn Chemin ReseauAerien::rechercheCheminBellManFord(const std::string &origine, const std::string &destination, int dureeCoutNiveau) const
 * \brief retourne le plus cours chemin a l'aide de l'algorithme de BellManFord, selon un critère définie par dureeCoutNiveau \n
 *  si sa valeur est de 1 on utilise la duree du vol, 2 le cout du vol et 3 le niveau de sécurité
 * \param[in] origine nom du noeud d'origine
 * \param[in] destination nom du noeud de destination
 * \param[in] dureeCoutNiveau parametre du chemin le plus cours
 * 
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
 * \brief retourne le plus cours chemin avec l'algorithme de dijkstra, si dureeCout est "vrai" la ponderation
 * est sur la "duree" sinon sur le "cout"
 * \param[in] origine nom du noeud d'origine
 * \param[in] destination nom du noeud de destination
 * \param[in] dureeCout indique la metric du plus court chemin
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
 * \brief initialise un vecteur "t" d'index correspondant aux sommets de réseau aérien pour l'algorithme de dijsktra
 * \param[in] taille taille t correspondant à la taille du ReseauAerien
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
 * \brief retourn l'index à partir duquel nous allons analyser le prochain chemin.
 * \param[in] t vecteur t de dijsktra contenant les sommets non analysés du réseau
 * \param[in] y vecteur contenant les valeur des noeuds à la suite de l'application de l'algorithme plus cours chemin sur le noeud en question
 */
size_t ReseauAerien::miseAjourTDijkstra(std::vector<size_t> &t, const std::vector<std::pair<size_t, float>> &y) const
{
    // afin d'eviter une erreur de segmentation quand on erase le dernier element
    if (t.size() == 1)
    {
        const size_t returnedValue = t.at(0);
        t.erase(t.end() - 1);
        return returnedValue;
    }
    std::tuple<size_t, float, std::vector<size_t>::const_iterator> min =
        std::make_tuple(std::numeric_limits<size_t>::infinity(),
                        std::numeric_limits<float>::infinity(), t.begin());
    // on cherche le plus petit y qui n'as pas ete traite
    for (size_t i = 0; i < y.size(); i++)
    {
        auto elementTrouve = std::find(t.begin(), t.end(), i);
        // on regarde si le sommet n'a pas ete analyser
        if (elementTrouve != t.end())
        {
            if (y.at(i).second < std::get<1>(min))
            {
                std::get<1>(min) = y.at(i).second;
                std::get<0>(min) = i;
                std::get<2>(min) = elementTrouve;
            }
        }
    }
    // si toutes les ponderations sont égles
    if (std::get<1>(min) == std::numeric_limits<float>::infinity())
    {
        const size_t returnedValue = t.at(0);
        t.erase(t.begin());
        return returnedValue;
    }
    t.erase(std::get<2>(min));
    return std::get<0>(min);
}
/**
 * \fn Chemin ReseauAerien::dijkstra(const std::string &origine, const std::string &destination, AttributPonderations attribut) const
 * \brief exécute l'algorithme de dijkstra selon l'attribut spécifié en paramètre
 * \param[in] origine nom du noeud d'origine
 * \param[in] destination nom du noeud de destination
 * \param[in] attribut
 * \return le chemin du trajet du vol des villes correspondantes après application de l'algorithme de dijkstra
 */
Chemin ReseauAerien::dijkstra(const std::string &origine, const std::string &destination, AttributPonderations attribut) const
{

    const size_t index_source = unReseau.getNumeroSommet(origine);
    // ponderation des sommet
    std::vector<std::pair<size_t, float>> y(unReseau.getNombreSommets(), std::make_pair(std::numeric_limits<size_t>::infinity(), std::numeric_limits<float>::infinity()));
    // met la valeur de la source a 0
    y.at(index_source).second = 0;
    // noeud a traite
    std::vector<size_t> t = intialiseTDijkstra(y.size());
    // on applique le relachement sur tous les arc dans l'ordre du plus petit y dans le vecteur t
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
 * \brief exécute l'algorithme de bellmanFord selon l'attribut spécifié
 * \param[in] origine nom du noeud d'origine
 * \param[in] destination nom du noeud de destination
 * \param[in] attribut
 * \return le chemin du trajet du vol des villes correspondantes après application de l'algorithme de bellman ford
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
    // on applique un relachement sur tous les arcs tant que les iterations sont instable ou qu'on a fais n+1 iteration
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
 * \brief crée un chemin à partir des résultat des différents relachements.Définit la ville  rajouter  partir du vecteur y qui contient les prédécesseurs de chaque noeud.
 * \param[in] y valeur des noeuds à la suite de l'application de l'algorithme du plus court chemin
 * \param[in] indexOrigin index de la source
 * \param[in] indexDestination index de la destination
 * \param[in] stable indique si l'algorithme a été stable après application de l'algorithme
 * \return un Chemin correspondant aux différentes villes du trajet
 */
Chemin ReseauAerien::makeChemin(const std::vector<std::pair<size_t, float>> &y, size_t indexOrigin, size_t indexDestination, bool stable) const
{
    Chemin chemin = initialiseChemin(y.size());
    chemin.reussi = stable;

    size_t origineCourante = indexDestination;
    if (y.at(indexDestination).second==std::numeric_limits<float>::infinity())
    {
        chemin.reussi = false;
        return chemin;
    }

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
            chemin.reussi = false;
            return chemin;
        }
    }
    chemin.listeVilles.push_back(unReseau.getNomSommet(indexOrigin));
    // on a procede a reculon, donc on inverse la le vecteur
    std::reverse(std::begin(chemin.listeVilles), std::end(chemin.listeVilles));
    return chemin;
}
/**
 * \fn void ReseauAerien::ajoutUneVilleAunChemin(Chemin &chemin, const Ponderations &ponderation, const std::string &ville) const
 * \brief met à jour un chemin à partir d'une ville (nom de la ville) et d'une ponderation (celle avec laquelle nous exécutons l'algorithme)
 * \param[in] chemin chemin sujet
 * \param[in] ponderation à ajouter au chemin
 * \param[in] ville ville à ajouter chemin
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
 * \brief retourne un chemin initialisé
 * \param[in] tailleListeVide taille du chemin
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
 * \brief modifie la valeur du vecteur y à l'aide d'un relachement pour une itération \n 
 * Retourne true si l'itération est stable (utilisable uniquement pour l'algorithme de Bellmanford)
 * \param[in] source index du sommet source
 * \param[in] arrive index du sommet d'arrivee
 * \param[in] y ponderation ainsi que successeur
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
 * \brief Charge un réseau à partir des données contenues dans un fichier texte
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
