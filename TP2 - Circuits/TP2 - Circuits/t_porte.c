/***************************************************************************************************************************************************************************/
/*  Fichier : T_PORTE.C																																					   */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                           */
/*	          LENGA  Amorella LENA91330301																		                                                           */
/*  Date de creation : <14 / 11 / 2023>																		                                                               */
/*                                                                                                                                                                         */
/*  Ce module contient des fonctions servant a modeliser des portes logiques, notamment des portes ET, OU, XOR et NOT, ainsi que des entrees et des sorties.               */
/***************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "t_porte.h"

/***************************************************************************************/
/*                             DECLARATION DES FONCTIONS PRIVES                        */
/***************************************************************************************/

/* Fonction: init_entree
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Initialise une porte en tant qu'entree dans un circuit.
 * Parametres :
 *   - nouv_porte : Pointeur vers la nouvelle porte a initialiser en tant qu'entree.
 *   - type : Type de la porte a initialiser en tant qu'entree.
 * Retour : Aucun.
 */
static void init_entree(t_porte * nouv_porte, e_types_portes type);

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
// Fonction: init_entree
// Description: Initialise les entrees en fonction du type de la porte.
static void init_entree(t_porte * nouv_porte, e_types_portes type)
{
	nouv_porte->type = type; // Attribution du type a la nouvelle porte.

	switch (type)
	{
		case PORTE_ET: case PORTE_OU: case PORTE_XOR:
		{
			nouv_porte->nb_entrees = MAX_ENTREES_PORTE; // Nombre d'entrees pour certains types de portes.

			for (int i = 0; i < nouv_porte->nb_entrees; i++)
			{
				nouv_porte->entrees[i] = t_pin_entree_init(); // Initialisation des pins d'entree.
			}
			break;
		}

		case PORTE_NOT:
		{
			nouv_porte->nb_entrees = 1; // Nombre d'entrees pour la porte NOT.

			nouv_porte->entrees[0] = t_pin_entree_init(); // Initialisation du pin d'entree unique.
			break;
		}
	}
}

/*==========================================================*/
// Fonction: t_porte_init
// Description: Initialise une nouvelle porte avec un identifiant, un type, un nom, et configure ses entrees et sa sortie.
t_porte* t_porte_init(int id, e_types_portes type, char* nom)
{
	t_porte* nouv_porte; // Variable pour stocker la nouvelle porte.

	nouv_porte = (t_porte*)malloc(sizeof(t_porte)); // Allocation de memoire pour la porte.

	nouv_porte->id = id; // Attribution de l'identifiant a la porte.
	nouv_porte->nom = _strdup(nom); // Attribution du nom a la porte en copiant la chaine.
	nouv_porte->type = type; // Attribution du type a la porte.

	init_entree(nouv_porte, type); // Initialisation des entrees en fonction du type de porte.

	nouv_porte->sortie = t_pin_sortie_init(); // Initialisation du pin de sortie de la porte.

	return nouv_porte; // Retourne la nouvelle porte initialisee.
}

/*==========================================================*/
// Fonction: t_porte_destroy
// Description: Libere la memoire allouee pour une porte, y compris ses entrees et sa sortie.
void t_porte_destroy(t_porte* porte)
{
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		t_pin_entree_destroy(porte->entrees[i]); // Liberation de la memoire des pins d'entree.
	}

	t_pin_sortie_destroy(porte->sortie); // Liberation de la memoire du pin de sortie.
	free(porte); // Liberation de la memoire allouee pour la porte.
}

/*==========================================================*/
// Fonction: t_porte_calculer_sorties
// Description: Calcule la sortie de la porte en fonction des valeurs des entrees.
void t_porte_calculer_sorties(t_porte* porte)
{
	int pin_entree0; // Variable contenant la valeur du premier pin d'entree.
	int pin_entree1; // Variable contenant la valeur du deuxieme pin d'entree.
	int resultat;	 // Variable contenant le resultat.
	
	pin_entree0 = t_pin_entree_get_valeur(porte->entrees[0]); // Valeur du premier pin d'entree.

	if (porte->type != PORTE_NOT)
	{
		pin_entree1 = t_pin_entree_get_valeur(porte->entrees[1]); // Valeur du deuxieme pin d'entree.
	}

	switch (porte->type)
	{
		case PORTE_ET:
		{
			resultat = pin_entree0 & pin_entree1; // Calcul de la porte ET.
			break;
		}

		case PORTE_OU:
		{
			resultat = pin_entree0 | pin_entree1; // Calcul de la porte OU.
			break;
		}

		case PORTE_XOR:
		{
			resultat = pin_entree0 ^ pin_entree1; // Calcul de la porte XOR.
			break;
		}

		case PORTE_NOT:
		{
			resultat = !pin_entree0; // Calcul de la porte NOT.
			break;
		}
	}

	t_pin_sortie_set_valeur(porte->sortie, resultat);
}

