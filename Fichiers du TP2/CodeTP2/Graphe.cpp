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
 * \fn Graphe::Graphe(size_t p_nbSommets):nbSommets(p_nbSommets)
 * \param p_nbSommets nombre de sommet du graph
 */
Graphe::Graphe(size_t p_nbSommets) : nbSommets(p_nbSommets), nbArcs(0)
{
	sommets.resize(nbSommets);
	listesAdj.resize(nbSommets);
}
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
 * \fn Graphe::~Graphe()
 * destructeur du graph
 */
Graphe::~Graphe()
{
}
/**
 * \fn void Graphe::resize(size_t nouvelleTaille)
 * \param nouvelleTaille nouvelle taille du graph
 * change la taille du graph, il est supposer que le graph est vide, aucune validation est faite
 * afin de s'assurer de cela
 */
void Graphe::resize(size_t nouvelleTaille)
{

	nbSommets = nouvelleTaille;
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
		listesAdj[source].push_back(new_arc);
		nbArcs++;
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
			nbArcs--;
		}
		else
		{
			throw std::logic_error("L'arc n'existe pas");
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

		const bool exist = (refArch != std::end(listesAdj[source]) ||
							(refArch == std::end(listesAdj[source]) &&
							 (refArch->destination == destination)));
		return exist;
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
		vecteur_return.reserve(nbSommets);
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
/**
 * \fn std::string Graphe::getNomSommet(size_t sommet) const
 * \param sommet index du sommet sujet
 * retourne le nom du sommet
 */
std::string Graphe::getNomSommet(size_t sommet) const
{
	if (noeudExiste(sommet))
	{
		return sommets[sommet];
	}
	throw std::logic_error("le sommet n'existe pas");
}

/**
 * \fn size_t Graphe::getNumeroSommet(const std::string &nom) const
 * \param nom nom du noeud recherche, retourne le premier noeud ayant ce nom
 */
size_t Graphe::getNumeroSommet(const std::string &nom) const
{
	for (size_t i = 0; i < nbSommets; ++i)
	{
		if (sommets[i] == nom)
		{
			return i;
		}
	}
	throw std::logic_error("le sommet n'existe pas");
}
/**
 * \fn int Graphe::getNombreSommets() const
 * retourne le nombre de sommet
 */
int Graphe::getNombreSommets() const
{
	return nbSommets;
}
/**
 * \fn int Graphe::getNombreArcs() const
 * retourne le nombre d'arcs
 */
int Graphe::getNombreArcs() const
{
	return nbArcs;
}

/**
 * \fn Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const
 * \param source sommet sujet
 * \param destination sommet destionation
 * retourne la ponderation d'un noeud adjacent
 */
Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const
{
	if (noeudExiste(source))
	{
		auto refArch = std::find_if(std::begin(listesAdj[source]), std::end(listesAdj[source]),
									[&](const Arc &el) -> bool { return el.destination == destination; });
		return refArch->poids;
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
/**
 * \fn 	bool isEqual( Ponderations poid1, Ponderations poid2)
 * \param poid1 premiere ponderation
 * \param poid2 deuxieme ponderation
 * verifie si 2 ponderation sont egal
 */
bool Graphe::isEqual(Ponderations poid1, Ponderations poid2) const
{
	return poid1.cout == poid2.cout && poid1.duree == poid2.duree && poid1.ns == poid2.ns;
}

} // namespace TP2
