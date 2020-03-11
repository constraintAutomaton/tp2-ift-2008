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
	std::list<Arc>::iterator it = std::find(liste.begin(),liste.end(),destination); // Méthode find à implémenter pour liste d'arcs ?? A revoir 
	if(it==liste.end())
	{
		throw std::logic_error("L'arc fourni existe déjà");
	}

	liste.erase(it);
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
	std::list<Arc> & liste = listesAdj[source];
	std::list<Arc>::iterator it = std::find(liste.begin(),liste.end(),destination); // Même Méthode find à implémenter pour liste d'arcs ?? 

	return it != liste.end();
}
}//Fin du namespace
