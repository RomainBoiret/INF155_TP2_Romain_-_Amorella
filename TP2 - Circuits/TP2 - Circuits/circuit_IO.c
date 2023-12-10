/*******************************************************************************************************************************************************************************************************/
/*  Fichier : CIRCUIT_IO.C																						                                                                                       */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                                       */
/*	          LENGA  Amorella LENA91330301																		                                                                                       */
/*  Date de creation : <28 / 11 / 2023>																		                                                                                           */
/*                                                                                                                                                                                                     */
/*  Ce module contient des fonctions servant a la serialisation, la sauvegarde et le chargement a partir de fichiers, ainsi que la gestion des connexions entre les differentes parties du circuit.    */
/*******************************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circuit_IO.h"

/***************************************************************************************/
/*                         DECLARATION DES FONCTIONS PRIVEES                           */
/***************************************************************************************/

/* Fonction: ecrire_entrees
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Ecrit les entrees du circuit dans un fichier.
 * Parametres :
 *   - nom_fichier : Le nom du fichier ou ecrire les informations.
 *   - nb_entrees : Le nombre d'entrees du circuit.
 *   - circuit : Le circuit dont les entrees doivent etre ecrites.
 * Retour : Aucun.
 */
static void ecrire_entrees(const char* nom_fichier, int nb_entrees, const t_circuit* circuit);

/* Fonction: ecrire_sorties
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Ecrit les sorties du circuit dans un fichier.
 * Parametres :
 *   - nom_fichier : Le nom du fichier ou ecrire les informations.
 *   - nb_sorties : Le nombre de sorties du circuit.
 *   - circuit : Le circuit dont les sorties doivent etre ecrites.
 * Retour : Aucun.
 */
static void ecrire_sorties(const char* nom_fichier, int nb_sorties, const t_circuit* circuit);

/* Fonction: ecrire_portes
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Ecrit les informations relatives aux portes du circuit dans un fichier.
 * Parametres :
 *   - nom_fichier : Le nom du fichier ou ecrire les informations.
 *   - nb_portes : Le nombre de portes du circuit.
 *   - circuit : Le circuit dont les informations sur les portes doivent etre ecrites.
 * Retour : Aucun.
 */
static void ecrire_portes(const char* nom_fichier, int nb_portes, const t_circuit* circuit);

/* Fonction: ecrire_liens
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Ecrit les liens (connections) des elements du circuit dans un fichier.
 * Parametres :
 *   - nom_fichier : Le nom du fichier ou ecrire les informations.
 *   - circuit : Le circuit dont les liens doivent etre ecrits.
 * Retour : Aucun.
 */
static void ecrire_liens(const char* nom_fichier, const t_circuit* circuit);

/* Fonction: lire_entrees
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Lit les entrees du circuit a partir d'un fichier.
 * Parametres :
 *   - nom_fichier : Le nom du fichier a partir duquel lire les informations.
 *   - nb_entrees : Le nombre d'entrees du circuit.
 *   - circuit : Le circuit ou les entrees lues doivent etre stockees.
 * Retour : Aucun.
 */
static void lire_entrees(const char* nom_fichier, int nb_entrees, const t_circuit* circuit);

/* Fonction: lire_sorties
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Lit les sorties du circuit a partir d'un fichier.
 * Parametres :
 *   - nom_fichier : Le nom du fichier a partir duquel lire les informations.
 *   - nb_sorties : Le nombre de sorties du circuit.
 *   - circuit : Le circuit ou les sorties lues doivent etre stockees.
 * Retour : Aucun.
 */
static void lire_sorties(const char* nom_fichier, int nb_sorties, const t_circuit* circuit);

/* Fonction: lire_portes
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Lit les informations relatives aux portes du circuit a partir d'un fichier.
 * Parametres :
 *   - nom_fichier : Le nom du fichier a partir duquel lire les informations.
 *   - nb_portes : Le nombre de portes du circuit.
 *  - circuit : Le circuit où les informations sur les portes lues doivent etre stockees.
 * Retour : Aucun.
 */
static void lire_portes(const char* nom_fichier, int nb_portes, const t_circuit* circuit);

/* Fonction: lire_liens
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Lit les liens (connections) des elements du circuit a partir d'un fichier.
 * Parametres :
 *   - nom_fichier : Le nom du fichier a partir duquel lire les informations.
 *   - circuit : Le circuit ou les liens lus doivent etre stockes.
 * Retour : Aucun.
 */
static void lire_liens(const char* nom_fichier, const t_circuit* circuit);

/***************************************************************************************/
/*                         DEFINITION DES FONCTIONS PRIVEES                            */
/***************************************************************************************/

