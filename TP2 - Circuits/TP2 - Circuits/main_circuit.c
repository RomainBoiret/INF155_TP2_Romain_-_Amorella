/********************************************************************************************************************************************************************************************/
/*  Fichier : MAIN_CIRCUIT.C																																								*/
/*  Auteurs : BOIRET Romain   BOIR71300401																																					*/
/*	          LENGA  Amorella LENA91330301																																					*/
/*  Date de creation : <28 / 11 / 2023>																																						*/
/*																																															*/
/*  Ce module contient la fonction main(), ainsi que les definitions des fonctions qui vont construire les circuits.																		*/
/*																																							                                */
/*  But du programme : Ce programme permet de concevoir des circuits logiques combinatoires (CLCs) et d’en calculer la table de verite ainsi que les equations des sorties du circuit.		*/
/********************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "main_circuit.h"

/***************************************************************************************/
/*                                 PROGRAMME PRINCIPAL                                 */
/***************************************************************************************/

int main(void)
{
	int choix; // Permet de saisir le vhoix de l'utilisateur.
	int valide; // Permet de valider l'entier choisi.
	int signal_m1[NB_BITS_SIGNAL_M1]; // Les 3 valeurs pour les 3 entrées du cricuit_1.
	int signal_m2[NB_BITS_SIGNAL_M2]; // Les 4 valeurs pour les 4 entrées du cricuit_2.
	int signal_m3[NB_BITS_SIGNAL_M3]; // Les 3 valeurs pour les 3 entrées du cricuit_3.
	char* nom_fichier[NOM_FICHIER]; // Permet de contenir le nom du fichier contenant le circuit a charger.
	char* nouv_fichier[NOM_FICHIER]; // Permet de contenir le nom du fichier contenant le circuit a sauvegarder.
	t_circuit* circuit;   // Le circuit complet.

	// Interface utilisateur pour choisir le mode de creation de circuit.
	printf("Veuillez choisir un mode de creation de ciruit:\n");
	printf("1 - creation manuel #1\n");
	printf("2 - creation manuel #2\n");
	printf("3 - creation manuel #3\n");
	printf("4 - a partir d'un fichier\n");

	// Boucle de saisie pour verifier et recuperer le choix utilisateur.
	do
	{
		valide = scanf("%d", &choix);

		if (choix < MANUEL_1 || CHARGE < choix)
		{
			printf("Mauvaise reponse, recommencez!\n");
		}

	} while (choix < MANUEL_1 || CHARGE < choix || valide != 1);

	// Switch pour executer les differentes operations en fonction du choix utilisateur.
	switch (choix)
	{
		case MANUEL_1:
		{
			// Creation du circuit manuellement.
			circuit = t_circuit_init();
			construire_circuit_m1(circuit);

			// Verification de la validite du circuit.
			if (t_circuit_est_valide(circuit))
			{
				printf("Circuit valide!\n");
			}
			else
			{
				printf("Circuit invalide!\n");
			}

			// Definition d'un signal de 3 bits (111).
			signal_m1[0] = 1;
			signal_m1[1] = 1;
			signal_m1[2] = 1;

			// Reinitialisation du circuit et application du signal.
			t_circuit_reset(circuit);
			t_circuit_appliquer_signal(circuit, signal_m1, NB_BITS_SIGNAL_M1);

			// Propagation du signal dans le circuit.
			if (t_circuit_propager_signal(circuit))
			{
				printf("Signal propage avec succes.\n");

				// Affichage des sorties apres la propagation du signal.
				for (int i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
				{
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit, i)));
				}
			}
			else
			{
				printf("Erreur lors de la propagation du signal.\n");
			}

			// Creation du fichier.
			printf("\nChoisissez un nom pour le nouveau fichier finissant par .txt : ");
			scanf("%s", &nouv_fichier);

			// Sauvegarde du circuit dans un fichier.
			circuit_IO_sauvegarder(nouv_fichier, circuit);

			// Generation de la table de verite du circuit.
			int** matrice = t_circuit_tdv(circuit);

			// Affichage de la table de verite.
			printf("\nTable de verite du circuit:\n");
			afficher_mat_bits(matrice, circuit);

			// Affichage des equations.
			printf("\nEquations des sorties du circuit (on ecrit le signe '!' devant le nom de l'entree si elle doit etre desactivee):");
			t_circuit_equations(matrice, circuit);

			printf("\n\nLe fichier [%s] a ete cree avec succes\n", nouv_fichier);

			// Liberation de la memoire du circuit.
			t_circuit_destroy(circuit);

			break;
		}

		case MANUEL_2:
		{
			// Creation du circuit manuellement.
			circuit = t_circuit_init();
			construire_circuit_m2(circuit);

			// Verification de la validite du circuit.
			if (t_circuit_est_valide(circuit))
			{
				printf("Circuit valide!\n");
			}
			else
			{
				printf("Circuit invalide!\n");
			}

			// Definition d'un signal de 4 bits (1111).
			signal_m2[0] = 1;
			signal_m2[1] = 1;
			signal_m2[2] = 1;
			signal_m2[3] = 1;

			// Reinitialisation du circuit et application du signal.
			t_circuit_reset(circuit);
			t_circuit_appliquer_signal(circuit, signal_m2, NB_BITS_SIGNAL_M2);

			// Propagation du signal dans le circuit.
			if (t_circuit_propager_signal(circuit))
			{
				printf("Signal propage avec succes.\n");

				// Affichage des sorties apres la propagation du signal.
				for (int i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit, i)));
			}
			else
			{
				printf("Erreur lors de la propagation du signal.\n");
			}

			// Creation du fichier.
			printf("\nChoisissez un nom pour le nouveau fichier finissant par .txt : ");
			scanf("%s", &nouv_fichier);

			// Sauvegarde du circuit dans un fichier.
			circuit_IO_sauvegarder(nouv_fichier, circuit);

			// Generation de la table de verite du circuit.
			int** matrice = t_circuit_tdv(circuit);

			// Affichage de la table de verite.
			printf("\nTable de verite du circuit:\n");
			afficher_mat_bits(matrice, circuit);

			// Affichage des equations.
			printf("\nEquations des sorties du circuit (on ecrit le signe '!' devant le nom de l'entree si elle doit etre desactivee):");
			t_circuit_equations(matrice, circuit);

			printf("\n\nLe fichier [%s] a ete cree avec succes\n", nouv_fichier);

			// Liberation de la memoire du circuit.
			t_circuit_destroy(circuit);

			break;
		}

		case MANUEL_3:
		{
			// Creation du circuit manuellement.
			circuit = t_circuit_init();
			construire_circuit_m3(circuit);

			// Verification de la validite du circuit.
			if (t_circuit_est_valide(circuit))
			{
				printf("Circuit valide!\n");
			}
			else
			{
				printf("Circuit invalide!\n");
			}

			// Definition d'un signal de 3 bits (111).
			signal_m3[0] = 1;
			signal_m3[1] = 1;
    		signal_m3[2] = 1;

			// Reinitialisation du circuit et application du signal.
			t_circuit_reset(circuit);
			t_circuit_appliquer_signal(circuit, signal_m3, NB_BITS_SIGNAL_M3);

			// Propagation du signal dans le circuit.
			if (t_circuit_propager_signal(circuit))
			{
				printf("Signal propage avec succes.\n");

				// Affichage des sorties apres la propagation du signal.
				for (int i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit, i)));
			}
			else
			{
				printf("Erreur lors de la propagation du signal.\n");
			}

			// Creation du fichier.
			printf("\nChoisissez un nom pour le nouveau fichier finissant par .txt : ");
			scanf("%s", &nouv_fichier);

			// Sauvegarde du circuit dans un fichier.
			circuit_IO_sauvegarder(nouv_fichier, circuit);

			// Generation de la table de verite du circuit.
			int** matrice = t_circuit_tdv(circuit);

			// Affichage de la table de verite.
			printf("\nTable de verite du circuit:\n");
			afficher_mat_bits(matrice, circuit);

			// Affichage des equations.
			printf("\nEquations des sorties du circuit (on ecrit le signe '!' devant le nom de l'entree si elle doit etre desactivee):");
			t_circuit_equations(matrice, circuit);

			printf("\n\nLe fichier [%s] a ete cree avec succes\n", nouv_fichier);

			// Liberation de la memoire du circuit.
			t_circuit_destroy(circuit);

			break;
		}
	
		case CHARGE:
		{
			// Creation du circuit a partir d'un fichier.
			circuit = t_circuit_init();

			// Demande a l'utilisateur le nom du fichier à charger.
			printf("\nEntrez le nom du fichier-texte source a lire : ");
			scanf("%s", &nom_fichier);

			// Chargement du circuit depuis le fichier specifie.
			circuit_IO_charger(nom_fichier, circuit);

			// Verification de la validite du circuit charge.
			if (t_circuit_est_valide(circuit))
			{
				printf("\nCircuit valide!\n");
			}
			else
			{
				printf("Circuit invalide!\n");
			}

			// Definition d'un signal de 3 bits (111).
			signal_m1[0] = 1;
			signal_m1[1] = 1;
			signal_m1[2] = 1;

			// Reinitialisation du circuit et application du signal sur les entrees.
			t_circuit_reset(circuit);
			t_circuit_appliquer_signal(circuit, signal_m1, t_circuit_get_nb_entrees(circuit));

			// Propagation du signal dans le circuit.
			if (t_circuit_propager_signal(circuit))
			{
				printf("Signal propage avec succes.\n");

				// Affichage des sorties apres la propagation du signal.
				for (int i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
				{
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit, i)));
				}
			}
			else
			{
				printf("Erreur lors de la propagation du signal.\n");
			}

			// Verification des sorties non reliees.
			for (int i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
			{
				t_sortie* sortie = t_circuit_get_sortie(circuit, i);

				if (t_sortie_est_reliee(sortie) == 0)
				{
					printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie));
				}
			}

			// Verification des portes non reliees.
			for (int i = 0; i < t_circuit_get_nb_portes(circuit); i++)
			{
				t_porte* porte = t_circuit_get_porte(circuit, i);

				if (t_porte_est_reliee(porte) == 0)
				{
					printf("La porte %s n'est pas reliee!\n", t_porte_get_nom(porte));
				}
			}

			// Creation du fichier.
			printf("\nChoisissez un nom pour le nouveau fichier finissant par .txt : ");
			scanf("%s", &nouv_fichier);

			// Sauvegarde du circuit dans un fichier.
			circuit_IO_sauvegarder(nouv_fichier, circuit);

			// Generation de la table de verite du circuit.
			int** matrice = t_circuit_tdv(circuit);

			// Affichage de la table de verite.
			printf("\nTable de verite du circuit:\n");
			afficher_mat_bits(matrice, circuit);

			// Affichage des equations.
			printf("\nEquations des sorties du circuit (on ecrit le signe '!' devant le nom de l'entree si elle doit etre desactivee):");
			t_circuit_equations(matrice, circuit);

			printf("\n\nLe fichier [%s] a ete cree avec succes\n", nouv_fichier);

			// Liberation de la memoire du circuit.
			t_circuit_destroy(circuit);

			break;
		}
	}
	 
	system("pause");
	return EXIT_SUCCESS;
}

