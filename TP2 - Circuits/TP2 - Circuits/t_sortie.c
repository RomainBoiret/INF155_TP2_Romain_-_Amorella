/************************************************************************************************************************************************************************************/
/*  Fichier : T_SORTIE.C																						                                                                */
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
#include "t_sortie.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
//Fonction: T_SORTIE_INIT
t_sortie* t_sortie_init(int id, char* nom)
{
	t_sortie* sortie_init;

	sortie_init = (t_sortie*)malloc(sizeof(t_sortie)); 

	sortie_init->id = id;
	sortie_init->nom = nom;

	sortie_init->pin = t_pin_entree_init();

	return sortie_init;
}

/*==========================================================*/
//Fonction: T_SORTIE_DESTROY
void t_sortie_destroy(t_sortie* sortie)
{
	t_pin_entree_destroy(sortie->pin);

	free(sortie);
}

/*==========================================================*/
//Fonction: T_SORTIE_GET_PIN
t_pin_entree* t_sortie_get_pin(t_sortie* sortie)
{
	return sortie->pin;
}

/*==========================================================*/
//Fonction: T_SORTIE_RELIER
int t_sortie_relier(t_sortie* dest, char* nom_composant, const t_pin_sortie* source)
{
	//On fait la liaison.
	t_pin_entree_relier(dest->pin, nom_composant, source);

	if (source == NULL)
		return 0; //Retourne Faux si la liaison n'a pas été effectué.
	
	return 1; //Retourne Vrai si la liaison a bien été effectué.
}

/*==========================================================*/
//Fonction: T_SORTIE_EST_RELIEE
int t_sortie_est_reliee(t_sortie* sortie)
{
	return t_pin_entree_est_reliee(sortie->pin);
}

/*==========================================================*/
//Fonction: T_SORTIE_RESET
void t_sortie_reset(t_sortie* sortie)
{
	return t_pin_entree_reset(sortie->pin);
}

/*==========================================================*/
//Fonction: T_SORTIE_GET_VALEUR
int t_sortie_get_valeur(const t_sortie* sortie)
{
	return t_pin_entree_get_valeur(sortie->pin);
}

/*==========================================================*/
//Fonction: T_SORTIE_GET_ID
int t_sortie_get_id(const t_sortie* sortie)
{
	return sortie->id; 
}

/*==========================================================*/
//Fonction: T_SORTIE_GET_NOM
char* t_sortie_get_nom(const t_sortie* sortie)
{
	return sortie->nom;
}

/*==========================================================*/
//Fonction: T_SORTIE_SERIALISER_LIENS
void t_sortie_serialiser(const t_sortie* sortie, char* resultat)
{
	int infocopie = 0; 

	infocopie += sprintf(resultat, "%d", t_sortie_get_id(sortie));

	infocopie += sprintf(resultat + infocopie, "%s", t_sortie_get_nom(sortie));

	infocopie += sprintf(resultat + infocopie, "%d", t_sortie_get_valeur(sortie));

	resultat[infocopie] = '\0';
}
