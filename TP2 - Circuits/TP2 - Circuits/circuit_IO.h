/*********************************************************************************************************************************************************/
/*  Fichier : CRICUIT_IO.H																						                                         */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                         */
/*	          LENGA  Amorella LENA91330301																		                                         */
/*  Date de creation : <28 / 11 / 2023>																		                                             */
/*                                                                                                                                                       */
/*  Ce module contient les fonctions necessaires au fonctionnement de CIRCUIT_IO.C.                                                                      */
/*********************************************************************************************************************************************************/

#ifndef CIRCUIT_IO_H_
#define CIRCUIT_IO_H_

#include "t_circuit.h"

#define TAILLE 100	//	Nombre de caracteres maximums que peut contenir une chaîne.
#define CONVERT_ASCII 48 // Valeur de conversion d'un caractere en entier.

/*******************************************************************************/
/*                   DECLARATION DES FONCTIONS PUBLIQUES                       */
/*******************************************************************************/

/* Fonction: circuit_IO_sauvegarder
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Sauvegarde les informations du circuit dans un fichier.
 * Parametres :
 *   - nom_fichier : Chemin d'acces du fichier ou les informations du circuit seront sauvegardees.
 *   - circuit : Pointeur vers le circuit dont les informations doivent etre sauvegardees.
 * Retour : Aucun.
 */
void circuit_IO_sauvegarder(const char* nom_fichier, const t_circuit* circuit);

/* Fonction: circuit_IO_charger
 * Auteurs : BOIRET Romain & LENGA Amorella.
 * Tache : Charge les informations du circuit a partir d'un fichier.
 * Parametres :
 *   - chemin_acces : Chemin d'acces du fichier contenant les informations du circuit a charger.
 *   - circuit : Pointeur vers le circuit ou les informations doivent etre chargees.
 * Retour : Aucun.
 */
void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit);


#endif
