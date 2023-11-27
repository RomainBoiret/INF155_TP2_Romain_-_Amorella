/*
TESTER LES ENTREES ET LES SORTIES
Auteur: Eric Th�, 13-11-2023

Programme qui teste l'utilisation des librairies de circuits logique "t_entree" 
(avec "t_pin_sortie") et "t_sortie".  Plusieurs tests unitaires sont faits avec "assert()"
*/
#include <assert.h>
#include "t_entree.h"
#include "t_sortie.h"
#include "t_circuit.h"

int main(void)
{
	//d�claration de variables
	t_entree* entree0;     //les 2 entr�es
	t_entree* entree1;
	t_sortie* sortie0;     //les 2 sorties
	t_sortie* sortie1;
	t_pin_sortie* pin;     //pointeur vers un des pins de sortie (de E0 ou E1)
	t_pin_entree* pin_in;  //pointeur vers un des pins d'entr�e (de S0 ou S1)

	//Cr�er tous les �l�ments dynamiques
	entree0 = t_entree_init(0, "E0");
	entree1 = t_entree_init(1, "E1");
	sortie0 = t_sortie_init(0, "S0");
	sortie1 = t_sortie_init(1, "S1");

	//on teste si les entr�es/sorties sont reli�es
	if (t_entree_est_reliee(entree0) == 0)
		printf("L'entree %s n'est pas reliee!\n", t_entree_get_nom(entree0));

	if (t_entree_est_reliee(entree1) == 0)
		printf("L'entree %s n'est pas reliee!\n", t_entree_get_nom(entree1));

	if (t_sortie_est_reliee(sortie0) == 0)
		printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie0));

	if (t_sortie_est_reliee(sortie1) == 0)
		printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie1));

	//on r�cup�re une r�f�rence sur le pin de sortie de entree0
	pin = t_entree_get_pin(entree0);

	//on connecte entree0 � la sortie0
	t_sortie_relier(sortie0, t_entree_get_nom(entree0), pin);
	assert(t_entree_est_reliee(entree0) == 1);		//test unitaire rapide avec assert()
	assert(t_sortie_est_reliee(sortie0) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie0);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie0), 
		                                                   t_pin_entree_get_lien(pin_in));

	//on connecte entree0 � la sortie1
	t_sortie_relier(sortie1, t_entree_get_nom(entree0), pin);
	assert(t_sortie_est_reliee(sortie1) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie1);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie1),
		                                                   t_pin_entree_get_lien(pin_in));

	//mettre le signal � 1 dans le pin de entree0 et propager le signal
	t_pin_sortie_set_valeur(pin, 1);
	t_entree_propager_signal(entree0);

	//TEST 1: on confirme la r�ception du signal (1) dans les deux sorties
	printf("\nTEST 1: %s (%d) -> %s et %s\n", t_entree_get_nom(entree0), t_entree_get_valeur(entree0),
		                                      t_sortie_get_nom(sortie0), t_sortie_get_nom(sortie1));

	printf("Sortie %d = %d\n", t_sortie_get_id(sortie0), t_sortie_get_valeur(sortie0));
	printf("Sortie %d = %d\n", t_sortie_get_id(sortie1), t_sortie_get_valeur(sortie1));

	//on efface les valeurs des deux sorties
	t_sortie_reset(sortie0);
	assert(t_sortie_get_valeur(sortie0) == INACTIF);   //test unitaire rapide avec assert()

	t_sortie_reset(sortie0);
	assert(t_sortie_get_valeur(sortie0) == INACTIF);   //test unitaire rapide avec assert()

	//on r�cup�re une r�f�rence sur le pin de sortie de entree1
	pin = t_entree_get_pin(entree1);

	//on connecte entree1 � la sortie1
	t_sortie_relier(sortie1, t_entree_get_nom(entree1), pin);
	assert(t_entree_est_reliee(entree1) == 1);		//test unitaire rapide avec assert()
	assert(t_sortie_est_reliee(sortie1) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie1);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie1),
		                                                   t_pin_entree_get_lien(pin_in));

	//mettre le signal � 1 dans le pin de entree1 et propager le signal
	t_pin_sortie_set_valeur(pin, 1);
	t_entree_propager_signal(entree1);

	//mettre le signal � -1 dans le pin de sortie de entree0
	t_entree_reset(entree0);
	assert(t_entree_get_valeur(entree0) == INACTIF);    //test unitaire rapide avec assert()

	//mettre le signal � 0 dans le pin de entree0 et propager le signal
	pin = t_entree_get_pin(entree0);
	t_pin_sortie_set_valeur(pin, 0);
	t_entree_propager_signal(entree0);

	//TEST 2: on confirme la r�ception du signal (1) dans S0 et (0) dans S1
	printf("\nTEST 2: %s (%d) -> %s, %s (%d) -> %s\n", t_entree_get_nom(entree0), t_entree_get_valeur(entree0), 
		                                               t_sortie_get_nom(sortie0),
		                                               t_entree_get_nom(entree1), t_entree_get_valeur(entree1), 
		                                               t_sortie_get_nom(sortie1));

	printf("Sortie %d = %d\n", t_sortie_get_id(sortie0), t_sortie_get_valeur(sortie0));
	printf("Sortie %d = %d\n", t_sortie_get_id(sortie1), t_sortie_get_valeur(sortie1));
	system("pause");

	/******************************************************/
