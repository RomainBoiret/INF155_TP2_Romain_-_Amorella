/************************************************************************************************************************************************************************************/
/*  Fichier : Test_circuit_portes.C																						                                                                    */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <21 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "t_circuit.h"

int main(void)
{	//déclaration des variables
	int signal[3];		//les 3 valeurs pour les 3 entrées
	t_circuit* circuit;   //le circuit complet
	circuit = t_circuit_init();   //Création du circuit
	construire_circuit(circuit);

	//Vérification de la validité du circuit
	if (t_circuit_est_valide(circuit)) {
		printf("Circuit valide!\n");
	}
	else {
		printf("Circuit invalide!\n");
	}

	//On définit un signal de 3 bits (111)
	signal[0] = 1;
	signal[1] = 1;
	signal[2] = 1;
	t_circuit_reset(circuit);
	t_circuit_appliquer_signal(circuit, signal, 3);

	if (t_circuit_propager_signal(circuit)) {
		printf("Signal propage avec succes.\n");
		printf("Sortie 0: %d\n", t_sortie_get_valeur(sortie0));
		printf("Sortie 1: %d\n", t_sortie_get_valeur(sortie1));
	}
	else  printf("Erreur lors de la propagation du signal.\n");

	t_circuit_destroy(circuit);
	system("pause");
	return EXIT_SUCCESS;
}
