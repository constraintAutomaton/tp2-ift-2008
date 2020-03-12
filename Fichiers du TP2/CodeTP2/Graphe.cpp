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

Graphe::Graphe(size_t p_nbSommets):nbSommets(p_nbSommets)
{
	sommets.resize(nbSommets);
	listesAdj.resize(nbSommets);
}
Graphe::~Graphe()
{

}

void Graphe::resize(size_t nouvelleTaille)
{
	if ( nbSommets == 0)
	{
		nbSommets = nouvelleTaille;
	}
	return;
}

void Graphe::nommer(size_t sommet, const std::string& nom)
{
	if(nbSommets <= sommet)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}
	sommets[sommet]=nom;
		
	
}

void Graphe::ajouterArc(size_t source, size_t destination, float duree, float cout, int ns)
{
	if( nbSommets <= source)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}

	if( nbSommets <= destination)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}

	if(arcExiste(source,destination))
	{
		throw std::logic_error("L'arc fourni existe déjà");
	}
	Ponderations *new_pond=new Ponderations(duree,cout,ns);
	Arc *new_arc=new Arc(destination,*new_pond);

	listesAdj[source].push_back[*new_arc];
}
void Graphe::enleverArc(size_t source, size_t destination)
{
	if( nbSommets <= source)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}

	if( nbSommets <= destination)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}
		if(arcExiste(source,destination))
	{
		throw std::logic_error("L'arc fourni existe déjà");
	}
	std::list<Arc> & liste = listesAdj[source];
	//std::list<Arc>::iterator it ;//=std::find(liste.begin(),liste.end(),it->destination); // Méthode find à implémenter pour liste d'arcs ?? A revoir 
	
	
		for(auto it=liste.begin();it == liste.end();++it)
		{
			if(it->destination == destination)
			{
				liste.erase(it);
			}
			if(it==liste.end())
			{
				throw std::logic_error("L'arc fourni est inexistant");
			}
		}

}

bool Graphe::arcExiste(size_t source, size_t destination) const
{
		if( nbSommets <= source)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}

	if( nbSommets <= destination)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}
	const std::list<Arc> & liste  = listesAdj[source];

for(auto it=liste.begin();it != liste.end();++it)
{
	if(it->destination == destination)
			{
				return true;
			}
}
	return false;

	//std::list<Arc>::iterator it = std::find(liste.begin(),liste.end(),destination); // Même Méthode find à implémenter pour liste d'arcs ?? 

}

std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const
{
		if( nbSommets <= sommet)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}
	std::vector<size_t> vecteur_return;
	for(std::list<Arc>::const_iterator it=listesAdj[sommet].begin();it !=listesAdj[sommet].end();++it)
	{
		vecteur_return.push_back(it->destination);
	}
	return vecteur_return;
}
	// Retourne le nom d'un sommet
	// Exception logic_error si sommet supérieur à nbSommets
	std::string Graphe::getNomSommet(size_t sommet) const
	{
		
			return sommets[sommet];
	}

	// Retourne le numéro d'un sommet
	// Exception logic_error si nom n'existe pas dans le graphe
	size_t Graphe::getNumeroSommet(const std::string& nom) const
	{
		for (size_t i = 0; i < nbSommets; ++i)
		{
			if (sommets[i]==nom)
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
		if( nbSommets <= source)
	{
		throw std::logic_error("Nombre de sommets fournis invalides");
	}
		const std::list<Arc> & liste  = listesAdj[source];

for(auto it=liste.begin();it != liste.end();++it)
{
	if(it->destination == destination)
			{
				return it->poids;
				
			}
}
	}
}//Fin du namespace
