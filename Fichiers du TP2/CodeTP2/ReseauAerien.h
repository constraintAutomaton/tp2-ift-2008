/**
 * \file ReseauAerien.h
 * \brief Gestion d'un réseau aérien.
 * \author IFT-2008
 * \version 0.1
 * \date mars 2020
 *
 *  Travail pratique numéro 2
 *
 */

#include "Graphe.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>
#include <vector>
#include <map>
#include <utility>
#include <queue>

#ifndef _RESEAUAERIEN__H
#define _RESEAUAERIEN__H

namespace TP2
{
/**
 * \struct Chemin
 * \brief Une struture utilisée pour définir le trajet d'un vol
 */
struct Chemin
{
	//listeVilles doit contenir la liste des villes formant le chemin
	//Le point de départ du chemin correspond à l'élément d'indice 0 du vecteur
	//le point d'arrivée correspond au dernier élément du vecteur.
	std::vector<std::string> listeVilles;

	float dureeTotale; // Durée totale du vol du chemin en heures incluant le temps d'escale
	float coutTotal;   // Cout total en dollars du chemin entre la ville de départ et la ville de destination
	int nsTotal;	   // Niveau de sécurité total du chemin
	bool reussi;	   // Un booléen qui vaut true si chemin a été trouvé, false sinon
};
/**
 * \class ReseauAerien
 * \brief Classe représentant un reseau aérien
 */
class ReseauAerien
{

public:
	// Constructeur
	ReseauAerien(std::string nomReseau, size_t nbVilles = 5);

	// Destructeur
	~ReseauAerien();

	// Change la taille du réseau en utilisant un nombre de villes = nouvelleTaille
	void resize(size_t nouvelleTaille);

	//Surcharge de l'opérateur de sortie.
	//Ne touchez pas à cette fonction !
	friend std::ostream &operator<<(std::ostream &out, const ReseauAerien &g)
	{
		out << g.unReseau << std::endl;
		return out;
	}

	// Charger un réseau à partir d'un fichier texte en entrée (voir format du fichier dans l'énoncé du Tp).
	// Construit un réseau routier à partir d'une liste de villes ainsi que leurs liens.
	// fichierEntree est ouvert corectement.
	// fichierEntree n'est pas fermé par la fonction.
	// Exception logic_error si fichierEntree n'est pas ouvert correctement.
	void chargerReseau(std::ifstream &fichierEntree);

	// Retourne le plus court chemin selon l'algorithme de Dijkstra
	// origine et destination font partie du graphe
	// Exception std::logic_error si origine et/ou destination absent du réseau
	Chemin rechercheCheminDijkstra(const std::string &origine, const std::string &destination, bool dureeCout) const;

	// Retourne le plus court chemin selon l'algorithme Bellman-Ford
	// origine et destination font partie du graphe
	// 1 <= dureeCoutNiveau <= 3
	// Exception std::logic_error si dureeCoutNiveau hors limite
	// Exception std::logic_error si origine et/ou destination absent du réseau
	Chemin rechercheCheminBellManFord(const std::string &origine, const std::string &destination, int dureeCoutNiveau) const;

	//Vous pouvez ajoutez d'autres méthodes publiques si vous sentez leur nécessité

private:
	Graphe unReseau;
	// Le type ReseauAerien est composé d'un graphe
	std::string nomReseau; // Le nom du reseau (exemple: Air Canada)
	float relachement(float ponderationSource, float ponderationTrajet, float ponderationDestination) const;
	Chemin bellManFord(const std::string &origine, const std::string &destination, AttributPonderations attribut) const;
	Chemin dijkstra(const std::string &origine, const std::string &destination, AttributPonderations attribut) const;
	Chemin initialiseChemin(int tailleListeVide) const;
	Chemin makeChemin(const std::vector<std::pair<size_t, float>> &y, size_t indexOrigin, size_t indexDestination, bool stable = true) const;
	bool iterationTrouverPlusCoursChemin(size_t source, size_t arrive, std::vector<std::pair<size_t, float>> &y, AttributPonderations attribut) const;
	void ajoutUneVilleAunChemin(Chemin &chemin, const Ponderations &ponderation, const std::string &ville) const;
	std::vector<size_t> intialiseTDijkstra(size_t taille) const;
	size_t miseAjourTDijkstra(std::vector<size_t> &t, const std::vector<std::pair<size_t, float>> &y) const;
	// Vous pouvez définir des constantes ici.

	//Vous pouvez ajoutez des méthodes privées si vous sentez leur nécessité
};

} // namespace TP2

#endif
