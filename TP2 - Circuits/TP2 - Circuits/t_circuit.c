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

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
//Fonction: T_CIRCUIT_INIT
t_circuit* t_circuit_init(void)
{
	int i;

	t_circuit* nouv_circuit;

	nouv_circuit = (t_circuit*)malloc(sizeof(t_circuit));

	nouv_circuit->nb_entrees = NULL;
	nouv_circuit->nb_sorties = NULL;
	nouv_circuit->nb_portes = NULL;

	for (i = 0; i < MAX_ENTREES; i++)
	{
		nouv_circuit->entrees[i] = NULL;
	}

	for (i = 0; i < MAX_SORTIES; i++)
	{
		nouv_circuit->sorties[i] = NULL;
	}

	for (i = 0; i < CIRCUIT_MAX_PORTES; i++)
	{
		nouv_circuit->portes[i] = NULL;
	}

	return	nouv_circuit;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_DESTROY
void t_circuit_destroy(t_circuit* circuit)
{
	free(circuit->entrees);
	free(circuit->sorties);
	free(circuit->portes);

	free(circuit);
}

/*==========================================================*/
//Fonction: T_CIRCUIT_AJOUTER_PORTE
t_porte* t_circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{
	/*
Fonction: T_CIRCUIT_AJOUTER_PORTE
Description: Crée une nouvelle porte et l'ajoute au circuit.
NDE: Il faut s'assurer qu'on ne dépasse pas le nombre de portes permis (CIRCUIT_MAX_PORTES).

Paramètres:
- circuit: Pointeur vers le circuit auquel la porte sera ajoutée
- type: Type de la porte créée parmi les types de portes prédéfinis (e_type_porte, voir t_porte.h)
Retour: Pointeur vers la nouvelle porte créée s'il a été possible de la créer. NULL sinon.
*/

	//1. Je m'assure que le nombre de portes n'est ne dépasse pas le nombre permis

	if (circuit->nb_portes > CIRCUIT_MAX_PORTES)
	{
		//je crée la nouvelle porte en appelant la fonction qui initialise t_porte

		circuit->portes[circuit->nb_portes] = t_porte_init(id,le_type,*nom);
		circuit->nb_portes++;

		return circuit->portes[circuit->nb_portes-1]; //Retourne Vrai si le lien a bien ete ajoute. //pas certaine de ça
	}

	return NULL; //Retourne Faux si le lien n'a pas ete ajoute.
}
	

/*==========================================================*/
//Fonction: T_CIRCUIT_AJOUTER_ENTREE
t_entree* t_circuit_ajouter_entree(t_circuit* circuit, int id, char* nom)
{
/*Fonction: T_CIRCUIT_AJOUTER_ENTREE
Description : Crée une nouvelle entrée de circuit et l'ajoute au circuit.
NDE : Il faut s'assurer qu'on ne dépasse pas le nombre d'entrées permis (MAX_ENTREES).

Paramètres :
	-circuit : Pointeur vers le circuit auquel l'entrée sera ajoutée
	Retour : Pointeur vers l'entrée créée s'il a été possible de la créer.NULL sinon.*/

	if (circuit->nb_entrees > MAX_ENTREES)
	{
		//je crée la nouvelle porte en appelant la fonction qui initialise t_porte

		circuit->entrees[circuit->nb_entrees] = t_entree_init(id, *nom);
		circuit->nb_entrees++;

		return circuit->entrees[circuit->nb_entrees - 1]; //Retourne Vrai si le lien a bien ete ajoute. //pas certaine de ça
	}

	return NULL; //Retourne Faux si le lien n'a pas ete ajoute.
}

/*==========================================================*/
//Fonction: T_CIRCUIT_AJOUTER_SORTIE
t_sortie* t_circuit_ajouter_sortie(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_sorties > MAX_ENTREES)
	{
		//je crée la nouvelle porte en appelant la fonction qui initialise t_porte

		circuit-> sorties[circuit->nb_sorties] = t_sortie_init(id, *nom);
		circuit->nb_sorties++;

		return circuit->sorties[circuit->nb_sorties - 1]; //Retourne Vrai si le lien a bien ete ajoute. //pas certaine de ça
	}

	return NULL; //Retourne Faux si le lien n'a pas ete ajoute.
}


/*==========================================================*/
//Fonction: T_CIRCUITEST_VALIDE
int t_circuit_est_valide(t_circuit* circuit)
{
	/*
Fonction: T_CIRCUIT_EST_VALIDE
Description: Vérifie si un circuit donné est un circuit valide. Pour qu'un circuit soit valide
			 toutes les entrées, portes et sorties du circuit doivent être reliées.
NDE: Vous utiliserez les fonctions t_entree_est_reliee, t_sortie_est_reliee et t_porte_est_reliee.

Paramètres:
- circuit: Pointeur vers le circuit dont on veut vérifier la validité
Retour: (Booléen) Vrai si le circuit est valide, faux sinon.
*/
	//appel des 3 fonctions 
	int valideentree = t_entree_est_reliee(circuit->entrees);
	int validesortie = t_sortie_est_reliee(circuit->sorties);
	int valideporte = t_porte_est_reliee(circuit->portes);

	if (valideentree && validesortie && valideporte == 1)
	{
		return 1;
	}
	return 0;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_APPLIQUER_SIGNAL
int t_circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{
	int i;

	if (nb_bits == circuit->nb_entrees)
	{
		//On change la valeur du pin de sortie de l'entrée 
		for (i = 0; i < circuit->nb_entrees; i++)
		{
			circuit->entrees[i] = signal[i];
			signal[i]++;
		}
		return 1;
	}
	return 0;
}

/*==========================================================*/
//Fonction: T_CIRCUIT_RESET
void t_circuit_reset(t_circuit* circuit)
{
	free(t_entree_reset);
	free(t_sortie_reset); 
	free(t_porte_reset);
	free(circuit);

}

/*==========================================================*/
//Fonction: T_CIRCUIT_PROPAGER_SIGNAL
int t_circuit_propager_signal(t_circuit* circuit)
{
	//à completer 

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
	return circuit->portes[pos];
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
	return circuit->sorties[pos];
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
	return circuit->entrees[pos];
}
