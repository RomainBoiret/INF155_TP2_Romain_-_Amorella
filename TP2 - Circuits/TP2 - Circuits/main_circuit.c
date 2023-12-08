/************************************************************************************************************************************************************************************/
/*  Fichier : MAIN_CIRCUIT.C																						                                                                    */
/*  Auteurs : BOIRET Romain   BOIR71300401																		                                                                    */
/*	          LENGA  Amorella LENA91330301																		                                                                    */
/*  Date de creation : <28 / 11 / 2023>																		                                                                        */
/*                                                                                                                                                                                  */
/*  Ce module contient...                                                                                                                                                           */
/************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "t_entree.h"
#include "t_sortie.h"
#include "t_circuit.h"
#include "circuit_IO.h"

#define MANUEL 1
#define CHARGE 2
#define NB_BITS_SIGNAL 3
#define NOM_FICHIER 50

void construire_circuit(t_circuit* circuit);

int main(void)
{
	int choix;
	int valide; //Permet de valider l'entier choisi.
	int signal[NB_BITS_SIGNAL];		//les 3 valeurs pour les 3 entrées
	char* nom_fichier[NOM_FICHIER];
	char* nouv_fichier = "nouv_circuit.txt";
	t_circuit* circuit;   //le circuit complet

	printf("Veuillez choisir un mode de creation de ciruit:\n");
	printf("1 - creation manuel\n");
	printf("2 - a partir d'un fichier\n");

	do
	{
		valide = scanf("%d", &choix);

		if (choix < MANUEL || CHARGE < choix)
		{
			printf("Mauvaise reponse, recommencez!\n");
		}

	} while (choix < MANUEL || CHARGE < choix || valide != 1);

	if (choix == MANUEL)
	{
		circuit = t_circuit_init();   //Création du circuit
		construire_circuit(circuit);

		//Vérification de la validité du circuit
		if (t_circuit_est_valide(circuit))
		{
			printf("Circuit valide!\n");
		}
		else
		{
			printf("Circuit invalide!\n");
		}

		//On définit un signal de 3 bits (111)
		signal[0] = 1;
		signal[1] = 1;
		signal[2] = 1;

		t_circuit_reset(circuit);
		t_circuit_appliquer_signal(circuit, signal, 3);

		if (t_circuit_propager_signal(circuit))
		{
			printf("Signal propage avec succes.\n");
		}
		else
		{
			printf("Erreur lors de la propagation du signal.\n");
		}

		circuit_IO_sauvegarder(nouv_fichier, circuit);
		
		printf("\nLe fichier [nouv_fichier.txt] a ete cree avec succes\n");

		t_circuit_destroy(circuit);
	}

	else if (choix == CHARGE)
	{
		circuit = t_circuit_init();   //Création du circuit

		printf("\nEntrez le nom du fichier-texte source a lire : ");
		scanf("%s", &nom_fichier);

		circuit_IO_charger(nom_fichier, circuit);

		//Vérification de la validité du circuit
		if (t_circuit_est_valide(circuit))
		{
			printf("\nCircuit valide!\n");
		}
		else
		{
			printf("Circuit invalide!\n");
		}

		if (t_circuit_propager_signal(circuit))
		{
			printf("Signal propage avec succes.\n");
		}
		else
		{
			printf("Erreur lors de la propagation du signal.\n");
		}

		circuit_IO_sauvegarder(nouv_fichier, circuit);

		printf("\nLe fichier [nouv_fichier.txt] a ete cree avec succes\n");

		t_circuit_destroy(circuit);
	}

	return EXIT_SUCCESS;
}

void construire_circuit(t_circuit* circuit)
{  //variables locales pour les composantes du circuit
	t_porte* porte_ou;	//les 4 portes
	t_porte* porte_et;
	t_porte* porte_not;
	t_porte* porte_xor;
	t_entree* entree0;	//les 3 entrées
	t_entree* entree1;
	t_entree* entree2;
	t_sortie* sortie0;	//les 2 sorties
	t_sortie* sortie1;

	//Ajout des entrées
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");
	//Ajout des sorties
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	sortie1 = t_circuit_ajouter_sortie(circuit, 1, "S1");

	//Ajout des portes
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU, 0, "P0");
	porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET, 1, "P1");
	porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR, 2, "P2");
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT, 3, "P3");

	//Ajout des liens
	t_porte_relier(porte_ou, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_ou, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 0, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));
	t_porte_relier(porte_not, 0, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
	t_porte_relier(porte_xor, 0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_porte_relier(porte_xor, 1, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_sortie_relier(sortie0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_xor), t_porte_get_pin_sortie(porte_xor));
}
