#ifndef FILES_PORTES_H_
#define FILES_PORTES_H_

//definitions pour la librairie de fonctions FILESLIB.CPP
#include "t_porte.h"

typedef struct t_porte t_porte;

#define MAXFILE 20	 // Nombre d'elements maximums que peut contenir une file.

//changer cette declaration pour obtenir une file pour un autre type
typedef t_porte* t_element;

typedef struct {
	t_element file[MAXFILE];
	int       debut, fin;
	int       total;          //le nombre total d'�l�ments dans la file
} t_file;

//fonction pour initialiser une file, la file sera vide apres un appel
//de cette fonction. peut aussi etre utilise pour vider une file.
void initfile(t_file*);

//fonction pour verifier si une file est pleine
int  pleine(const t_file*);

//fonction pour verifier si une file est vide
int  vide(const t_file*);

//fonction pour ajouter un element de plus a la fin d'une file
void ajouterfin(t_file*, t_element);

//fonction pour enlever un element du debut d'une file
void enleverdebut(t_file*, t_element*);
#endif