/*==========================================================*/
// Fonction: ecrire_entrees
// Description: Cette fonction ecrit les informations sur les entrees dans un fichier et affiche ces informations dans la console.
static void ecrire_entrees(FILE* nom_fichier, int nb_entrees, const t_circuit* circuit)
{
	char ecrire[TAILLE]; // Creation d'un tableau de caracteres.
	printf("\nLes entrees:\n");

	// Iteration sur toutes les entrees du circuit pour les ecrire dans le fichier et les afficher.
	for (int i = 0; i < nb_entrees; i++)
	{
		t_entree_serialiser(circuit->entrees[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
		printf("%s", ecrire);
	}
}

/*==========================================================*/
// Fonction: ecrire_sorties
// Description: Cette fonction ecrit les informations sur les sorties dans un fichier et affiche ces informations dans la console.
static void ecrire_sorties(FILE* nom_fichier, int nb_sorties, const  t_circuit* circuit)
{
	char ecrire[TAILLE]; // Creation d'un tableau de caracteres.
	printf("\nLes sorties:\n");

	// Iteration sur toutes les sorties du circuit pour les ecrire dans le fichier et les afficher.
	for (int i = 0; i < nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
		printf("%s", ecrire);
	}
}

/*==========================================================*/
// Fonction: ecrire_portes
// Description: Cette fonction ecrit les informations sur les portes dans un fichier et affiche ces informations dans la console.
static void ecrire_portes(FILE* nom_fichier, int nb_portes, const  t_circuit* circuit)
{
	char ecrire[TAILLE]; // Creation d'un tableau de caracteres.
	printf("\nLes portes:\n");

	// Iteration sur toutes les portes du circuit pour les ecrire dans le fichier et les afficher.
	for (int i = 0; i < nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], ecrire);
		fprintf(nom_fichier, "%s", ecrire);
		printf("%s", ecrire);
	}
}

/*==========================================================*/
// Fonction: ecrire_liens
// Description: Cette fonction ecrit les informations sur les connexions des composants du circuit dans un fichier et affiche ces informations dans la console.
static void ecrire_liens(FILE* nom_fichier, const  t_circuit* circuit)
{
	printf("\nLes liens:\n");

	// Parcours de chaque porte du circuit pour ecrire les informations sur les connexions dans le fichier et les afficher.
	for (int i = 0; i < circuit->nb_portes; i++)
	{	
		// Recuperation du nom de chaque porte.
		t_porte* porte = t_circuit_get_porte(circuit,i);
		const char* nomporte = t_porte_get_nom(porte);

		fprintf(nom_fichier, "%s ", nomporte);
		printf("Porte %s <- ", nomporte);

		// Parcours de chaque entree de la porte pour obtenir les informations sur les liaisons.
		for (int j = 0; j < circuit->portes[i]->nb_entrees; j++)
		{	
			// Recuperation de chaque nom de liaisons lies a ces portes.
			const char* nomliaison = t_pin_entree_get_lien(circuit->portes[i]->entrees[j]);

			t_pin_entree* entree_porte = t_porte_get_pin_entree(porte, j);

			// Si le nom de la liaison est vide:
			if (strcmp(t_pin_entree_get_lien(entree_porte), "") == 0)
			{
				fprintf(nom_fichier, "%s ", "XX");
				printf("%s ", "VIDE");
			}
			else
			{	
				// Affichage de chaque nom de liaison.
				fprintf(nom_fichier, "%s ", nomliaison);
				printf("%s ", nomliaison);
			}
		}

		fprintf(nom_fichier, "\n"); // Saut de ligne dans le fichier.
		printf("\n"); // Saut de ligne dans la console.
	}

	// Parcours de chaque sortie pour obtenir les informations sur les liaisons.
	for (int i = 0; i < circuit->nb_sorties; i++)
	{	
		// Recuperation de chaque sortie et affichage de chacun des liens.
		t_sortie* sortie = t_circuit_get_sortie(circuit, i);
		const char* nomsortie = t_sortie_get_nom(sortie);
		const char* nomlien = t_pin_entree_get_lien(t_sortie_get_pin(sortie));
		
		fprintf(nom_fichier, "%s ", nomsortie);
		printf("Sortie %s <- ", nomsortie);

		if (strcmp(nomlien, "") == 0)
		{
			fprintf(nom_fichier, "%s ", "XX");
			printf("%s", "VIDE");
		}
		else
		{
			fprintf(nom_fichier, "%s ", nomlien);
			printf("%s", nomlien);
		}

		fprintf(nom_fichier, "\n"); // Saut de ligne dans le fichier.
		printf("\n"); // Saut de ligne dans la console.
	}
}