/***************************************************************************************/
/*                         DEFINITION DES FONCTIONS PRIVEES                            */
/***************************************************************************************/

/*==========================================================*/
// Fonction: construire_circuit_m1
// Description: Cette fonction construit un circuit avec quatre portes logiques, trois entrees et deux sorties.
// Elle relie les composants du circuit en fonction des operations logiques requises.
void construire_circuit_m1(t_circuit* circuit)
{  
	// Variables locales pour les composantes du circuit.
	// Les 4 portes.
	t_porte* porte_ou;
	t_porte* porte_et;
	t_porte* porte_not;
	t_porte* porte_xor;
	// Les 3 entrees.
	t_entree* entree0;
	t_entree* entree1;
	t_entree* entree2;
	// Les 2 sorties.
	t_sortie* sortie0;
	t_sortie* sortie1;

	// Ajout des entrees.
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");

	// Ajout des sorties.
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	sortie1 = t_circuit_ajouter_sortie(circuit, 1, "S1");

	// Ajout des portes.
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU, 0, "P0");
	porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET, 1, "P1");
	porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR, 2, "P2");
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT, 3, "P3");

	// Ajout des liens pour les entrees.
	t_porte_relier(porte_ou, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_ou, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 0, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));

	// Ajout des liens pour les portes.
	t_porte_relier(porte_not, 0, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
	t_porte_relier(porte_xor, 0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_porte_relier(porte_xor, 1, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));

	// Ajout des liens pour les sorties.
	t_sortie_relier(sortie0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_xor), t_porte_get_pin_sortie(porte_xor));
}

