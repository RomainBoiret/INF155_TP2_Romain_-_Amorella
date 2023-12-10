/*********************************************************************************************************************************************************************/
/*  Fichier : T_PIN_SORTIE.C																						                                                 */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                     */
/*	          LENGA  Amorella LENA91330301																		                                                     */
/*  Date de creation : <14 / 11 / 2023>																		                                                         */
/*                                                                                                                                                                   */
/*  Ce module contient des fonctions destinees a la manipulation d'une structure de donnees representant un pin de sortie (t_pin_sortie)                             */
/*********************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "t_pin_sortie.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
// Fonction: t_pin_sortie_init
// Description: Initialise un pin de sortie avec une valeur par defaut et un tableau de liaisons.
t_pin_sortie* t_pin_sortie_init(void)
{
    t_pin_sortie* nouv_pin_sortie; // Variable pour stocker le nouveau pin de sortie.

    nouv_pin_sortie = (t_pin_sortie*)malloc(sizeof(t_pin_sortie)); // Allocation de memoire pour le pin de sortie.

    nouv_pin_sortie->valeur = INACTIF; // Initialisation de la valeur du pin à INACTIF.
    nouv_pin_sortie->nb_liaisons = 0; // Initialisation du nombre de liaisons a zero.

    // Initialisation de chaque element du tableau de liaisons à NULL.
    for (int i = 0; i < SORTIE_MAX_LIAISONS; i++)
    {
        nouv_pin_sortie->liaisons[i] = NULL;
    }

    return nouv_pin_sortie; // Retourne le nouveau pin de sortie initialise.
}

/*==========================================================*/
// Fonction: t_pin_sortie_destroy
// Description: Libere la memoire allouee pour un pin de sortie.
void t_pin_sortie_destroy(t_pin_sortie* pin)
{
    free(pin); // Libere la memoire allouee pour le pin de sortie.
}

/*==========================================================*/
// Fonction: t_pin_sortie_get_valeur
// Description: Recupere la valeur actuelle du pin de sortie.
int t_pin_sortie_get_valeur(t_pin_sortie* pin)
{
    return pin->valeur; // Recupere et retourne la valeur du pin de sortie.
}

/*==========================================================*/
// Fonction: t_pin_sortie_set_valeur
// Description: Definit une nouvelle valeur pour le pin de sortie.
void t_pin_sortie_set_valeur(t_pin_sortie* pin, int valeur)
{
    if (valeur < INACTIF || valeur > 1)
    {
        return; // Valeur incorrecte, ne fait rien.
    }
    pin->valeur = valeur; // Met a jour la valeur du pin de sortie.
}

/*==========================================================*/
// Fonction: t_pin_sortie_ajouter_lien
// Description: Ajoute une liaison entre le pin de sortie et un pin d'entree.
int t_pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, t_pin_entree* pin_entree)
{
    if (pin_sortie->nb_liaisons < SORTIE_MAX_LIAISONS)
    {
        // Ajoute le pin d'entree a la liste des liaisons du pin de sortie.
        pin_sortie->liaisons[pin_sortie->nb_liaisons] = pin_entree;
        pin_sortie->nb_liaisons++;

        return VRAI; // Retourne VRAI pour indiquer que la liaison a ete ajoutee avec succes.
    }
    return FAUX; // Retourne FAUX si le nombre maximum de liaisons est atteint.
}

/*==========================================================*/
// Fonction: t_pin_sortie_supprimer_lien
// Description: Supprime une liaison entre le pin de sortie et un pin d'entree.
void t_pin_sortie_supprimer_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{
    for (int i = 0; i < pin_sortie->nb_liaisons; i++)
    {
        if (pin_sortie->liaisons[i] == pin_entree)
        {
            // Trouve le pin d'entree dans la liste des liaisons et le supprime.
            for (int j = i; j < pin_sortie->nb_liaisons - 1; j++)
            {
                pin_sortie->liaisons[j] = pin_sortie->liaisons[j + 1];
            }

            // Diminue le nombre de liaisons de 1.
            pin_sortie->nb_liaisons--;
            break;
        }
    }
}

/*==========================================================*/
// Fonction: t_pin_sortie_est_reliee
// Description: Verifie si le pin de sortie est relie a au moins un pin d'entree.
int t_pin_sortie_est_reliee(t_pin_sortie* pin)
{
    return pin->nb_liaisons != 0; // Renvoie VRAI si le pin est relie a au moins un pin d'entree, sinon FAUX.
}

/*=========================================================*/
// Fonction: t_pin_sortie_propager_signal
// Description: Propage la valeur du pin de sortie a tous ses pins d'entree relies.
int t_pin_sortie_propager_signal(t_pin_sortie* pin)
{
    if (pin->valeur == INACTIF || pin->nb_liaisons == 0)
    {
        return 0; // Retourne 0 (FAUX) si la valeur est INACTIF ou s'il n'y a pas de liaisons.
    }

    // Propage la valeur du pin de sortie a tous ses pins d'entree relies.
    for (int i = 0; i < pin->nb_liaisons; i++)
    {
        (pin->liaisons[i])->valeur = pin->valeur;
    }

    return 1; // Retourne 1 (VRAI) pour indiquer que la valeur a ete propagee avec succes.
}

/*==========================================================*/
// Fonction: t_pin_sortie_reset
// Description: Reinitialise la valeur du pin de sortie a INACTIF.
void t_pin_sortie_reset(t_pin_sortie* pin)
{
    pin->valeur = INACTIF; // Reinitialise la valeur du pin de sortie à INACTIF.
}
