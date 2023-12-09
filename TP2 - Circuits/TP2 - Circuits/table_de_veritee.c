/************************************************************************************************************************************************************************************/
/*  Fichier : TABLE_DE_VERITEE.C																						                                                            */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <28 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "table_de_veritee.h"

/***************************************************************************************/
/*                         DECLARATION DES FONCTIONS PRIVEES                           */
/***************************************************************************************/

static int inverser_tab_bits(int tab_bits[], int nb_bits);
static int codage_dec2bin(int nombre, int resultat[]);
static void afficher_tab_bits(const int tab_bits[], int nb_bits);


/***************************************************************************************/
/*                               DEFINITION DES FONCTIONS                              */
/***************************************************************************************/

/*==========================================================*/
//Fonction: T_CIRCUIT_TDV
int** t_circuit_tdv(const t_circuit* le_circuit)
{
    int nb_entrees = t_circuit_get_nb_entrees(le_circuit);
    int nb_sorties = t_circuit_get_nb_sorties(le_circuit);
    int nb_colonnes = nb_entrees + nb_sorties;
    int nb_lignes = pow(2, nb_entrees);

    int** matrice = (int**)malloc(nb_colonnes * sizeof(int*));
    for (int i = 0; i < nb_colonnes; i++)
    {
        matrice[i] = (int*)malloc(nb_lignes * sizeof(int*));
    }

    int signal[MAX_ENTREES];

    for (int i = 0; i < nb_lignes; i++)
    {

    }

    return matrice;
}

/*==========================================================*/
//Fonction "inverser_tab_bits" - Fonction qui inverse les "nb_bits/2" premières valeurs d'un tableau de bits: le premier bit devient la dernier (et inversement), le deuxième devient l'avant dernier, etc. Cette fonction est utilisée par la fonction "codage_dec2bin". 
int inverser_tab_bits(int tab_bits[], int nb_bits)
{
    int i; //Variable temporaire pour la boucle for.

    int temp; //Variable temporaire qui permet de stocker la valeur d'une position du tableau tab_bits[].

    if (nb_bits <= CODAGE_NB_BITS)
    {
        for (i = 0; i < nb_bits / 2; i++)
        {
            temp = tab_bits[i]; //exemple 0 est mise dans la variable temp
            tab_bits[i] = tab_bits[nb_bits - i - 1]; // i devient donc 7
            tab_bits[nb_bits - i - 1] = temp; //et le dernier élément devient donc 
        }

        return 1;
    }
    else
        return 0;
}

/*==========================================================*/
//Fonction "codage_dec2bin" - Le résultat est stocké dans le tableau "resultat" et le nombre de bits utilisés est renvoyé. Le codage du nombre décimal doit se faire en un maximum de CODAGE_NB_BITS (fixée à 8).
int codage_dec2bin(int nombre, int resultat[])
{
    int compt = 0; //Compter chaque fois pour renvoyer le nombre de bits nécessaire pour ce nombre.
    int bin; //Permet destocker le résultat de la division euclidienne du nombre par 2.
    int inverse; //Permet de stocker la valeur retourné par le fonction "inverser_tab_bits".
    int i; //Variable temporaire pour la boucle for.

    //stocker résultat dans le tableau, jusquà 8 bits

    while (nombre > 0)
    {
        bin = nombre % 2; //fais le modulo de 2
        nombre /= 2;
        resultat[compt] = bin; //ajoute ce résultat dans la position
        compt++;
    }

    for (i = compt; i < CODAGE_NB_BITS; i++)
    {
        resultat[i] = 0;
    }

    inverse = inverser_tab_bits(resultat, CODAGE_NB_BITS);

    if (compt > CODAGE_NB_BITS)
    {
        return 0;
    }
    else
        return compt;
}

/*==========================================================*/
//Fonction "afficher_tab_bits" - Affiche un tableau contenant des bits à l'écran. Cette fonction est utilisée pour des fins de test. 
void afficher_tab_bits(const int tab_bits[], int nb_bits)
{
    int i; //Variable temporaire pour la boucle for.

    for (i = 0; i < nb_bits; i++)
    {
        printf("%d", tab_bits[i]);
    }
}