/*==========================================================*/
// Fonction: t_porte_relier
// Description: Relie un pin de sortie source à un numéro d'entrée spécifique de la porte.
int t_porte_relier(t_porte* dest, int num_entree, char* nom_sortie, const t_pin_sortie* source)
{
	if (num_entree > (dest->nb_entrees) - 1)
		return FAUX; // Retourne Faux si le lien n'existe pas pour le numéro d'entrée donné.

	t_pin_entree_relier(dest->entrees[num_entree], nom_sortie, source); // Relie le pin d'entrée à la sortie source.
	return VRAI; // Retourne Vrai si le lien a été effectué.
}

/*==========================================================*/
// Fonction: t_porte_est_reliee
// Description: Verifie si la porte est entierement reliee (entrees et sortie).
int t_porte_est_reliee(t_porte* porte)
{
	// Verifie les entrees de la porte.
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		if (t_pin_entree_est_reliee(porte->entrees[i]) == FAUX)
			return FAUX; // Retourne Faux si une entree n'est pas entierement reliee.
	}

	// Vérifie la sortie de la porte.
	if (t_pin_sortie_est_reliee(porte->sortie) == FAUX)
		return FAUX; // Retourne Faux si la sortie n'est pas entierement reliee.

	return VRAI; // Retourne Vrai si la porte est entierement reliee.
}

/*==========================================================*/
// Fonction: t_porte_reset
// Description: Reinitialise les entrees et la sortie de la porte a l'etat INACTIF.
void t_porte_reset(t_porte* porte)
{
	// Reinitialise les entrees a l'etat INACTIF.
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		t_pin_entree_set_valeur(porte->entrees[i], INACTIF);
	}

	// Reinitialise la sortie a l'etat INACTIF.
	t_pin_sortie_set_valeur(porte->sortie, INACTIF);
}

/*==========================================================*/
// Fonction: t_porte_propager_signal
// Description: Propage le signal de la porte si toutes ses entrees ont reçu un signal.
int t_porte_propager_signal(t_porte* porte)
{
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		if (t_pin_entree_get_valeur(porte->entrees[i]) == INACTIF)
			return FAUX; // Retourne Faux si une entree est inactive.
	}

	// Calcule la sortie et propage le signal.
	t_porte_calculer_sorties(porte);
	return t_pin_sortie_propager_signal(porte->sortie); // Retourne Vrai si toutes les entrees ont reçu un signal.
}

/************************** LES ACCESSEURS **************************/

/*==========================================================*/
// Fonction: t_porte_get_id
// Description: Recupere l'identifiant de la porte.
int t_porte_get_id(const t_porte* porte)
{
	return porte->id; // Retourne l'identifiant de la porte.
}

/*==========================================================*/
// Fonction: t_porte_get_nom
// Description: Recupere le nom de la porte.
char* t_porte_get_nom(const t_porte* porte)
{
	return porte->nom; // Retourne le nom de la porte.
}

/*==========================================================*/
// Fonction: t_porte_get_nb_entrees
// Description: Recupere le nombre d'entrees de la porte.
int t_porte_get_nb_entrees(const t_porte* porte)
{
	return porte->nb_entrees; // Retourne le nombre d'entrees de la porte.
}

/*==========================================================*/
// Fonction: t_porte_get_type
// Description: Recupere le type de la porte.
e_types_portes t_porte_get_type(const t_porte* porte)
{
	return porte->type; // Retourne le type de la porte.
}

/*==========================================================*/
// Fonction: t_porte_get_pin_entree
// Description: Recupere le pin d'entree a un numero specifique.
t_pin_entree* t_porte_get_pin_entree(const t_porte* porte, int num)
{
	return porte->entrees[num]; // Retourne le pin d'entree correspondant au numero specifie.
}

/*==========================================================*/
// Fonction: t_porte_get_pin_sortie
// Description: Recupere le pin de sortie de la porte.
t_pin_sortie* t_porte_get_pin_sortie(const t_porte* porte)
{
	return porte->sortie; // Retourne le pin de sortie de la porte.
}

/*==========================================================*/
// Fonction: t_porte_serialiser
// Description: Serialise les informations de la porte (identifiant, type, nom) dans une chaine de caracteres.
void t_porte_serialiser(const t_porte* porte, char* resultat)
{
	int infocopie = 0; // Variable utilisee pour suivre la position de copie dans le resultat.

	// Copie de l'identifiant numerique de la porte dans la chaine resultat.
	infocopie += sprintf(resultat, "%d ", t_porte_get_id(porte));

	// Copie du type enumere de la porte dans la chaine resultat.
	infocopie += sprintf(resultat + infocopie, "%d ", t_porte_get_type(porte));

	// Copie du nom de la porte dans la chaine resultat.
	infocopie += sprintf(resultat + infocopie, "%s\n", t_porte_get_nom(porte));

	// Fin de la serialisation en ajoutant un caractere de fin de chaine.
	resultat[infocopie] = '\0';
}
