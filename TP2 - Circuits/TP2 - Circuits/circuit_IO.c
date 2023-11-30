/************************************************************************************************************************************************************************************/
/*  Fichier : CRICUIT_IO.C																						                                                                */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <28 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circuit_IO.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
//Fonction: CIRCUIT_IO_SAUVEGARDER
void circuit_IO_sauvegarder(const char* test_circuit, const  t_circuit* circuit)
{
	//Transformer les composantes du circuits en format textuel.
	//Tansformer en textes les composantes de t_entree.
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_serialiser(circuit->entrees[i], &test_circuit);
	}

	//Tansformer en textes les composantes de t_sortie.
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], &test_circuit);
	}

	//Tansformer en textes les composantes de t_porte.
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], &test_circuit);
	}

	FILE *fecrire = fopen("test_circuit.txt", "w");  //ouverture du fichier 
	//fprintf(fecrire, "%s\n", chaine);      //dans le fichier avec le ‘\n’
}

/*==========================================================*/
//Fonction: CIRCUIT_IO_CHARGER
void  circuit_IO_charger(const char* chemin_acces, t_circuit* circuit)
{

}