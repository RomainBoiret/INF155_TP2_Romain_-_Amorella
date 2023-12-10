/****************************************************************************************************************************************************************************************/
/*  Fichier : T_CIRCUIT.C																						                                                                        */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                        */
/*	          LENGA  Amorella LENA91330301																		                                                                        */
/*  Date de creation : <14 / 11 / 2023>																		                                                                            */
/*                                                                                                                                                                                      */
/*  Ce module contient des fonctions conçuent pour simuler un circuit abstrait en utilisant des structures de donnees telles que des circuits, des portes, des entrees et des sorties   */
/****************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "t_circuit.h"
#include "files_portes.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
// Fonction: t_circuit_init
// Description: Initialise un circuit avec un nombre limite d'entrees, de sorties et de portes.
t_circuit* t_circuit_init(void)
{
	t_circuit* nouv_circuit; // Pointeur vers la structure de donnees du circuit.

	nouv_circuit = (t_circuit*)malloc(sizeof(t_circuit)); // Allocation de memoire pour le circuit.

	// Initialisation des compteurs a zero.
	nouv_circuit->nb_entrees = 0;
	nouv_circuit->nb_sorties = 0;
	nouv_circuit->nb_portes = 0;

	// Initialisation des tableaux d'entrees, de sorties et de portes a NULL.
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

	return	nouv_circuit; // Retourne le pointeur vers le circuit initialise.
}

/*==========================================================*/
// Fonction: t_circuit_destroy
// Description: Libere la memoire allouee pour le circuit, y compris ses entrees, sorties et portes.
void t_circuit_destroy(t_circuit* circuit)
{
	// Liberation de la memoire pour chaque entree du circuit.
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_destroy(circuit->entrees[i]);
	}

	// Liberation de la memoire pour chaque sortie du circuit.
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_destroy(circuit->sorties[i]);
	}

	// Liberation de la memoire pour chaque porte du circuit.
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_destroy(circuit->portes[i]);
	}

	free(circuit); // Liberation de la memoire pour la structure de donnees du circuit.
}

/*==========================================================*/
// Fonction: t_circuit_ajouter_porte
// Description: Ajoute une nouvelle porte au circuit avec les details specifies.
t_porte* t_circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{
	// Verifier si le nombre de portes ne depasse pas le nombre permis
	if (circuit->nb_portes < CIRCUIT_MAX_PORTES)
	{
		// Creation de la nouvelle porte en appelant la fonction t_porte_init()
		t_porte* nouv_porte = t_porte_init(id, le_type, nom);
		circuit->portes[circuit->nb_portes] = nouv_porte;
		circuit->nb_portes++;

		return nouv_porte; // Retourne Vrai si la porte a bien ete ajoutee.
	}

	return NULL; // Retourne NULL si la porte n'a pas ete ajoutee.
}

/*==========================================================*/
// Fonction: t_circuit_ajouter_entree
// Description: Ajoute une nouvelle entree au circuit avec les details specifies.
t_entree* t_circuit_ajouter_entree(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_entrees < MAX_ENTREES)
	{
		// Creation de la nouvelle entree si la condition est vraie
		t_entree* nouv_entree = t_entree_init(id, nom);
		circuit->entrees[circuit->nb_entrees] = nouv_entree;
		circuit->nb_entrees++;

		// Retourne la nouvelle entree si elle a ete ajoutee avec succes.
		return (nouv_entree);
	}

	return NULL; // Retourne NULL si l'entree n'a pas ete ajoutee.
}

/*==========================================================*/
// Fonction: t_circuit_ajouter_sortie
// Description: Ajoute une nouvelle sortie au circuit avec les details specifies.
t_sortie* t_circuit_ajouter_sortie(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_sorties < MAX_SORTIES)
	{
		// Creation de la nouvelle sortie si la condition est vraie
		t_sortie* nouv_sortie = t_sortie_init(id, nom);
		circuit->sorties[circuit->nb_sorties] = nouv_sortie;
		circuit->nb_sorties++;

		return (nouv_sortie); // Retourne la nouvelle sortie si elle a ete ajoutee avec succes.
	}

	return NULL; // Retourne NULL si la sortie n'a pas ete ajoutee.
}

/*==========================================================*/
// Fonction: t_circuit_est_valide
// Description: Verifie si le circuit est valide en verifiant la connectivite de ses composants.
int t_circuit_est_valide(t_circuit* circuit)
{
	// Verifie la connectivite des entrees, sorties et portes du circuit.
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

	return VRAI; // Retourne VRAI si le circuit est valide.
}

