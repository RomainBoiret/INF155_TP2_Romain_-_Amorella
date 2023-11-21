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

}

/*==========================================================*/
//Fonction: T_CIRCUIT_AJOUTER_ENTREE
t_entree* t_circuit_ajouter_entree(t_circuit* circuit, int id, char* nom)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_AJOUTER_SORTIE
t_sortie* t_circuit_ajouter_sortie(t_circuit* circuit, int id, char* nom)
{

}

/*==========================================================*/
//Fonction: T_CIRCUITEST_VALIDE
int t_circuit_est_valide(t_circuit* circuit)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_APPLIQUER_SIGNAL
int t_circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_RESET
void t_circuit_reset(t_circuit* circuit)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_PROPAGER_SIGNAL
int t_circuit_propager_signal(t_circuit* circuit)
{

}

/************************** Les ACCESSEURS ************************************/

/*==========================================================*/
//Fonction: T_CIRCUIT_NB_PORTES
int t_circuit_get_nb_portes(const t_circuit* circuit)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_PORTE
t_porte* t_circuit_get_porte(const t_circuit* circuit, int pos)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_NB_SORTIES
int t_circuit_get_nb_sorties(const t_circuit* circuit)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_SORTIES
t_sortie* t_circuit_get_sortie(const t_circuit* circuit, int pos)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_NB_ENTREES
int t_circuit_get_nb_entrees(const t_circuit* circuit)
{

}

/*==========================================================*/
//Fonction: T_CIRCUIT_GET_ENTREE
t_entree* t_circuit_get_entree(const t_circuit* circuit, int pos)
{

}