//TESTS ajout�s par nous

//TEST T_PORTE_INIT
/*
	t_porte* porte;
	porte = t_porte_init(0, PORTE_NOT, "P0");
	printf("\nNombres d'entrees de la porte: %d", porte->nb_entrees);
	printf("\n");

	//Set valeurs des entr�es
	t_pin_sortie_set_valeur(entree0->pin, 1);
	t_pin_sortie_set_valeur(entree1->pin, 1);

	//CONNECTER entr�es et la sortie
	int valeur1 = t_porte_relier(porte, 0, "E0", entree0->pin);
	int valeur2 = t_porte_relier(porte, 1, "E1", entree1->pin);
	int valeur3 = t_sortie_relier(sortie0, "S0", porte->sortie);

	//TEST afficher si les liens sont bien faits et si la porte
	//est reli�e
	int porte_reliee = t_porte_est_reliee(porte);
	printf("\nLiaison reussie ou pas: %d", valeur1);
	printf("\nLiaison reussie ou pas: %d", valeur2);
	printf("\nLiaison reussie ou pas: %d", valeur3);
	printf("\nPorte reliee ou pas: %d", porte_reliee);

	//tester de propager le signal
	t_entree_propager_signal(entree0);
	t_entree_propager_signal(entree1);
	t_porte_propager_signal(porte);
	printf("\nValeur recue de la sortie S0: %d", sortie0->pin->valeur);
	printf("\n\n");

	//Test d'acc�s au nom de la porte
	char* nom = t_porte_get_nom(porte);
	printf("Nom: %s", nom);

	//Test acc�s au type
	e_types_portes type = t_porte_get_type(porte);
	printf("\nType: %d", type);
*/
	/******************************************************/

	//lib�rer les 4 allocations
	t_entree_destroy(entree0);
	t_entree_destroy(entree1);
	t_sortie_destroy(sortie0);
	t_sortie_destroy(sortie1);

	//d�claration des variables
	int signal[3];		//les 3 valeurs pour les 3 entr�es
	t_circuit* circuit;   //le circuit complet
	circuit = t_circuit_init();   //Cr�ation du circuit
	//construire_circuit(circuit);

	//V�rification de la validit� du circuit
	if (t_circuit_est_valide(circuit)) {
		printf("Circuit valide!\n");
	}
	else {
		printf("Circuit invalide!\n");
	}

	//On d�finit un signal de 3 bits (111)
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