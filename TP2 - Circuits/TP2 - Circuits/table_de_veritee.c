/**************************************************************************************************************************************/
/*  Fichier : TABLE_DE_VERITEE.C																						              */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                      */
/*	          LENGA  Amorella LENA91330301																		                      */
/*  Date de creation : <28 / 11 / 2023>																		                          */
/*                                                                                                                                    */
/*  Ce module contient l'ensemble des fonctions travaillant sur la table de veritee du circuit.                                       */
/**************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "table_de_veritee.h"

/***************************************************************************************/
/*                         DECLARATION DES FONCTIONS PRIVEES                           */
/***************************************************************************************/

/* Fonction: inverser_tab_bits
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Inverse l'ordre des bits dans un tableau de bits.
 * Parametres :
 *   - tab_bits : Tableau de bits a inverser.
 *   - nb_bits : Nombre de bits dans le tableau.
 *   - le_circuit : Pointeur vers le circuit associe a la fonction.
 * Retour : 1 si l'inversion a reussi, 0 sinon.
 */
static int inverser_tab_bits(int tab_bits[], int nb_bits, const t_circuit* le_circuit);

/* Fonction: codage_dec2bin
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Convertit un nombre decimal en binaire dans un tableau de bits.
 * Parametres :
 *   - nombre : Nombre decimal a convertir en binaire.
 *   - resultat : Tableau pour stocker la representation binaire du nombre.
 *   - le_circuit : Pointeur vers le circuit associe a la fonction.
 * Retour : Le nombre de bits utilises pour representer le nombre en binaire.
 */
static int codage_dec2bin(int nombre, int resultat[], const t_circuit* le_circuit);

/***************************************************************************************/
/*                               DEFINITION DES FONCTIONS                              */
/***************************************************************************************/

/*==========================================================*/
// Fonction: t_circuit_tdv
// Description: Cette fonction genere une table de verite pour un circuit donne en evaluant toutes les combinaisons possibles d'entrees et en stockant les sorties correspondantes.
// Elle utilise les fonctions de manipulation de circuit pour appliquer les signaux et recuperer les valeurs de sortie.
int** t_circuit_tdv(const t_circuit* le_circuit)
{
    int nb_entrees = t_circuit_get_nb_entrees(le_circuit); // Stocke le nombre d'entrees du circuit.
    int nb_sorties = t_circuit_get_nb_sorties(le_circuit); // Stocke le nombre de sorties du circuit.
    int nb_colonnes = nb_entrees + nb_sorties; // Nombre total de colonnes dans la table de verite.
    int nb_lignes = pow(2, nb_entrees); // Nombre total de lignes dans la table de verite.
    int signal[MAX_ENTREES]; // Tableau utilise pour stocker les signaux des entrees.
    int* bits_entrees; // Tableau temporaire utilise pour stocker les bits des entrees.

    // Creer la matrice pour stocker la table de verite.
    int** matrice = (int**)malloc(nb_lignes * sizeof(int*));
    for (int i = 0; i < nb_lignes; i++)
    {
        matrice[i] = (int*)malloc(nb_colonnes * sizeof(int));
    }

    // Generer les valeurs pour chaque combinaison d'entrees.
    for (int i = 0; i < nb_lignes; i++)
    {
        t_circuit_reset(le_circuit);

        // Convertir l'index en binaire pour representer les entrees.
        bits_entrees = (int*)malloc(nb_entrees * sizeof(int*));
        codage_dec2bin(i, bits_entrees, le_circuit);

        // Placer les bits des entrees dans la matrice.
        for (int j = 0; j < nb_entrees; j++)
        {
            matrice[i][j] = bits_entrees[j];
        }

        // Appliquer le signal aux entrees du circuit et propager le signal.
        t_circuit_appliquer_signal(le_circuit, matrice[i], t_circuit_get_nb_entrees(le_circuit));
        t_circuit_propager_signal(le_circuit);

        // Enregistrer les valeurs des sorties dans la matrice.
        for (int j = 0; j < nb_sorties; j++)
        {
            matrice[i][nb_entrees + j] = le_circuit->sorties[j]->pin->valeur;
        }
    }

    return matrice;
}

