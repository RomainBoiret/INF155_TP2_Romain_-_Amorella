/************************************************************************************************************************************************************************************/
/*  Fichier : CRICUIT_IO.H																						                                                                */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <28 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#ifndef CIRCUIT_IO_H_
#define CIRCUIT_IO_H_


#include <stdio.h>

#include "t_circuit.h"




void circuit_IO_sauvegarder(const char* nom_fichier, const  t_circuit* circuit);


void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit);


#endif