/*==========================================================*/
// Fonction: construire_circuit_m2
// Description: Cette fonction construit un circuit avec quatre portes logiques, quatre entrees et trois sorties.
// Elle relie les composants du circuit en fonction des operations logiques requises.
void construire_circuit_m2(t_circuit* circuit)
{
	// Variables locales pour les composantes du circuit.
	// Les 4 portes.
	t_porte* porte_ou; 
	t_porte* porte_et;
	t_porte* porte_not;
	t_porte* porte_xor;
	// Les 4 entrees.
	t_entree* entree0;
	t_entree* entree1;
	t_entree* entree2;
	t_entree* entree3;
	// Les 3 sorties.
	t_sortie* sortie0;
	t_sortie* sortie1;
	t_sortie* sortie2;

	// Ajout des entrees.
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");
	entree3 = t_circuit_ajouter_entree(circuit, 3, "E3");

	// Ajout des sorties.
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	sortie1 = t_circuit_ajouter_sortie(circuit, 1, "S1");
	sortie2 = t_circuit_ajouter_sortie(circuit, 2, "S2");

	// Ajout des portes.
	porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET, 1, "P0");
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT, 3, "P1");
	porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR, 2, "P2");
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU, 0, "P3");

	// Ajout des liens pour les entrees.
	t_porte_relier(porte_et, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_et, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_ou, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));
	t_porte_relier(porte_xor, 0, t_entree_get_nom(entree2), t_entree_get_pin(entree2));
	t_porte_relier(porte_not, 0, t_entree_get_nom(entree3), t_entree_get_pin(entree3));

	// Ajout des liens pour les portes.
	t_porte_relier(porte_ou, 0, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_porte_relier(porte_xor, 1, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));

	// Ajout des liens pour les sorties.
	t_sortie_relier(sortie0, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
	t_sortie_relier(sortie2, t_porte_get_nom(porte_xor), t_porte_get_pin_sortie(porte_xor));
}