/*==========================================================*/
// Fonction: lire_entrees
// Description: Cette fonction lit les informations sur les entrees d'un circuit a partir d'un fichier et les ajoutes au circuit.
static void lire_entrees(FILE * chemin_acces, int nb_entrees, const  t_circuit * circuit)
{
	char nom[TAILLE]; // Tableaux de caracteres pour stocker le nom de l'entree lu depuis le fichier.
	int id = 0; // Variable pour stocker l'identifiant de l'entree lu depuis le fichier.

	// Boucle pour lire chaque entree a partir du fichier.
	for (int i = 0; i < nb_entrees; i++)
	{
		// Lecture de l'identifiant et du nom de l'entree depuis le fichier.
		fscanf(chemin_acces, "%d%s\n", &id, nom);

		// Ajout de l'entree au circuit en utilisant la fonction t_circuit_ajouter_entree().
		t_circuit_ajouter_entree(circuit, id, nom);
	}
}

/*==========================================================*/
// Fonction: lire_sorties
// Description: Cette fonction lit les informations sur les sorties d'un circuit a partir d'un fichier et les ajoutes au circuit.
static void lire_sorties(FILE * chemin_acces, int nb_sorties, const  t_circuit * circuit)
{
	char nom[TAILLE]; // Tableaux de caracteres pour stocker le nom de la sortie lu depuis le fichier.
	int id = 0; // Variable pour stocker l'identifiant de la sortie lu depuis le fichier.

	// Boucle pour lire chaque sortie a partir du fichier.
	for (int i = 0; i < nb_sorties; i++)
	{
		// Lecture de l'identifiant et du nom de la sortie depuis le fichier.
		fscanf(chemin_acces, "%d%s\n", &id, nom);

		// Ajout de la sortie au circuit en utilisant la fonction t_circuit_ajouter_sortie().
	    t_circuit_ajouter_sortie(circuit, id, nom);
	}
}

/*==========================================================*/
// Fonction: lire_portes
// Description: Cette fonction lit les informations sur les portes d'un circuit a partir d'un fichier et les ajoutes au circuit.
static void lire_portes(FILE * chemin_acces, int nb_portes, const  t_circuit * circuit)
{
	char nom[TAILLE]; // Tableaux de caracteres pour stocker le nom de la porte lu depuis le fichier.
	int id = 0; // Variable pour stocker l'identifiant de la porte lu depuis le fichier.
	e_types_portes type; // Variable pour stocker le type de la porte lu depuis le fichier.

	// Boucle pour lire chaque porte a partir du fichier.
	for (int i = 0; i < nb_portes; i++)
	{
		// Lecture de l'identifiant et du nom de la porte depuis le fichier.
		fscanf(chemin_acces, "%d%d%s\n", &id, &type, nom);

		// Ajout de la porte au circuit en utilisant la fonction t_circuit_ajouter_porte().
		t_circuit_ajouter_porte(circuit, type, id, nom);
	}
}

