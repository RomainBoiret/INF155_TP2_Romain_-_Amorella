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

static int inverser_tab_bits(int tab_bits[], int nb_bits, const t_circuit* le_circuit);
static int codage_dec2bin(int nombre, int resultat[], const t_circuit* le_circuit);


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
    int signal[MAX_ENTREES];
    int* bits_entrees;

    //Créer la matrice
    int** matrice = (int**)malloc(nb_lignes * sizeof(int*));
    for (int i = 0; i < nb_lignes; i++)
    {
        matrice[i] = (int*)malloc(nb_colonnes * sizeof(int));
    }

    //Mettre les valeur de toutes les combinaisons d'entrées
    t_circuit_reset(le_circuit);

    for (int i = 0; i < nb_lignes; i++)
    {
        //Traduire la ligne en binaire
        bits_entrees = (int*)malloc(nb_entrees * sizeof(int*));
        codage_dec2bin(i, bits_entrees, le_circuit);

        //mettre les bits des entrées dans le tableau
        for (int j = 0; j < nb_entrees; j++)
        {
            matrice[i][j] = bits_entrees[j];
        }

        t_circuit_appliquer_signal(le_circuit, matrice[i], t_circuit_get_nb_entrees(le_circuit));
        t_circuit_propager_signal(le_circuit);

        //écrire les valeurs des sorties dans la matrice
        for (int j = 0; j < nb_sorties; j++)
        {
            matrice[i][nb_entrees + j] = le_circuit->sorties[j]->pin->valeur;
        }
    }

    return matrice;
}

/*==========================================================*/
//Fonction: INVERSER_TAB_BITS
int inverser_tab_bits(int tab_bits[], int nb_bits, const t_circuit* le_circuit)
{
    int temp;

    if (nb_bits <= t_circuit_get_nb_entrees(le_circuit))
    {
        for (int i = 0; i < nb_bits / 2; i++)
        {
            temp = tab_bits[i];
            tab_bits[i] = tab_bits[nb_bits - 1 - i];
            tab_bits[nb_bits - 1 - i] = temp;
        }

        return 1;
    }
    else
        return 0;
}

/*==========================================================*/
//Fonction: CODAGE_DEC2BIN
int codage_dec2bin(int nombre, int resultat[], const t_circuit* le_circuit)
{
    int bit;
    int nb_bits = 0;

    //Pour déterminer si la case du tableau contient un 1 ou un 0
    for (int i = 0; i < t_circuit_get_nb_entrees(le_circuit); i++)
    {
        bit = nombre % 2;
        resultat[i] = bit;

        //Pour trouver le nombre de bits utilisés pour écrire la valeur en binaire
        if (nombre)
        {
            nb_bits++;
        }

        nombre /= 2;
    }

    inverser_tab_bits(resultat, t_circuit_get_nb_entrees(le_circuit), le_circuit);
    return nb_bits;
}

/*==========================================================*/
//Fonction: AFFICHER_MAT_BITS
void afficher_mat_bits(int ** mat_bits, const t_circuit* le_circuit)
{
    for (int i = 0; i < (le_circuit->nb_entrees); i++)
    {
        printf("E%d ", i);
    }

    for (int i = 0; i < (le_circuit->nb_sorties); i++)
    {
        printf("S%d ", i);
    }

    printf("\n");

    for (int i = 0; i < pow(2, t_circuit_get_nb_entrees(le_circuit)); i++)
    {
        for (int j = 0; j < (t_circuit_get_nb_entrees(le_circuit) + t_circuit_get_nb_sorties(le_circuit)); j++)
        {
            printf("%d  ", mat_bits[i][j]);
        }

        printf("\n");
    }
}
