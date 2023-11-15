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

	//Ce pin contient aucune valeur et pas de liaison.
	nouv_pin_sortie->valeur = INACTIF;
	nouv_pin_sortie->nb_liaisons = 0;

	return nouv_pin_sortie;
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_DESTROY(Destructeur)
void t_pin_sortie_destroy(t_pin_sortie* pin)
{
	free(pin);
	pin = NULL;
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
		//Valeur erron�e
		return;
	}
	pin->valeur = valeur;
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_AJOUTER_LIEN
int t_pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, t_pin_entree* pin_entree)
{	
	int i = 0;
	
    //On vérifie d'abord si on n'excède pas le nombre maximal de liens autorisés
	if (pin_sortie->nb_liaisons < SORTIE_MAX_LIAISONS)
	{  //je supprime la liaison du pin de sortie à lequel elle est présentement liée

		t_pin_sortie_supprimer_lien(pin_sortie, pin_entree);

		/*Là, le pin d'entrée est libre, on peut tout simplement aller dans le tableau de liaison et on pointe
		la prochaine case pour y insérer le pin entrée, on AJOUTE un lien*/

		pin_sortie->liaisons[pin_sortie->nb_liaisons] = pin_entree;
		pin_sortie->nb_liaisons++;

		return 1;
	}

	return 0;
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_SUPPRIMER_LIEN
void t_pin_sortie_supprimer_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{	
	int i;
	int j;
	
	//1.je parcours tout mon tableau de 0 à nb de liaisons que j'ai dans cette sortie 
	for (i = 0; i < pin_sortie->nb_liaisons; i++)
	{
		//si ce lien a été retrouvé entre le pin de sortie et celui d'entrée
		if (pin_sortie->liaisons[i] == pin_entree)
		{
			// Décalage de toutes les liaisons suivantes vers la gauche à PARTIR DE i, i sera donc supprimé.
			for (j = i; j < pin_sortie->nb_liaisons - 1; j++)// à partir de i jusqu'à la dernière case
			{
				//position actuelle a dorénavant la valeur qui était à droite mtn
				pin_sortie->liaisons[j] = pin_sortie->liaisons[j + 1];
			}
		}

		// Diminution du nombre de liaisons de 1
		pin_sortie->nb_liaisons--;
	}
}

/*==========================================================*/
//Fonction: T_PIN_SORTIE_EST_RELIEE
int t_pin_sortie_est_reliee(t_pin_sortie * pin)
{
		return pin->nb_liaisons != NULL;
}

/*=========================================================*/
//Fonction: T_PIN_SORTIE_PROPAGER_SIGNAL
int t_pin_sortie_propager_signal(t_pin_sortie * pin)
{
	int i;

	if (pin->valeur == INACTIF || pin->nb_liaisons == 0)
	{
		return 0; //Retourne Faux si non propagé.
	}

	for (i = 0; i < pin->nb_liaisons; i++)
	{
		pin->liaisons[i] = pin->valeur;
	}

	return 1; //Retourne Vrai si propagé.
}

/*==========================================================*/
//Fonction: Fonction: T_PIN_SORTIE_RESET
void t_pin_sortie_reset(t_pin_sortie * pin)
{
	pin->valeur = INACTIF;
}