/*==========================================================*/
// Fonction: lire_liens
// Description: Cette fonction lit les liens entre les differentes composantes du circuit a partir d'un fichier et les relies correctement.
static void lire_liens(FILE * chemin_acces, const  t_circuit * circuit)
{
	char tab_nom[TAILLE]; // Tableau de caracteres pour stocker le nom de la liaison lu depuis le fichier.
	char* nom_comp = _strdup(tab_nom); // Variable pour stocker le nom de la composante lu depuis le fichier.
	char* nom_liais = _strdup(tab_nom); // Variable pour stocker le nom de la liaison lu depuis le fichier.

	int porte_pos; // Position de la porte dans le circuit.
	int porte_nb_entrees; // Nombre d'entrees de la porte.

	int liaison_pos; // Position de la liaison.
	int sortie_pos; // Position de la sortie.

	t_entree* entree_des; // Pointeur vers l'entree designee.
	t_sortie* sortie_des; // Pointeur vers la sortie désignee.
	t_porte* porte_des; // Pointeur vers la porte désignee.
	t_porte* porte; // Pointeur vers une porte.
	t_pin_sortie* source; // Pointeur vers la source du signal.

	// Boucle pour lire chaque ligne de liens à partir du fichier.
	while (!feof(chemin_acces))
	{
		fscanf(chemin_acces, "%s", nom_comp); // Lecture du nom de la composante.

		// Verification du type de la composante.
		if (nom_comp[0] == 'P') // Si la composante est une porte.
		{
			porte_pos = nom_comp[1] - CONVERT_ASCII; // Recuperation de la position de la porte.

			// Recuperation de la porte depuis le circuit.
			porte = t_circuit_get_porte(circuit, porte_pos);
			porte_nb_entrees = t_porte_get_nb_entrees(porte); // Recuperation du nombre d'entrees de la porte.

			// Boucle pour lire les liens associes a chaque entree de la porte.
			for (int i = 0; i < porte_nb_entrees; i++)
			{
				fscanf(chemin_acces, "%s", nom_liais); // Lecture du nom de la liaison.

				if (nom_liais[0] == 'E') // Si la liaison est une entree.
				{
					liaison_pos = nom_liais[1] - CONVERT_ASCII; // Recuperation de la position de la liaison.
					entree_des = circuit->entrees[liaison_pos]; // Recuperation de l'entree designee.

					source = t_entree_get_pin(entree_des); // Recuperation de la source du signal depuis l'entree.

					// Relier la porte a l'entree correspondante en utilisant t_porte_relier().
					t_porte_relier(porte, i, nom_liais, source);
				}
				else if (nom_liais[0] == 'P') // Si la liaison est une autre porte.
				{
					liaison_pos = nom_liais[1] - CONVERT_ASCII; // Recuperation de la position de la liaison.
					porte_des = t_circuit_get_porte(circuit, liaison_pos); // Recuperation de la porte designee.

					source = t_porte_get_pin_sortie(porte_des); // Recuperation de la source du signal depuis la porte.
					
					// Relier la porte a l'entree correspondante en utilisant t_porte_relier().
					t_porte_relier(porte, i, nom_liais, source);
				}
			}
		}

		else if (nom_comp[0] == 'S') // Si la composante est une sortie.
		{
			sortie_pos = nom_comp[1] - CONVERT_ASCII; // Recuperation de la position de la sortie.
			sortie_des = t_circuit_get_sortie(circuit, sortie_pos); // Recuperation de la sortie designee.

			fscanf(chemin_acces, "%s", nom_liais); // Lecture du nom de la liaison.
			liaison_pos = nom_liais[1] - CONVERT_ASCII; // Recuperation de la position de la liaison.
			porte_des = t_circuit_get_porte(circuit, liaison_pos); // Recuperation de la porte designee.

			// Relier la sortie a la porte correspondante en utilisant t_sortie_relier().
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
	FILE* fsortie = fopen(nom_fichier, "w");  // Ouverture du fichier.

	int nb_entrees = t_circuit_get_nb_entrees(circuit); // Recuperer le nombre d'entrees du circuit.
	int nb_sorties = t_circuit_get_nb_sorties(circuit); // Recuperer le nombre de sorties du circuit.
	int nb_portes = t_circuit_get_nb_portes(circuit);   // Recuperer le nombre de portes du circuit.

	// Ecrire le nombre d'entrees, de sorties et de portes.
	fprintf(fsortie, "%d %d %d\n", nb_entrees, nb_sorties, nb_portes);
	printf("\nLes composantes du circuit:\n");
	printf("%d entrees, %d sorties, %d portes\n", nb_entrees, nb_sorties, nb_portes);

	// Tansformer en textes les composantes de t_entree.
	ecrire_entrees(fsortie, nb_entrees, circuit);

	// Tansformer en textes les composantes de t_sortie.
	ecrire_sorties(fsortie, nb_sorties, circuit);

	// Tansformer en textes les composantes de t_porte.
	ecrire_portes(fsortie, nb_portes, circuit);

	// Tansformer en textes les composantes des liens.
	ecrire_liens(fsortie, circuit);

	fclose(fsortie);
}

/*==========================================================*/
//Fonction: CIRCUIT_IO_CHARGER
void circuit_IO_charger(const char* chemin_acces, t_circuit * circuit)
{
	FILE* fentree = fopen(chemin_acces, "r");  // Ouverture du fichier.

	assert(fentree != NULL); // Si le fichier est vide, on retourne FAUX.

	int nb_entrees; // Pour contenir le nombre d'entrees du circuit.
	int nb_sorties; // Pour contenir le nombre de sorties du circuit.
	int nb_portes; // Pour contenir le nombre de portes du circuit.

	fscanf(fentree, "%d", &nb_entrees); // Recuperer le nombre d'entrees du circuit.
	fscanf(fentree, "%d", &nb_sorties); // Recuperer le nombre de sorties du circuit.
	fscanf(fentree, "%d", &nb_portes);  // Recuperer le nombre de portes du circuit.

	// Lire les composantes de t_entree.
	lire_entrees(fentree, nb_entrees, circuit);

	// Lire les composantes de t_sortie.
	lire_sorties(fentree, nb_sorties, circuit);

	// Lire les composantes de t_porte.
	lire_portes(fentree, nb_portes, circuit);

	// Lire les composantes des liens.
	lire_liens(fentree, circuit);

	fclose(fentree);
}
