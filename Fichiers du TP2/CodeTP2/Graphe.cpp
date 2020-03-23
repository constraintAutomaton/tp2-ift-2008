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
 * \brief Constructeur de la classe graphe
 * \param[in] p_nbSommets nombre de sommets du graphe
 */
Graphe::Graphe(size_t p_nbSommets) : nbSommets(p_nbSommets), nbArcs(0)
{
	resize(nbSommets);
}
/**
 * \fn void Graphe::noeudExiste(size_t sommet) const
 * \brief Verifie si le sommet appartient au graphe
 * \param[in] sommet index du noeud (sommet) sujet
 
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
 * \brief destructeur de la classe graphe
 */
Graphe::~Graphe()
{
}
/**
 * \fn void Graphe::resize(size_t nouvelleTaille)
 * \brief Change la taille du graphe, il est supposé que le graphe soit vide, mais aucune vérification n'est faite pour s'en assurer
 * \param[in] nouvelleTaille nouvelle taille du graphe
 */
void Graphe::resize(size_t nouvelleTaille)
{	
	nbSommets = nouvelleTaille;
	sommets.resize(nbSommets);
	listesAdj.resize(nbSommets);
	
}
/**
 * \fn void Graphe::nommer(size_t sommet, const std::string &nom)
 * \brief donne un nom à un sommet d'après sont index dans le vecteur des sommet. Renomme le sommet si celui-ci est deja nommé.
 * \param[in] sommet index du sommet dans le graphe
 * \param[in] nom nom du sommet
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
 * \brief ajoute un arc entre deux noeud en y attributant une ponderation
 * \param[in] source index du sommet sujet
 * \param[in] destination index du noeud destination
 * \param[in] duree duree du vol
 * \param[in] cout cout du trajet en dollars
 * \param[in] ns de securite du vol
 * 
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
		listesAdj.at(source).push_back(new_arc);
		nbArcs++;
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
/**
 * \fn void Graphe::enleverArc(size_t source, size_t destination)
 * \brief  retire un arc entre deux noeud
 * \param[in] source index du noeud sujet
 * \param[in] destination index du noeud destination
 *
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
 * \brief Indique si un arc existe entre deux noeuds
 * \param[in] source index du noeud sujet
 * \param[in] destionation index de la destination
 * \return un booléen qui indique si l'arc existe ou non
 */
bool Graphe::arcExiste(size_t source, size_t destination) const
{
	if (noeudExiste(source) && noeudExiste(destination))
	{

		auto refArch = std::find_if(std::begin(listesAdj[source]), std::end(listesAdj[source]),
									[&](const Arc &el) -> bool { return el.destination == destination; });

		const bool exist = (refArch != std::end(listesAdj[source]));
		return exist;
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
/**
 * \fn std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const
 * \brief retourne les indexs des sommets adjacent au sommet sujet
 * \param[in] sommet sommet sujet 
 * \return les sommets adjacents dans un vecteur <size_t>
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
 * \brief retourne le nom du sommet sujet
 * \param[in] sommet index du sommet sujet
 * \return le nom du sommet correspondant dans un "string"
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
 * \brief retourne l'index du premier noeud ayant ce nom dans le graphe (supposé que deux sommets ont des noms différents)
 * \param[in] nom nom du noeud recherche
 * \return l'index du noeud correspondant au nom fournit en paramètre 
 */
size_t Graphe::getNumeroSommet(const std::string &nom) const
{
	for (size_t i = 0; i < nbSommets; ++i)
	{
		if (sommets.at(i) == nom)
		{
			return i;
		}
	}
	throw std::logic_error("le sommet n'existe pas");
}
/**
 * \fn int Graphe::getNombreSommets() const
 * \brief retourne le nombre de sommets du graphe
 * \return nbSommets l'attribut indiquant le nombre de sommets du graphe
 */
int Graphe::getNombreSommets() const
{
	return nbSommets;
}
/**
 * \fn int Graphe::getNombreArcs() const
 * \brief retourne le nombre d'arcs du graphe
 * \return nbArcs l'attribut indiquant le nombre d'arc du graphe
 */
int Graphe::getNombreArcs() const
{
	return nbArcs;
}

/**
 * \fn std::vector<std::string> Graphe::getSommetsGraphe() const
 * \brief retourne le vecteur de sommets du graphe
 * \return sommets l'attribut contenant les sommets du graphe
 */
std::vector<std::string> Graphe::getSommetsGraphe() const
{
	return sommets;
}
/**
 * \fn Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const
 * \brief retourne la ponderation d'un noeud adjacent
 * \param[in] source sommet sujet
 * \param[in] destination sommet destination
 * \return pondération de l'arc correspondant
 */
Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const
{
	if (noeudExiste(source))
	{
		if (arcExiste(source, destination))
		{
			auto refArch = std::find_if(std::begin(listesAdj[source]), std::end(listesAdj[source]),
										[&](const Arc &el) -> bool { return el.destination == destination; });
			return refArch->poids;
		}
		else
		{
			throw std::logic_error("l'arc n'existe pas");
		}
		
	}
	else
	{
		throw std::logic_error("index du sommet invalide");
	}
}
/**
 * \fn 	bool isEqual( Ponderations poid1, Ponderations poid2)
 * \brief verifie si deux ponderation sont égales ou non
 * \param[in] poid1 premiere ponderation
 * \param[in] poid2 deuxieme ponderation
 * \return un booléen qui indique si les deux pondérations fournit en paramètres sont égales ou non
 */
bool Graphe::isEqual(Ponderations poid1, Ponderations poid2) const
{
	return poid1.attributCout == poid2.attributCout && poid1.duree == poid2.duree && poid1.ns == poid2.ns;
}

} // namespace TP2
