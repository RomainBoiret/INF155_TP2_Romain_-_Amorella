/*******************************************************************************************************************************************************/
/*  Fichier : T_SORTIE.C																						                                       */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                       */
/*	          LENGA  Amorella LENA91330301																		                                       */
/*  Date de creation : <14 / 11 / 2023>																		                                           */
/*                                                                                                                                                     */
/*  Ce module contient un ensemble de fonctions destinees a manipuler une structure de donnees appelee t_sortie.                                       */
/*******************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "t_sortie.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
// Fonction: t_sortie_init
// Description: Initialise une sortie avec un identifiant et un nom.
t_sortie* t_sortie_init(int id, char* nom)
{
    t_sortie* sortie_init; // Variable utilisee pour stocker la sortie initialisee.

    sortie_init = (t_sortie*)malloc(sizeof(t_sortie)); // Allocation de memoire pour la sortie.

    sortie_init->id = id; // Attribution de l'identifiant a la sortie.
    sortie_init->nom = _strdup(nom); // Attribution du nom a la sortie en copiant la chaine.

    sortie_init->pin = t_pin_entree_init(); // Initialisation du pin de sortie.

    return sortie_init; // Retourne la sortie initialisee.
}

/*==========================================================*/
// Fonction: t_sortie_destroy
// Description: Libere la memoire allouee pour une sortie.
void t_sortie_destroy(t_sortie* sortie)
{
    t_pin_entree_destroy(sortie->pin); // Liberation de la memoire allouee pour le pin d'entree de la sortie.

    free(sortie); // Liberation de la memoire allouee pour la sortie.
}

/*==========================================================*/
// Fonction: t_sortie_get_pin
// Description: Recupere le pin d'entree associe a une sortie.
t_pin_entree* t_sortie_get_pin(t_sortie* sortie)
{
    return sortie->pin; // Retourne le pin d'entree de la sortie.
}

/*==========================================================*/
// Fonction: t_sortie_relier
// Description: Relie la sortie a un composant via un pin de sortie.
int t_sortie_relier(t_sortie* dest, char* nom_composant, const t_pin_sortie* source)
{
    // On fait la liaison.
    t_pin_entree_relier(dest->pin, nom_composant, source);

    if (source == NULL)
        return FAUX; // Retourne FAUX si la source est nulle.

    return VRAI; // Retourne VRAI si la liaison est effectuee.
}

/*==========================================================*/
// Fonction: t_sortie_est_reliee
// Description: Verifie si la sortie est reliee a un composant.
int t_sortie_est_reliee(t_sortie* sortie)
{
    return t_pin_entree_est_reliee(sortie->pin); // Verifie si le pin d'entree de la sortie est relie.
}

/*==========================================================*/
// Fonction: t_sortie_reset
// Description: Reinitialise la sortie.
void t_sortie_reset(t_sortie* sortie)
{
    t_pin_entree_reset(sortie->pin); // Reinitialise le pin d'entree de la sortie.
}

/*==========================================================*/
// Fonction: t_sortie_get_valeur
// Description: Recupere la valeur de la sortie.
int t_sortie_get_valeur(const t_sortie* sortie)
{
    return t_pin_entree_get_valeur(sortie->pin); // Recupere la valeur du pin d'entree de la sortie.
}

/*==========================================================*/
// Fonction: t_sortie_get_id
// Description: Recupere l'identifiant de la sortie.
int t_sortie_get_id(const t_sortie* sortie)
{
    return sortie->id; // Recupere et retourne l'identifiant de la sortie.
}

/*==========================================================*/
// Fonction: t_sortie_get_nom
// Description: Recupere le nom de la sortie.
char* t_sortie_get_nom(const t_sortie* sortie)
{
    return sortie->nom; // Recupere et retourne le nom de la sortie.
}

/*==========================================================*/
// Fonction: t_sortie_serialiser
// Description: Serialise les informations de la sortie dans une chaine de caracteres.
void t_sortie_serialiser(const t_sortie* sortie, char* resultat)
{
    int infocopie = 0; // Variable utilisee pour suivre la position de copie dans le resultat.

    // Copie de l'identifiant dans le resultat.
    infocopie += sprintf(resultat, "%d ", t_sortie_get_id(sortie));

    // Copie du nom dans le resultat avec un saut de ligne.
    infocopie += sprintf(resultat + infocopie, "%s\n", t_sortie_get_nom(sortie));

    // Fin de la serialisation en ajoutant un caractere de fin de chaîne.
    resultat[infocopie] = '\0';
}