/*==========================================================*/
// Fonction: inverser_tab_bits
// Description: Cette fonction inverse l'ordre des bits dans un tableau donne jusqu'a la position indiquee.
// Elle est utilisee pour convertir des nombres en binaire.
int inverser_tab_bits(int tab_bits[], int nb_bits, const t_circuit* le_circuit)
{
    int temp; // Variable temporaire utilisee pour stocker temporairement une valeur lors de l'inversion.

    if (nb_bits <= t_circuit_get_nb_entrees(le_circuit)) // Verifie si le nombre de bits est inferieur ou egal au nombre d'entrees du circuit.
    {
        for (int i = 0; i < nb_bits / 2; i++)
        {
            temp = tab_bits[i]; // Stocke temporairement la valeur actuelle.
            tab_bits[i] = tab_bits[nb_bits - 1 - i]; // Echange la valeur actuelle avec la valeur symetrique dans le tableau.
            tab_bits[nb_bits - 1 - i] = temp; // Place la valeur temporairement stockee dans la position symetrique.
        }

        return 1; // Indique que l'inversion des bits a ete realisee avec succes.
    }
    else
        return 0; // Indique que l'inversion des bits n'a pas ete effectuee car le nombre de bits est superieur au nombre d'entrees.
}

/*==========================================================*/
// Fonction: codage_dec2bin
// Description: Cette fonction convertit un nombre decimal en binaire dans un tableau de bits.
// Elle utilise la division et la recuperation du reste pour obtenir la representation binaire du nombre.
int codage_dec2bin(int nombre, int resultat[], const t_circuit* le_circuit)
{
    int bit; // Variable utilisee pour stocker chaque bit du nombre binaire.
    int nb_bits = 0; // Variable pour stocker le nombre total de bits utilises pour representer le nombre.

    // Boucle pour determiner la representation binaire du nombre.
    for (int i = 0; i < t_circuit_get_nb_entrees(le_circuit); i++)
    {
        bit = nombre % 2; // Recupere le bit de poids faible du nombre.
        resultat[i] = bit; // Stocke le bit dans le tableau resultat.

        if (nombre) // Verifie si le nombre n'est pas nul.
        {
            nb_bits++; // Incremente le nombre total de bits utilises.
        }

        nombre /= 2; // Decale le nombre vers la droite pour recuperer le bit suivant.
    }

    inverser_tab_bits(resultat, t_circuit_get_nb_entrees(le_circuit), le_circuit); // Inverse les bits dans le tableau resultat.
    return nb_bits; // Retourne le nombre total de bits utilises.
}

/*==========================================================*/
// Fonction: afficher_mat_bits
// Description: Cette fonction affiche la table de verite (matrice de bits) pour un circuit donne.
// Elle parcourt la matrice et affiche les valeurs des entrees et des sorties.
void afficher_mat_bits(int** mat_bits, const t_circuit* le_circuit)
{
    for (int i = 0; i < (le_circuit->nb_entrees); i++)
    {
        printf("E%d ", i); // Affiche le nom des entrees.
    }

    for (int i = 0; i < (le_circuit->nb_sorties); i++)
    {
        printf("S%d ", i); // Affiche le nom des sorties.
    }

    printf("\n"); // Retour a la ligne.

    // Affiche les valeurs des entrees et sorties pour chaque combinaison possible des entrees.
    for (int i = 0; i < pow(2, t_circuit_get_nb_entrees(le_circuit)); i++)
    {
        for (int j = 0; j < (t_circuit_get_nb_entrees(le_circuit) + t_circuit_get_nb_sorties(le_circuit)); j++)
        {
            printf("%d  ", mat_bits[i][j]); // Affiche la valeur binaire pour chaque entree/sortie.
        }

        printf("\n"); // Retour a la ligne.
    }
}
