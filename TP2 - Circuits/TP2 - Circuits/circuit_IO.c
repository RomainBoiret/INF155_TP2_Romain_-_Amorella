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

#define TAILLE 100

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
//Fonction: CIRCUIT_IO_SAUVEGARDER
void circuit_IO_sauvegarder(const char* nom_fichier, const  t_circuit* circuit)
{
	FILE* fsortie = fopen(nom_fichier, "a");  //ouverture du fichier 

	char ecrire[TAILLE];
	int infocopied = 0;

	infocopied += sprintf(ecrire, "%d", circuit->nb_entrees);
	infocopied += sprintf(ecrire + infocopied, "%d", circuit->nb_sorties);
	infocopied += sprintf(ecrire + infocopied, "%d", circuit->nb_portes);

	//ecrire le texte dans le fichier.
	fprintf(fsortie, "%s\n", ecrire);

	//Transformer les composantes du circuits en format textuel.
	//Tansformer en textes les composantes de t_entree.
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_serialiser(circuit->entrees[i], &ecrire);
		fprintf(fsortie, "%s", ecrire);
	}

	//Tansformer en textes les composantes de t_sortie.
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], &ecrire);
		fprintf(fsortie, "%s", ecrire);
	}

	//Tansformer en textes les composantes de t_porte.
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], &ecrire);
		fprintf(fsortie, "%s", ecrire);
	}

	fclose(fsortie);
}

/*==========================================================*/
//Fonction: CIRCUIT_IO_CHARGER
void  circuit_IO_charger(const char* chemin_acces, t_circuit* circuit)
{

}