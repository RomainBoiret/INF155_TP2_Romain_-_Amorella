/************************************************************************************************************************************************************************************/
/*  Fichier : CIRCUIT_IO.C																						                                                                    */
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
#define CONVERT_ASCII 48

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
static void ecrire_entrees(FILE* nom_fichier, int nb_entrees, const t_circuit* circuit)
{
	// Création d'un tableau de caractères
	char ecrire[TAILLE];
	printf("\nLes entrees\n");

	for (int i = 0; i < nb_entrees; i++)
	{
		t_entree_serialiser(circuit->entrees[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
		printf("%s", ecrire);
	}
}

/*==========================================================*/
//Fonction: ECRIRE_SORTIES
static void ecrire_sorties(FILE* nom_fichier, int nb_sorties, const  t_circuit* circuit)
{
	// Création d'un tableau de caractères
	char ecrire[TAILLE];
	printf("\nLes sorties\n");

	for (int i = 0; i < nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
		printf("%s", ecrire);
	}
}

/*==========================================================*/
//Fonction: ECRIRE_PORTES
static void ecrire_portes(FILE* nom_fichier, int nb_portes, const  t_circuit* circuit)
{
	char ecrire[TAILLE];
	printf("\nLes portes\n");

	for (int i = 0; i < nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
		//affichage dans la console 
		printf("%s", ecrire);
	}
}

/*==========================================================*/
static void ecrire_liens(FILE* nom_fichier, const  t_circuit* circuit)

{
	printf("\nLes liens\n");
	for (int i = 0; i < circuit->nb_portes; i++)

	{	//Récupération du nom de chaque porte
		t_circuit*porte = t_circuit_get_porte(circuit,i);
		const char*nomporte = t_porte_get_nom(porte);
		fprintf(nom_fichier, "%s ", nomporte);
		printf("Porte %s <- ", nomporte);
		for (int j = 0; j < circuit->portes[i]->nb_entrees; j++)

		{	//Récupération de chaque nom de liaisons liés à ces portes
			const char* nomliaison = t_pin_entree_get_lien(circuit->portes[i]->entrees[j]);
			if (nomliaison == NULL)
			{	//si liaison n'a pas de nom, afficher les xx
				fprintf(nom_fichier, "%s", "XX");
				printf("%s ", "XX");
			}
			else
			{	//Affichage de chaque nom de liaison
				fprintf(nom_fichier, "%s ", nomliaison);
				printf("%s ", nomliaison);
			}
		}

		fprintf(nom_fichier, "\n"); //saut de ligne.
		printf("\n");
	}

	for (int i = 0; i < circuit->nb_sorties; i++)

	{	//Récupération de chaque sortie et affichage de chacun des liens 
		t_circuit*sortie = t_circuit_get_sortie(circuit, i);
		const char *nomsortie = t_sortie_get_nom(sortie);
		const char *nomlien = t_pin_entree_get_lien(circuit->sorties[i]->pin);
		
		fprintf(nom_fichier, "%s ", nomsortie);
		printf("Sortie %s <- ", nomsortie);

		fprintf(nom_fichier, "%s ", nomlien);
		printf("%s", nomlien);

		fprintf(nom_fichier, "\n"); //saut de ligne.
		printf("\n");
	}
}
	/*==========================================================*/
	//Fonction: LIRE_ENTREES
	static void lire_entrees(FILE * chemin_acces, int nb_entrees, const  t_circuit * circuit)
	{
		char nom[TAILLE];
		int id = 0;

		for (int i = 0; i < nb_entrees; i++)
		{
			fscanf(chemin_acces, "%d%s\n", &id, nom);
			t_circuit_ajouter_entree(circuit, id, nom);
		}
	}

	/*==========================================================*/
	//Fonction: LIRE_SORTIES
	static void lire_sorties(FILE * chemin_acces, int nb_sorties, const  t_circuit * circuit)
	{
		char nom[TAILLE];
		int id = 0;

		for (int i = 0; i < nb_sorties; i++)
		{
			fscanf(chemin_acces, "%d%s\n", &id, nom);
			t_circuit_ajouter_sortie(circuit, id, nom);
		}
	}

	/*==========================================================*/
	//Fonction: LIRE_PORTES
	static void lire_portes(FILE * chemin_acces, int nb_portes, const  t_circuit * circuit)
	{
		char nom[TAILLE];
		int id = 0;
		e_types_portes type;

		for (int i = 0; i < nb_portes; i++)
		{
			fscanf(chemin_acces, "%d%d%s\n", &id, &type, nom);
			t_circuit_ajouter_porte(circuit, type, id, nom);
		}
	}

	/*==========================================================*/
	//Fonction: LIRE_LIENS
	static void lire_liens(FILE * chemin_acces, const  t_circuit * circuit)
	{
		char tab_nom[TAILLE];
		char* nom_comp = _strdup(tab_nom);
		char* nom_liais = _strdup(tab_nom);

		int porte_pos;
		int porte_nb_entrees;
		int liaison_pos;
		int sortie_pos;

		t_entree* entree_des;
		t_sortie* sortie_des;
		t_porte* porte_des;
		t_porte* porte;
		t_pin_sortie* source;

		while (!feof(chemin_acces))
		{
			fscanf(chemin_acces, "%s", nom_comp);

			if (nom_comp[0] == 'P')
			{
				porte_pos = nom_comp[1] - 48;

				porte = t_circuit_get_porte(circuit, porte_pos);
				porte_nb_entrees = t_porte_get_nb_entrees(porte);

				for (int i = 0; i < porte_nb_entrees; i++)
				{
					fscanf(chemin_acces, "%s", nom_liais);

					if (nom_liais[0] == 'E')
					{
						liaison_pos = nom_liais[1] - 48;
						entree_des = circuit->entrees[liaison_pos];

						source = t_entree_get_pin(entree_des);

						t_porte_relier(porte, i, nom_liais, source);
					}

					else if (nom_liais[0] == 'P')
					{
						liaison_pos = nom_liais[1] - 48;
						porte_des = t_circuit_get_porte(circuit, liaison_pos);

						source = t_porte_get_pin_sortie(porte);

						t_porte_relier(porte, i, nom_liais, source);
					}
				}
			}

			else if (nom_comp[0] == 'S')
			{
				sortie_pos = nom_comp[1] - 48;
				sortie_des = t_circuit_get_sortie(circuit, sortie_pos);

				fscanf(chemin_acces, "%s", nom_liais);

				liaison_pos = nom_liais[1] - 48;

				porte_des = t_circuit_get_porte(circuit, liaison_pos);

				t_sortie_relier(sortie_des, nom_liais, t_porte_get_pin_sortie(porte_des));
			}
		}
	}


	/***************************************************************************************/
	/*                             DEFINITION DES FONCTIONS                                */
	/***************************************************************************************/

	/*==========================================================*/
	//Fonction: CIRCUIT_IO_SAUVEGARDER
	void circuit_IO_sauvegarder(const char* nom_fichier, const  t_circuit * circuit)
	{
		FILE* fsortie = fopen(nom_fichier, "w");  //Ouverture du fichier.

		int nb_entrees = t_circuit_get_nb_entrees(circuit);
		int nb_sorties = t_circuit_get_nb_sorties(circuit);
		int nb_portes = t_circuit_get_nb_portes(circuit);

		//Ecrire le nombre d'entrees, de sorties et de portes.
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
	void circuit_IO_charger(const char* chemin_acces, t_circuit * circuit)
	{
		FILE* fentree = fopen(chemin_acces, "r");  //Ouverture du fichier.

		assert(fentree != NULL); //Si le fichier est vide, on retourne FAUX.

		int nb_entrees;
		int nb_sorties;
		int nb_portes;

		fscanf(fentree, "%d", &nb_entrees);
		fscanf(fentree, "%d", &nb_sorties);
		fscanf(fentree, "%d", &nb_portes);

		//Lire les composantes de t_entree.
		lire_entrees(fentree, nb_entrees, circuit);

		//Lire les composantes de t_sortie.
		lire_sorties(fentree, nb_sorties, circuit);

		//Lire les composantes de t_porte.
		lire_portes(fentree, nb_portes, circuit);

		//Lire les composantes des liens.
		lire_liens(fentree, circuit);

		fclose(fentree);
	}
