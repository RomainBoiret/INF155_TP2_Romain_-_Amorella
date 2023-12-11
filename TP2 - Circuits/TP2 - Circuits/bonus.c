/**************************************************************************************************************************************/
/*  Fichier : BONUS.C																						                          */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                      */
/*	          LENGA  Amorella LENA91330301																		                      */
/*  Date de creation : <28 / 11 / 2023>																		                          */
/*                                                                                                                                    */
/*  Ce module contient l'ensemble des fonctions travaillant sur la table de veritee et les equations des sorties du circuit.          */
/**************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "bonus.h"

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

/*==========================================================*/
// Fonction: t_circuit_equations
// Description: Cette fonction affiche les equations des sorties pour un circuit donné.
// Strategie: La fonction parcourt la matrice mat_bits representant les entrees et les sorties du circuit.
//            Pour chaque sortie du circuit, elle genere l'equation logique correspondante en utilisant les valeurs binaires des entrees.
//            Les valeurs binaires sont interpretees comme les etats des entrees pour lesquelles la sortie donnee est activee (valeur 1).
//            Elle utilise la logique booleenne pour generer les equations de sortie en fonction des entrees activees.
void t_circuit_equations(int** mat_bits, const t_circuit* le_circuit)
{
    int nb_lignes = pow(2, le_circuit->nb_entrees); // Nombre de lignes (combinaisons d'entrees possibles).
    int nb_colonnes = t_circuit_get_nb_entrees(le_circuit) + t_circuit_get_nb_sorties(le_circuit); // Nombre total de colonnes dans la matrice.
    int nb_sorties_act = 0; // Compteur pour le nombre de sorties actives dans une ligne donnee.
    int nb_sorties_inact = 0; // Compteur pour le nombre de sorties inactives dans une ligne donnee.

    // Boucle parcourant chaque sortie du circuit.
    for (int j = 0; j < le_circuit->nb_sorties; j++)
    {
        // Boucle parcourant chaque ligne de la matrice mat_bits.
        for (int i = 0; i < nb_lignes; i++)
        {
            // Verifie si la sortie j est activee dans la ligne i.
            if (mat_bits[i][le_circuit->nb_entrees + j] == 1)
            {
                nb_sorties_act++; // Incremente le compteur de sorties actives.

                if (nb_sorties_act < 2)
                    printf("\nS%d = ", j); // Affiche la sortie si c'est la premiere de l'equation.
                else
                    printf(" + "); // Affiche le signe "+" entre les termes de l'equation.

                // Boucle parcourant les colonnes correspondant aux entrees.
                for (int k = 0; k < (nb_colonnes - le_circuit->nb_sorties); k++)
                {
                    if (mat_bits[i][k] == 1)
                        printf("E%d", k); // Affiche l'entree k si elle est active.
                    else
                        printf("!E%d", k); // Affiche la negation de l'entrée k si elle n'est pas active.

                    if (k != (nb_colonnes - le_circuit->nb_sorties) - 1)
                        printf("*"); // Ajoute le symbole "*" sauf pour le dernier terme de l'equation.
                }
            }

            // Verifie si la sortie j est inactivee dans la ligne i et si le compteur de sorties inactives et a 0.
            else if (mat_bits[i][le_circuit->nb_entrees + j] == INACTIF && nb_sorties_inact == 0)
            {
                nb_sorties_inact++; // Incremente le compteur de sorties inactives.
                printf("\nAucune equations possible pour S%d !", j);
            }
        }

        nb_sorties_act = 0; // Reinitialise le compteur de sorties actives pour la prochaine sortie.
        nb_sorties_inact = 0; // Reinitialise le compteur de sorties inactives pour la prochaine sortie.
    }
}
