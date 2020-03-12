/**
* \file Graphe.cpp
* \brief Implémentation d'un graphe orienté.
* \author Étudiant(e)
* \version 0.1
* \date mars 2020
*
*  Travail pratique numéro 2
*
*/

#include "Graphe.h"

//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2
{
/**
 * \fn void Graphe::noeudExiste(size_t sommet) const
 * \param sommet index du noeud sujet
 * verifie si le sommet existe
*/
bool Graphe::noeudExiste(size_t sommet) const
{
	if (nbSommets <= sommet)
	{
		return false;
	}
	return true;
}
/**
 * \fn Graphe::Graphe(size_t p_nbSommets):nbSommets(p_nbSommets)
 * \param p_nbSommets nombre de sommet du graph
 */
Graphe::Graphe(size_t p_nbSommets) : nbSommets(p_nbSommets)
{
	sommets.resize(nbSommets * 2);
	listesAdj.resize(nbSommets * 2);
}
/**
 * \fn Graphe::~Graphe()
 * destructeur du graph
 */
Graphe::~Graphe()
{
}
/**
 * \fn void Graphe::resize(size_t nouvelleTaille)
 * \param nouvelleTaille nouvelle taille du graph
 * change la taille du graph seulement si celui-ci est vide
 */
void Graphe::resize(size_t nouvelleTaille)
{
	if (nbSommets == 0)
	{
		nbSommets = nouvelleTaille;
	}
}
/**
 * \fn void Graphe::nommer(size_t sommet, const std::string &nom)
 * \param nom nom du sommet
 * donne un nom a un sommet d'apres sont index dans le vecteur des sommet.
 * renome le sommet si celui-ci est deja nommee
 */
void Graphe::nommer(size_t sommet, const std::string &nom)
{
	if (noeudExiste(sommet))
	{
		sommets[sommet] = nom;
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
/**
 * \fn void Graphe::ajouterArc(size_t source, size_t destination, float duree, float cout, int ns)
 * \param source index du noeud sujet
 * \param destination index du noeud destination
 * \param duree duree du vol
 * \param cout cout du trajet en dollars
 * \param niveau de securite du vol
 * ajoute un arc entre deux noeud en y attributant une ponderation
 */
void Graphe::ajouterArc(size_t source, size_t destination, float duree, float cout, int ns)
{
	if (noeudExiste(source) && noeudExiste(destination))
	{
		if (arcExiste(source, destination))
		{
			throw std::logic_error("L'arc fourni existe déjà");
		}
		Ponderations new_pond = Ponderations(duree, cout, ns);
		Arc new_arc = Arc(destination, new_pond);

		listesAdj[source].push_back[new_arc];
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
/**
 * \fn void Graphe::enleverArc(size_t source, size_t destination)
 * \param source index du noeud sujet
 * \param destination index du noeud destination
 * retire l'arc entre deux noeud
 */
void Graphe::enleverArc(size_t source, size_t destination)
{
	if (noeudExiste(source) && noeudExiste(destination))
	{
		if (arcExiste(source, destination))
		{
			listesAdj[source].remove_if([&](Arc arc) { return arc.destination == destination; });
		}
		else
		{
			throw std::logic_error("L'arc fourni existe déjà");
		}
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
/**
 * \fn bool Graphe::arcExiste(size_t source, size_t destination) const
 * \param source index du noeud sujet
 * \param destionation index de la destination
 */
bool Graphe::arcExiste(size_t source, size_t destination) const
{
	if (noeudExiste(source) && noeudExiste(destination))
	{

		auto refArch = std::find_if(std::begin(listesAdj[source]), std::end(listesAdj[source]),
									[&](const Arc &el) -> bool { return el.destination == destination; });
		// refArch n'as pas ete trouve et le dernier element n'a pas la bonne destionation
		return !(refArch == std::end(listesAdj[source]) && refArch->destination != destination);
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
/**
 * \fn std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const
 * \param sommet sommet sujet
 * retourne les indexs des sommet adjacent
 */
std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const
{
	if (noeudExiste(sommet))
	{
		std::vector<size_t> vecteur_return;
		for (auto noeud : listesAdj[sommet])
		{
			vecteur_return.push_back(noeud.destination);
		}
		return vecteur_return;
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
// Retourne le nom d'un sommet
// Exception logic_error si sommet supérieur à nbSommets
std::string Graphe::getNomSommet(size_t sommet) const
{

	return sommets[sommet];
}

// Retourne le numéro d'un sommet
// Exception logic_error si nom n'existe pas dans le graphe
size_t Graphe::getNumeroSommet(const std::string &nom) const
{
	for (size_t i = 0; i < nbSommets; ++i)
	{
		if (sommets[i] == nom)
		{
			return i;
		}
	}
}

// Retourne le nombre de sommet du graphe
int Graphe::getNombreSommets() const
{
	return nbSommets;
}

// Retourne le nombre des arcs du graphe
int Graphe::getNombreArcs() const
{
	return nbArcs;
}

// Retourne les pondérations se trouvant dans un arc (source -> destination)
// Exception logic_error si source ou destination supérieur à nbSommets
Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const
{
	if (nbSommets <= source)
	{
		throw std::logic_error("index du sommet invalide");
	}
	const std::list<Arc> &liste = listesAdj[source];

	for (auto it = liste.begin(); it != liste.end(); ++it)
	{
		if (it->destination == destination)
		{
			return it->poids;
		}
	}
}
} // namespace TP2
