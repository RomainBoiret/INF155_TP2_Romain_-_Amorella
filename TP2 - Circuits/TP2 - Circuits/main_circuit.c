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

#define MANUEL_1 1
#define MANUEL_2 2
#define CHARGE   3
#define NB_BITS_SIGNAL_M1 3
#define NB_BITS_SIGNAL_M2 4
#define NOM_FICHIER   50

void construire_circuit_m1(t_circuit* circuit); //AUTEUR: ERIC THE.
void construire_circuit_m2(t_circuit* circuit); //AUTEUR: BOIRET Romain & LENGA Amorella.

int main(void)
{
	int choix;
	int valide; //Permet de valider l'entier choisi.
	int signal_m1[NB_BITS_SIGNAL_M1];		//les 3 valeurs pour les 3 entrées du cricuit_1
	int signal_m2[NB_BITS_SIGNAL_M2];		//les 4 valeurs pour les 4 entrées du cricuit_2
	char* nom_fichier[NOM_FICHIER];
	char* nouv_fichier = "nouv_circuit.txt";
	t_circuit* circuit_1;   //le circuit complet
	t_circuit* circuit_2;   //le circuit complet
	t_circuit* circuit_3;   //le circuit complet

	printf("Veuillez choisir un mode de creation de ciruit:\n");
	printf("1 - creation manuel\n");
	printf("2 - creation manuel #2\n");
	printf("3 - a partir d'un fichier\n");

	do
	{
		valide = scanf("%d", &choix);

		if (choix < MANUEL_1 || CHARGE < choix)
		{
			printf("Mauvaise reponse, recommencez!\n");
		}

	} while (choix < MANUEL_1 || CHARGE < choix || valide != 1);

	switch (choix)
	{
		case MANUEL_1:
		{
			circuit_1 = t_circuit_init();   //Création du circuit
			construire_circuit_m1(circuit_1);

			//Vérification de la validité du circuit
			if (t_circuit_est_valide(circuit_1))
			{
				printf("Circuit valide!\n");
			}
			else
			{
				printf("Circuit invalide!\n");
			}

			//On définit un signal de 3 bits (111)
			signal_m1[0] = 1;
			signal_m1[1] = 1;
			signal_m1[2] = 1;

			t_circuit_reset(circuit_1);
			t_circuit_appliquer_signal(circuit_1, signal_m1, NB_BITS_SIGNAL_M1);

			if (t_circuit_propager_signal(circuit_1))
			{
				printf("Signal propage avec succes.\n");

				for (int i = 0; i < t_circuit_get_nb_sorties(circuit_1); i++)
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit_1, i)));
			}
			else
			{
				printf("Erreur lors de la propagation du signal.\n");
			}

			circuit_IO_sauvegarder(nouv_fichier, circuit_1);

			printf("\nLe fichier [nouv_fichier.txt] a ete cree avec succes\n");

			t_circuit_destroy(circuit_1);

			break;
		}

		case MANUEL_2:
		{
			circuit_2 = t_circuit_init();   //Création du circuit
			construire_circuit_m2(circuit_2);

			//Vérification de la validité du circuit
			if (t_circuit_est_valide(circuit_2))
			{
				printf("Circuit valide!\n");
			}
			else
			{
				printf("Circuit invalide!\n");
			}

			//On définit un signal de 4 bits (1111)
			signal_m2[0] = 1;
			signal_m2[1] = 1;
			signal_m2[2] = 1;
			signal_m2[3] = 1;

			t_circuit_reset(circuit_2);
			t_circuit_appliquer_signal(circuit_2, signal_m2, NB_BITS_SIGNAL_M2);

			if (t_circuit_propager_signal(circuit_2))
			{
				printf("Signal propage avec succes.\n");

				for (int i = 0; i < t_circuit_get_nb_sorties(circuit_2); i++)
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit_2, i)));
			}
			else
			{
				printf("Erreur lors de la propagation du signal.\n");
			}

			circuit_IO_sauvegarder(nouv_fichier, circuit_2);

			printf("\nLe fichier [nouv_fichier.txt] a ete cree avec succes\n");

			t_circuit_destroy(circuit_2);

			break;
		}

		case CHARGE:
		{
			circuit_3 = t_circuit_init();   //Création du circuit

			printf("\nEntrez le nom du fichier-texte source a lire : ");
			scanf("%s", &nom_fichier);

			circuit_IO_charger(nom_fichier, circuit_3);

			//Vérification de la validité du circuit
			if (t_circuit_est_valide(circuit_3))
			{
				printf("\nCircuit valide!\n");
			}
			else
			{
				printf("Circuit invalide!\n");
			}

			//On définit un signal de 3 bits (111)
			signal_m1[0] = 1;
			signal_m1[1] = 1;
			signal_m1[2] = 1;

			t_circuit_reset(circuit_3);
			t_circuit_appliquer_signal(circuit_3, signal_m1, t_circuit_get_nb_entrees(circuit_3));

			if (t_circuit_propager_signal(circuit_3))
			{
				printf("Signal propage avec succes.\n");

				for (int i = 0; i < t_circuit_get_nb_sorties(circuit_3); i++)
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit_3, i)));
			}
			else
			{
				printf("Erreur lors de la propagation du signal.\n");
			}

			for (int i = 0; i < t_circuit_get_nb_sorties(circuit_3); i++)
			{
				t_sortie* sortie = t_circuit_get_sortie(circuit_3, i);

				if (t_sortie_est_reliee(sortie) == 0)
					printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie));
			}

			for (int i = 0; i < t_circuit_get_nb_portes(circuit_3); i++)
			{
				t_porte* porte = t_circuit_get_porte(circuit_3, i);

				if (t_porte_est_reliee(porte) == 0)
					printf("La porte %s n'est pas reliee!\n", t_porte_get_nom(porte));
			}

			circuit_IO_sauvegarder(nouv_fichier, circuit_3);

			printf("\nLe fichier [nouv_fichier.txt] a ete cree avec succes\n");

			t_circuit_destroy(circuit_3);

			break;
		}
	}
	  
	return EXIT_SUCCESS;
}

