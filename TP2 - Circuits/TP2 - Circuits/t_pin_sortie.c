/************************************************************************************************************************************************************************************/
/*  Fichier : T_PIN_SORTIE.C																						                                                                */
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
#include "t_pin_sortie.h"

/***************************************************************************************/
/*                             DEFINITION DES FONCTIONS                                */
/***************************************************************************************/

/*==========================================================*/
//Fonction: T_PIN_SORTIE_INIT(constructeur)
t_pin_sortie* t_pin_sortie_init(void)
{
	t_pin_sortie* nouv_pin_sortie;

	nouv_pin_sortie = (t_pin_sortie*)malloc(sizeof(t_pin_sortie));

	nouv_pin_sortie->valeur = INACTIF;
	
	nouv_pin_sortie->nb_liaisons = 0;

	for (int i = 0; i < SORTIE_MAX_LIAISONS; i++)
	{
		nouv_pin_sortie->liaisons[i] = NULL;
	}

	return nouv_pin_sortie;
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_DESTROY(Destructeur)
void t_pin_sortie_destroy(t_pin_sortie* pin)
{
	free(pin);
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_GET_VALEUR (Accesseur)
int t_pin_sortie_get_valeur(t_pin_sortie* pin)
{
	return pin->valeur;
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_SET_VALEUR (Mutateur)
void t_pin_sortie_set_valeur(t_pin_sortie* pin, int valeur)
{
	if (valeur < INACTIF || valeur > 1)
	{
		//Valeur erronee
		return;
	}
	pin->valeur = valeur;
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_AJOUTER_LIEN
int t_pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, t_pin_entree* pin_entree)
{
	if (pin_sortie->nb_liaisons < SORTIE_MAX_LIAISONS)
	{
		pin_sortie->liaisons[pin_sortie->nb_liaisons] = pin_entree;
		pin_sortie->nb_liaisons++;

		return VRAI;
	}
	return FAUX;
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_SUPPRIMER_LIEN
void t_pin_sortie_supprimer_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{
	for (int i = 0; i < pin_sortie->nb_liaisons; i++)
	{
		if (pin_sortie->liaisons[i] == pin_entree) //; <-- JE T'AI TROUVE MOUHAHAHAHAHA
		{
			for (int j = i; j < pin_sortie->nb_liaisons - 1; j++)
			{
				pin_sortie->liaisons[j] = pin_sortie->liaisons[j + 1];
			}

			// Diminution du nombre de liaisons de 1
			pin_sortie->nb_liaisons--;
			break;
		}
	}
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_EST_RELIEE
int t_pin_sortie_est_reliee(t_pin_sortie * pin)
{
	return pin->nb_liaisons != 0;
}

/*=========================================================*/
//Fonction: T_PIN_SORTIE_PROPAGER_SIGNAL
int t_pin_sortie_propager_signal(t_pin_sortie * pin)
{
	if (pin->valeur == INACTIF || pin->nb_liaisons == 0)
	{
		return 0; //Retourne Faux si non propage.
	}

	for (int i = 0; i < pin->nb_liaisons; i++)
	{
		pin->liaisons[i]->valeur = pin->valeur;
	}

	return VRAI; //Retourne Vrai si propage.
}

/*==========================================================*/
//Fonction: Fonction: T_PIN_SORTIE_RESET
void t_pin_sortie_reset(t_pin_sortie * pin)
{
	pin->valeur = INACTIF;
}