/*==========================================================*/
// Fonction: construire_circuit_m3
// Description: Cette fonction construit un circuit avec trois portes logiques, trois entrees et une sorties.
// Elle relie les composants du circuit en fonction des operations logiques requises.
void construire_circuit_m3(t_circuit* circuit)
{
	// Variables locales pour les composantes du circuit.
	// Les 4 portes.
	t_porte* porte_ou;
	t_porte* porte_not;
	t_porte* porte_xor;
	// Les 3 entrees.
	t_entree* entree0;
	t_entree* entree1;
	t_entree* entree2;
	// Les 2 sorties.
	t_sortie* sortie0;
	
	// Ajout des entrees.
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");

	// Ajout des sorties.
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	
	// Ajout des portes.
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU, 0, "P0");
	porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR, 2, "P2");
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT, 3, "P3");

	// Ajout des liens pour les entrees.
	t_porte_relier(porte_xor, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_xor, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_not, 0, t_entree_get_nom(entree2), t_entree_get_pin(entree2));

	// Ajout des liens pour les portes.
	t_porte_relier(porte_ou, 1, t_porte_get_nom(porte_xor), t_porte_get_pin_sortie(porte_xor));
	t_porte_relier(porte_ou, 0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));

	// Ajout des liens pour les sorties.
	t_sortie_relier(sortie0, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
}