/*==========================================================*/
// Fonction: t_circuit_appliquer_signal
// Description: Applique un signal aux entrees du circuit.
int t_circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{
	if (nb_bits == circuit->nb_entrees)
	{
		// Change la valeur du pin de sortie de l'entree.
		for (int i = 0; i < circuit->nb_entrees; i++)
		{
			t_pin_sortie_set_valeur(circuit->entrees[i]->pin, signal[i]);
		}

		return VRAI; // Retourne VRAI si le signal a ete applique avec succes.
	}

	return FAUX; // Retourne FAUX si le nombre de bits ne correspond pas au nombre d'entrees.
}

/*==========================================================*/
// Fonction: t_circuit_reset
// Description: Reinitialise les entrees, sorties et portes du circuit.
void t_circuit_reset(t_circuit* circuit)
{
	// Reinitialise les entrees, sorties et portes du circuit.
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
// Fonction: t_circuit_propager_signal
// Description: Propage le signal a travers les composants du circuit.
int t_circuit_propager_signal(t_circuit* circuit)
{
	// Initialise les variables locales.
	t_file nouv_file;
	initfile(&nouv_file); // File de portes initialisee.
	t_porte* porte_courante = NULL; // Pointeur vers une porte.
	int nb_iterations = 0; // Initialisation a 0.

	// Verifie si le circuit est valide.
	if (t_circuit_est_valide(circuit) == FAUX)
		return FAUX;

	// Verifie la validite des entrees.
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		if (t_entree_get_pin(circuit->entrees[i]) == INACTIF)
			return FAUX;
	}

	// Propage le signal de l'entree.
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_propager_signal(circuit->entrees[i]);
	}

	// Ajoute les portes a la file.
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		ajouterfin(&nouv_file, circuit->portes[i]);
	}

	while (!vide(&nouv_file) && nb_iterations < (circuit->nb_portes * (circuit->nb_portes + 1) / 2))
	{
		// Defile une porte de la file et la stocke dans porte_courante.
		enleverdebut(&nouv_file, &porte_courante);

		int val_propage = t_porte_propager_signal(porte_courante);

		// Si le signal ne se propage pas, le range dans la file.
		if (val_propage == FAUX)
		{
			ajouterfin(&nouv_file, porte_courante);
		}

		nb_iterations++;
	}

	if (vide(&nouv_file))
	{
		return VRAI; // Si la file est vide, le signal s'est propage avec succes.
	}
	else
	{
		return FAUX; // Le circuit a une boucle.
	}
}

/************************** Les ACCESSEURS ************************************/

/*==========================================================*/
// Fonction: t_circuit_get_nb_portes
// Description: Renvoie le nombre de portes dans le circuit.
int t_circuit_get_nb_portes(const t_circuit* circuit)
{
	return circuit->nb_portes; // Retourne le nombre de portes actuel du circuit.
}

/*==========================================================*/
// Fonction: t_circuit_get_porte
// Description: Renvoie la porte a la position donnee dans le circuit, si elle existe.
t_porte* t_circuit_get_porte(const t_circuit* circuit, int pos)
{
	if (pos > INACTIF && pos < CIRCUIT_MAX_PORTES)
	{
		return circuit->portes[pos]; // Retourne la porte a la position donnee dans le circuit.
	}
	else
	{
		return NULL; // Retourne NULL si la position n'est pas valide ou si la porte n'existe pas.
	}
}

/*==========================================================*/
// Fonction: t_circuit_get_nb_sorties
// Description: Renvoie le nombre de sorties dans le circuit.
int t_circuit_get_nb_sorties(const t_circuit* circuit)
{
	return circuit->nb_sorties; // Retourne le nombre de sorties actuel du circuit.
}

/*==========================================================*/
// Fonction: t_circuit_get_sortie
// Description: Renvoie la sortie a la position donnee dans le circuit, si elle existe.
t_sortie* t_circuit_get_sortie(const t_circuit* circuit, int pos)
{
	if (pos > INACTIF && pos < MAX_SORTIES)
	{
		return circuit->sorties[pos]; // Retourne la sortie a la position donnee dans le circuit.
	}
	else
	{
		return NULL; // Retourne NULL si la position n'est pas valide ou si la sortie n'existe pas.
	}
}

/*==========================================================*/
// Fonction: t_circuit_get_nb_entrees
// Description: Renvoie le nombre d'entrees dans le circuit.
int t_circuit_get_nb_entrees(const t_circuit* circuit)
{
	return circuit->nb_entrees; // Retourne le nombre d'entrees actuel du circuit.
}

/*==========================================================*/
// Fonction: t_circuit_get_entree
// Description: Renvoie l'entree a la position donnee dans le circuit, si elle existe.
t_entree* t_circuit_get_entree(const t_circuit* circuit, int pos)
{
	if (pos > INACTIF && pos < MAX_ENTREES)
	{
		return circuit->entrees[pos]; // Retourne l'entree a la position donnee dans le circuit.
	}
	else
	{
		return NULL; // Retourne NULL si la position n'est pas valide ou si l'entree n'existe pas.
	}
}
