/************************************************************************************************************************************************************************************/
/*  Fichier : T_ENTREE.C																						                                                                    */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <14 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient des fonctions destinées à manipuler une structure de données représentant une entrée (t_entree).                                                             */
/************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "t_entree.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
// Fonction: t_entree_init
// Description: Initialise une entree avec un identifiant, un nom et un pin de sortie associe.
t_entree* t_entree_init(int id, char* nom)
{
    t_entree* nouv_entree; // Variable pour stocker la nouvelle entree.

    nouv_entree = (t_entree*)malloc(sizeof(t_entree)); // Allocation de mémoire pour l'entrée.

    nouv_entree->id = id; // Attribution de l'identifiant a l'entree.
    nouv_entree->nom = _strdup(nom); // Attribution du nom a l'entree en copiant la chaine.

    nouv_entree->pin = t_pin_sortie_init(); // Initialisation du pin de sortie associe a l'entree.

    return nouv_entree; // Retourne la nouvelle entree initialisee.
}

/*==========================================================*/
// Fonction: t_entree_destroy
// Description: Libere la memoire allouee pour une entree, y compris le pin de sortie associe.
void t_entree_destroy(t_entree* entree)
{
    // Liberation de la memoire allouee pour le pin de sortie de l'entree.
    t_pin_sortie_destroy(entree->pin);

    free(entree); // Liberation de la memoire allouee pour l'entree.
}

/*==========================================================*/
// Fonction: t_entree_get_pin
// Description: Recupere le pin de sortie associe a une entree.
t_pin_sortie* t_entree_get_pin(t_entree* entree)
{
    return entree->pin; // Renvoie le pin de sortie associe a l'entree.
}

/*==========================================================*/
// Fonction: t_entree_est_reliee
// Description: Verifie si l'entree est reliee a un pin de sortie.
int t_entree_est_reliee(t_entree* entree)
{
    return t_pin_sortie_est_reliee(entree->pin); // Renvoie VRAI si l'entree est reliee, sinon FAUX.
}

/*==========================================================*/
// Fonction: t_entree_reset
// Description: Reinitialise la valeur du pin de sortie associe a l'entree.
void t_entree_reset(t_entree* entree)
{
    t_pin_sortie_reset(entree->pin); // Reinitialise le pin de sortie associe à l'entree.
}

/*==========================================================*/
// Fonction: t_entree_propager_signal
// Description: Propage la valeur du pin de sortie associe a l'entree.
int t_entree_propager_signal(t_entree* entree)
{
    return t_pin_sortie_propager_signal(entree->pin); // Propage la valeur du pin de sortie et renvoie le resultat.
}

/*==========================================================*/
// Fonction: t_entree_get_valeur
// Description: Recupere la valeur actuelle du pin de sortie associe a l'entree.
int t_entree_get_valeur(const t_entree* entree)
{
    return t_pin_sortie_get_valeur(entree->pin); // Renvoie la valeur actuelle du pin de sortie.
}

/*==========================================================*/
// Fonction: t_entree_get_id
// Description: Recupere l'identifiant de l'entree.
int t_entree_get_id(const t_entree* entree)
{
    return entree->id; // Renvoie l'identifiant de l'entree.
}

/*==========================================================*/
// Fonction: t_entree_get_nom
// Description: Recupere le nom de l'entree.
char* t_entree_get_nom(const t_entree* entree)
{
    return entree->nom; // Renvoie le nom de l'entree.
}

/*==========================================================*/
// Fonction: t_entree_serialiser
// Description: Serialise les informations de l'entree dans une chaine de caracteres.
void t_entree_serialiser(const t_entree* entree, char* resultat)
{
    int infocopie = 0; // Variable pour suivre la position de copie dans le resultat.

    // Copie de l'identifiant de l'entree dans la chaine resultat.
    infocopie += sprintf(resultat, "%d ", t_entree_get_id(entree));

    // Copie du nom de l'entree dans la chaine resultat avec un saut de ligne.
    infocopie += sprintf(resultat + infocopie, "%s\n", t_entree_get_nom(entree));

    // Ajout d'un caractere de fin de chaine.
    resultat[infocopie] = '\0';
}
