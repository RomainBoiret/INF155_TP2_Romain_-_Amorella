/************************************************************************************************************************************************************************************/
/*  Fichier : TABLE_DE_VERITEE.H																						                                                                    */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <28 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#ifndef TABLE_DE_VERITEE_H_
#define TABLE_DE_VERITEE_H_

#include "circuit_IO.h"

int** t_circuit_tdv(const t_circuit* le_circuit);

void afficher_mat_bits(int** mat_bits, const t_circuit* le_circuit);

#endif
