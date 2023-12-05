/************************************************************************************************************************************************************************************/
/*  Fichier : CRICUIT_IO.C																						                                                                    */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <28 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "circuit_IO.h"

#define TAILLE 100

/***************************************************************************************/
/*                         DECLARATION DES FONCTIONS PRIVEES                           */
/***************************************************************************************/

//Pour la fonction CIRCUIT_IO_SAUVEGARDER.
static void ecrire_entrees(const char* nom_fichier, int nb_entrees, const  t_circuit* circuit);
static void ecrire_sorties(const char* nom_fichier, int nb_sorties, const  t_circuit* circuit);
static void ecrire_portes(const char* nom_fichier, int nb_portes, const  t_circuit* circuit);
static void ecrire_liens(const char* nom_fichier, const  t_circuit* circuit);

//Pour la fonction CIRCUIT_IO_CHARGER.
static void lire_entrees(const char* nom_fichier, int nb_entrees, const  t_circuit* circuit);
static void lire_sorties(const char* nom_fichier, int nb_sorties, const  t_circuit* circuit);
static void lire_portes(const char* nom_fichier, int nb_portes, const  t_circuit* circuit);
static void lire_liens(const char* nom_fichier, const  t_circuit* circuit);

/***************************************************************************************/
/*                         DEFINITION DES FONCTIONS PRIVEES                            */
/***************************************************************************************/

/*==========================================================*/
//Fonction: ECRIRE_ENTREES
static void ecrire_entrees(FILE* nom_fichier, int nb_entrees, const  t_circuit* circuit)
{
	char ecrire[TAILLE];
#
	for (int i = 0; i < nb_entrees; i++)
	{
		t_entree_serialiser(circuit->entrees[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
	}
}

/*==========================================================*/
//Fonction: ECRIRE_SORTIES
static void ecrire_sorties(FILE* nom_fichier, int nb_sorties, const  t_circuit* circuit)
{
	char ecrire[TAILLE];

	for (int i = 0; i < nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
	}
}

/*==========================================================*/
//Fonction: ECRIRE_PORTES
static void ecrire_portes(FILE* nom_fichier, int nb_portes, const  t_circuit* circuit)
{
	char ecrire[TAILLE];

	for (int i = 0; i < nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
	}
}

/*==========================================================*/
//Fonction: ECRIRE_LIENS
static void ecrire_liens(FILE* nom_fichier, const  t_circuit* circuit)
{
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		fprintf(nom_fichier, "%s ", circuit->portes[i]->nom);

		for (int j = 0; j < circuit->portes[i]->nb_entrees; j++)
		{
			if (circuit->portes[i]->entrees[j]->nom_liaison == NULL)
			{
				fprintf(nom_fichier, "%s ", "XX");
			}
			else
			{
				fprintf(nom_fichier, "%s ", circuit->portes[i]->entrees[j]->nom_liaison);
			}
		}

		fprintf(nom_fichier, "%c", '\n');
	}

	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		fprintf(nom_fichier, "%s ", circuit->sorties[i]->nom);

		fprintf(nom_fichier, "%s ", circuit->sorties[i]->pin->nom_liaison);

		fprintf(nom_fichier, "%c", '\n');
	}
}

/*==========================================================*/
//Fonction: LIRE_ENTREES
static void lire_entrees(FILE* nom_fichier, int nb_entrees, const  t_circuit* circuit)
{

}

/*==========================================================*/
//Fonction: LIRE_SORTIES
static void lire_sorties(FILE* nom_fichier, int nb_sorties, const  t_circuit* circuit)
{

}

/*==========================================================*/
//Fonction: LIRE_PORTES
static void lire_portes(FILE* nom_fichier, int nb_portes, const  t_circuit* circuit)
{

}

/*==========================================================*/
//Fonction: LIRE_LIENS
static void lire_liens(FILE* nom_fichier, const  t_circuit* circuit)
{

}

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
//Fonction: CIRCUIT_IO_SAUVEGARDER
void circuit_IO_sauvegarder(const char* nom_fichier, const  t_circuit* circuit)
{
	FILE* fsortie = fopen(nom_fichier, "w");  //ouverture du fichier 

	char ecrire[TAILLE];
	int infocopied = 0;

	int nb_entrees = t_circuit_get_nb_entrees(circuit);
	int nb_sorties = t_circuit_get_nb_sorties(circuit);
	int nb_portes = t_circuit_get_nb_portes(circuit);

	fprintf(fsortie, "%d %d %d\n", nb_entrees, nb_sorties, nb_portes);

	//Transformer les composantes du circuits en format textuel.
	//Tansformer en textes les composantes de t_entree.
	ecrire_entrees(fsortie, nb_entrees, circuit);

	//Tansformer en textes les composantes de t_sortie.
	ecrire_sorties(fsortie, nb_sorties, circuit);

	//Tansformer en textes les composantes de t_porte.
	ecrire_portes(fsortie, nb_portes, circuit);

	//Tansformer en textes les composantes des liens.
	ecrire_liens(fsortie, circuit);

	fclose(fsortie);
}

/*==========================================================*/
//Fonction: CIRCUIT_IO_CHARGER
void  circuit_IO_charger(const char* chemin_acces, t_circuit* circuit)
{

}