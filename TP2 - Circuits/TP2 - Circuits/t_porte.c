/************************************************************************************************************************************************************************************/
/*  Fichier : T_PORTE.C																																							    */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <14 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "t_porte.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
//Fonction: T_PORTE_INIT
t_porte* t_porte_init(int id, e_types_portes type, char* nom)
{

}

/*==========================================================*/
//Fonction: T_PORTE_DESTROY
void t_porte_destroy(t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_CALCULER_SORTIES
void t_porte_calculer_sorties(t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_RELIER
int t_porte_relier(t_porte* dest, int num_entree, char* nom_sortie, const t_pin_sortie* source)
{

}

/*==========================================================*/
//Fonction: T_PORTE_EST_RELIEE
int t_porte_est_reliee(t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_RESET
void t_porte_reset(t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_PROPAGER_SIGNAL
int t_porte_propager_signal(t_porte* porte)
{

}

/************************** Les ACCESSEURS ************************************/

/*==========================================================*/
//Fonction: T_PORTE_GET_ID
int t_porte_get_id(const t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_GET_NOM
char* t_porte_get_nom(const t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_GET_NB_ENTREES
int t_porte_get_nb_entrees(const t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_GET_TYPE
e_types_portes t_porte_get_type(const t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_GET_PIN_ENTREE
t_pin_entree* t_porte_get_pin_entree(const t_porte* porte, int num)
{

}

/*==========================================================*/
//Fonction: T_PORTE_GET_PIN_SORTIE
t_pin_sortie* t_porte_get_pin_sortie(const t_porte* porte)
{

}

/*==========================================================*/
//Fonction: T_PORTE_SERIALISER
void t_porte_serialiser(const t_porte* porte, char* resultat)
{

}
