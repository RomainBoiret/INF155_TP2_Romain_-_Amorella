/************************************************************************************************************************************************************************************/
/*  Fichier : T_ENTREE.C																						                                                                    */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <14 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
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
//Fonction: T_ENTREE_INIT
t_entree* t_entree_init(int id, char* nom)
{
	t_entree* nouv_entree;

	nouv_entree = (t_entree*)malloc(sizeof(t_entree));

	nouv_entree->id = id;
	nouv_entree->nom = nom;

	nouv_entree->pin = t_pin_sortie_init();

	return nouv_entree;
}

/*==========================================================*/
//Fonction: T_ENTREE_DESTROY
void t_entree_destroy(t_entree* entree)
{
	// Detruire le pin_sortie de l'entree.
	t_pin_sortie_destroy(entree->pin);

	// Liberer la memoire occupé par l'entree.
	free(entree);
}

/*==========================================================*/
//Fonction: T_ENTREE_GET_PIN
t_pin_sortie* t_entree_get_pin(t_entree* entree)
{
	return entree->pin;
}

/*==========================================================*/
//Fonction: T_ENTREE_EST_RELIEE
int t_entree_est_reliee(t_entree* entree)
{
	return t_pin_sortie_est_reliee(entree->pin);
}

/*==========================================================*/
//Fonction: T_ENTREE_RESET
void t_entree_reset(t_entree* entree)
{
	t_pin_sortie_reset(entree->pin);
}

/*==========================================================*/
//Fonction: T_ENTREE_PROPAGER_SIGNAL
int t_entree_propager_signal(t_entree* entree)
{
	return t_pin_sortie_propager_signal(entree->pin);
}

/*==========================================================*/
//Fonction: T_ENTREE_GET_VALEUR
int t_entree_get_valeur(const t_entree* entree)
{
	return t_pin_sortie_get_valeur(entree->pin);
}

/*==========================================================*/
//Fonction: T_ENTREE_GET_ID
int t_entree_get_id(const t_entree* entree)
{
	return entree->id;
}

/*==========================================================*/
//Fonction: T_ENTREE_GET_NOM
char* t_entree_get_nom(const t_entree* entree)
{
	return entree->nom;
}

/*==========================================================*/
//Fonction: T_ENTREE_SERIALISER_LIENS
void t_entree_serialiser(const t_entree* entree, char* resultat)
{
	int infocopied = 0;

	// Copie de l'identifiant numerique de l'entree dans la chaine resultat.
	infocopied += sprintf(resultat, "%d", entree->id);

	// Copie du nom de l'entree dans la chaine resultat.
	infocopied += sprintf(resultat + infocopied, "%s", entree->nom);

	// Copie de la valeur du signal de l'entree dans la chaine resultat.
	infocopied += sprintf(resultat + infocopied, "%d", entree->pin->valeur);

	// Fin de la serialisation en ajoutant un caractere de fin de chaine.
	resultat[infocopied] = '\0';
}
