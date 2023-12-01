/************************************************************************************************************************************************************************************/
/*  Fichier : T_CIRCUIT.C																						                                                                    */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <14 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "t_circuit.h"
#include "files_portes.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
//Fonction: T_CIRCUIT_INIT
t_circuit* t_circuit_init(void)
{
	t_circuit* nouv_circuit;

	nouv_circuit = (t_circuit*)malloc(sizeof(t_circuit));
	//les trois compteurs sont mis à zéro
	nouv_circuit->nb_entrees = 0;
	nouv_circuit->nb_sorties = 0;
	nouv_circuit->nb_portes = 0;

	for (int i = 0; i < MAX_ENTREES; i++)
	{
		nouv_circuit->entrees[i] = NULL;
	}

	for (int i = 0; i < MAX_SORTIES; i++)
	{
		nouv_circuit->sorties[i] = NULL;
	}

	for (int i = 0; i < CIRCUIT_MAX_PORTES; i++)
	{
		nouv_circuit->portes[i] = NULL;
	}

	return	nouv_circuit;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_DESTROY
void t_circuit_destroy(t_circuit* circuit)
{
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_destroy(circuit->entrees[i]);
	}

	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_destroy(circuit->sorties[i]);
	}

	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_destroy(circuit->portes[i]);
	}

	free(circuit);
}

/*==========================================================*/
//Fonction: T_CIRCUIT_AJOUTER_PORTE
t_porte* t_circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{
	//1. Le nombre de portes ne doit pas dépasser pas le nombre permis
	if (circuit->nb_portes < CIRCUIT_MAX_PORTES)
	{
		//Création de la nouvelle porte avec appel de fonction
		t_porte* nouv_porte = t_porte_init(id, le_type, nom);
		circuit->portes[circuit->nb_portes] = nouv_porte;
		circuit->nb_portes++;

		return nouv_porte; //Retourne Vrai si le lien a bien ete ajoute.
	}

	return NULL; //Retourne NULL si le lien n'a pas ete ajoute.
}

/*==========================================================*/
//Fonction: T_CIRCUIT_AJOUTER_ENTREE
t_entree* t_circuit_ajouter_entree(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_entrees < MAX_ENTREES)
	{
		//Création de la nouvelle entrée si condition vraie 

		t_entree* nouv_entree = t_entree_init(id, nom);
		circuit->entrees[circuit->nb_entrees] = nouv_entree;
		circuit->nb_entrees++;
		//Retourne Vrai si le lien a bien ete ajoute.
		return (nouv_entree);
	}

	return NULL; //Retourne NULL si le lien n'a pas ete ajoute.
}

/*==========================================================*/
//Fonction: T_CIRCUIT_AJOUTER_SORTIE
t_sortie* t_circuit_ajouter_sortie(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_sorties < MAX_SORTIES)
	{
		//Création de la nouvelle sortie si condition vraie
		t_sortie* nouv_sortie = t_sortie_init(id, nom);
		circuit->sorties[circuit->nb_sorties] = nouv_sortie;
		circuit->nb_sorties++;

		return (nouv_sortie);
	}

	return NULL; //Retourne NULL si le lien n'a pas ete ajoute.
}

/*==========================================================*/
//Fonction: T_CIRCUITEST_VALIDE
int t_circuit_est_valide(t_circuit* circuit)
{
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		if (!t_entree_est_reliee(circuit->entrees[i]))
			return FAUX;
	}

	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		if (!t_sortie_est_reliee(circuit->sorties[i]))
			return FAUX;
	}

	for (int i = 0; i < circuit->nb_portes; i++)
	{
		if (!t_porte_est_reliee(circuit->portes[i]))
			return FAUX;
	}

	return VRAI;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_APPLIQUER_SIGNAL
int t_circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{
	if (nb_bits == circuit->nb_entrees)
	{
		//On change la valeur du pin de sortie de l'entrée 
		for (int i = 0; i < circuit->nb_entrees; i++)
		{
			t_pin_sortie_set_valeur(circuit->entrees[i]->pin, signal[i]);
		}

		return VRAI;
	}

	return FAUX;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_RESET
void t_circuit_reset(t_circuit* circuit)
{
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_reset(circuit->entrees[i]);
	}

	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_reset(circuit->sorties[i]);
	}

	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_reset(circuit->portes[i]);
	}
}

/*==========================================================*/
//Fonction: T_CIRCUIT_PROPAGER_SIGNAL
int t_circuit_propager_signal(t_circuit* circuit)
{
	//Initialiser les variables locales.
	t_file nouv_file;	initfile(&nouv_file);	// Une file de portes que l’on doit initialiser.
	t_porte* porte_courante = NULL;				// Un pointeur vers une porte.
	int nb_iterations = 0;						// Un entier initialisé à 0.

	//Vérifier si le circuit est valide.
	if (t_circuit_est_valide(circuit) == FAUX)
		return FAUX;

	//Vérifier si l'entrée est valide.
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		if (t_entree_get_pin(circuit->entrees[i]) == INACTIF)
			return FAUX;
	}

	//Propager le signal de l'entree.
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_propager_signal(circuit->entrees[i]);
	}

	//Ajouter les portes à la file.
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		ajouterfin(&nouv_file, circuit->portes[i]);
	}

	while (!vide(&nouv_file) && nb_iterations < (circuit->nb_portes * (circuit->nb_portes + 1) / 2))
	{
		//Défiler une porte de la file et la stocker dans porte_courante.
		enleverdebut(&nouv_file, &porte_courante);

		int val_propage = t_porte_propager_signal(porte_courante);

		//Si ça ne se propage pas on le range dans la file.
		if (val_propage == FAUX)
		{
			ajouterfin(&nouv_file, porte_courante);
		}

		nb_iterations++;
	}

	//Si la file est vide le signal peut se propager.
	if (vide(&nouv_file))
	{
		return VRAI; //Le signal s’est bien propagé.
	}
	else return FAUX; //Car cela veut dire que notre circuit a une boucle .
}

/************************** Les ACCESSEURS ************************************/

/*==========================================================*/
//Fonction: T_CIRCUIT_NB_PORTES
int t_circuit_get_nb_portes(const t_circuit* circuit)
{
	return circuit->nb_portes;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_PORTE
t_porte* t_circuit_get_porte(const t_circuit* circuit, int pos)
{
	if (pos > INACTIF && pos < CIRCUIT_MAX_PORTES)
	{
		return circuit->sorties[pos];
	}

	else return NULL;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_NB_SORTIES
int t_circuit_get_nb_sorties(const t_circuit* circuit)
{
	return circuit->sorties;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_SORTIES
t_sortie* t_circuit_get_sortie(const t_circuit* circuit, int pos)
{
	if (pos > INACTIF && pos < MAX_SORTIES)
	{
		return circuit->sorties[pos];
	}

	else return NULL;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_NB_ENTREES
int t_circuit_get_nb_entrees(const t_circuit* circuit)
{	
	return circuit->nb_entrees;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_ENTREE
t_entree* t_circuit_get_entree(const t_circuit* circuit, int pos)
{
	if (pos > INACTIF && pos < MAX_ENTREES)
	{
		return circuit->entrees[pos];
	}

	else return NULL;
}