void construire_circuit_m1(t_circuit* circuit)
{  
	//variables locales pour les composantes du circuit
	//les 4 portes
	t_porte* porte_ou;
	t_porte* porte_et;
	t_porte* porte_not;
	t_porte* porte_xor;
	//les 3 entrées
	t_entree* entree0;
	t_entree* entree1;
	t_entree* entree2;
	//les 2 sorties
	t_sortie* sortie0;
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

	//Ajout des liens pour les entrees
	t_porte_relier(porte_ou, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_ou, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 0, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));

	//Ajout des liens pour les portes
	t_porte_relier(porte_not, 0, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
	t_porte_relier(porte_xor, 0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_porte_relier(porte_xor, 1, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));

	//Ajout des liens pour les sorties
	t_sortie_relier(sortie0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_xor), t_porte_get_pin_sortie(porte_xor));
}

void construire_circuit_m2(t_circuit* circuit)
{
	//variables locales pour les composantes du circuit
	//les 4 portes
	t_porte* porte_ou;
	t_porte* porte_et;
	t_porte* porte_not;
	t_porte* porte_xor;
	//les 4 entrées
	t_entree* entree0;
	t_entree* entree1;
	t_entree* entree2;
	t_entree* entree3;
	//les 3 sorties
	t_sortie* sortie0;
	t_sortie* sortie1;
	t_sortie* sortie2;

	//Ajout des entrées
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");
	entree3 = t_circuit_ajouter_entree(circuit, 3, "E3");

	//Ajout des sorties
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	sortie1 = t_circuit_ajouter_sortie(circuit, 1, "S1");
	sortie2 = t_circuit_ajouter_sortie(circuit, 2, "S2");

	//Ajout des portes
	porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET, 1, "P0");
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT, 3, "P1");
	porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR, 2, "P2");
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU, 0, "P3");

	//Ajout des liens pour les entrees
	t_porte_relier(porte_et, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_et, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_ou, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));
	t_porte_relier(porte_xor, 0, t_entree_get_nom(entree2), t_entree_get_pin(entree2));
	t_porte_relier(porte_not, 0, t_entree_get_nom(entree3), t_entree_get_pin(entree3));

	//Ajout des liens pour les portes
	t_porte_relier(porte_ou, 0, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_porte_relier(porte_xor, 1, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));

	//Ajout des liens pour les sorties
	t_sortie_relier(sortie0, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
	t_sortie_relier(sortie2, t_porte_get_nom(porte_xor), t_porte_get_pin_sortie(porte_xor));
}
