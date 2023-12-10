/*******************************************************************************************************************************************/
/*  Fichier : MAIN_CIRCUIT.H																							                   */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                           */
/*	          LENGA  Amorella LENA91330301																		                           */
/*  Date de creation : <28 / 11 / 2023>																		                               */
/*                                                                                                                                         */
/*  Ce module contient un ensemble de fonctions destinees a manipuler et a simuler des circuits logiques.                                  */
/*******************************************************************************************************************************************/

#ifndef MAIN_CIRCUIT_H_
#define MAIN_CIRCUIT_H_

#include "table_de_veritee.h"

// Constantes representant les differents modes de creation de circuit manuel ou a partir d'un fichier.
#define MANUEL_1 1  // Mode manuel 1.
#define MANUEL_2 2  // Mode manuel 2.
#define MANUEL_3 3  // Mode manuel 3.
#define CHARGE   4  // Mode de chargement a partir d'un fichier.

// Constantes representant le nombre de bits pour differents signaux.
#define NB_BITS_SIGNAL_M1 3  // Nombre de bits pour le signal du circuit 1.
#define NB_BITS_SIGNAL_M2 4  // Nombre de bits pour le signal du circuit 2.
#define NB_BITS_SIGNAL_M3 3  // Nombre de bits pour le signal du circuit 3.

// Constante definissant la longueur maximale du nom de fichier.
#define NOM_FICHIER 50  // Longueur maximale du nom de fichier.

/*******************************************************************************/
/*                   DECLARATION DES FONCTIONS PUBLIQUES                       */
/*******************************************************************************/

/*
 * Fonction: construire_circuit_m1
 * Auteurs: THE Eric.
 * Tache: Construit un circuit specifique (M1) avec des portes logiques et des entrees/sorties.
 *
 * Parametres: 
 *   - circuit : Un pointeur vers la structure du circuit a construire.
 *               Doit etre non NULL.
 */
void construire_circuit_m1(t_circuit* circuit);

/*
 * Fonction: construire_circuit_m2
 * Auteurs: BOIRET Romain.
 * Tache: Construit un circuit seécifique (M2) avec des portes logiques et des entrees/sorties.
 *
 * Parametres:
 *   - circuit : Un pointeur vers la structure du circuit a construire.
 *               Doit etre non NULL.
 */
void construire_circuit_m2(t_circuit* circuit);

/*
 * Fonction: construire_circuit_m3
 * Auteurs: LENGA Amorella.
 * Tache: Construit un circuit specifique (M3) avec des portes logiques et des entrees/sorties.
 *
 * Parametres: 
 *   - circuit : Un pointeur vers la structure du circuit a construire.
 *               Doit etre non NULL.
 */
void construire_circuit_m3(t_circuit* circuit);


#endif
