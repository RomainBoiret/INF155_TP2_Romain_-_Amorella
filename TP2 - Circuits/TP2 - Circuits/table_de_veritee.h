/*************************************************************************************************************************************************/
/*  Fichier : TABLE_DE_VERITEE.H																						                         */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                 */
/*	          LENGA  Amorella LENA91330301																		                                 */
/*  Date de creation : <28 / 11 / 2023>																		                                     */
/*                                                                                                                                               */
/*  Ce module contient les fonctions necessaires au fonctionnement de TABLE_DE_VERITEE.C.                                                        */
/*************************************************************************************************************************************************/

#ifndef TABLE_DE_VERITEE_H_
#define TABLE_DE_VERITEE_H_

#include "circuit_IO.h"

/*******************************************************************************/
/*                   DECLARATION DES FONCTIONS PUBLIQUES                       */
/*******************************************************************************/

/* Fonction: t_circuit_tdv
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Genere la table de verite du circuit passe en parametre.
 * Parametres :
 *   - le_circuit : Pointeur vers le circuit pour lequel la table de verite doit etre generee.
 * Retour : Pointeur vers une matrice representant la table de verite du circuit.
 */
int** t_circuit_tdv(const t_circuit* le_circuit);

/* Fonction: afficher_mat_bits
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Affiche la matrice de bits du circuit avec ses entrees et ses sorties.
 * Parametres :
 *   - mat_bits : Matrice de bits a afficher representant la table de verite du circuit.
 *   - le_circuit : Pointeur vers le circuit associe a la matrice de bits.
 * Retour : Aucun.
 */
void afficher_mat_bits(int** mat_bits, const t_circuit* le_circuit);


#endif
