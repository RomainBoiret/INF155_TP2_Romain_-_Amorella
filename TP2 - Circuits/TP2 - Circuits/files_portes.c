#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "files_portes.h"

//fonction pour initialiser une file, la file sera vide 
void initfile(t_file* f)
{
    f->debut = 0;   // Pointeur de fin est placé au début de la file.
    f->fin = MAXFILE - 1; // Pointeur de fin est positionné à la fin.
    f->total = 0; // Initialisation du nombre d'éléments dans la file à zéro.
}

//fonction pour verifier si une file est pleine
int  pleine(const t_file* f)
{
    return (f->total == MAXFILE);   // Retourne VRAI si le nombre d'éléments n'est pas égal à sa capacité maximale.
}

//fonction pour verifier si une file est vide
int  vide(const t_file* f)
{
    return (f->total == 0); // Retourne VRAI si le nombre d'éléments dans la file est égal à zéro.
}

//fonction pour ajouter un element de plus a la fin d'une file
void ajouterfin(t_file* f, t_element el)
{
    if (pleine(f))
        printf("ERREUR!!! Debordement de file.\n"); // Message d'erreur en cas de file pleine.
    else {
        f->fin = (f->fin + 1) % MAXFILE;    // Si la file n'est pas pleine, ajout d'un élément à la fin.
        f->file[f->fin] = el;
        f->total++; //  Incrémentation du nombre d'éléments.
    }
}

//focntion pour enlever un element du debut d'une file
void enleverdebut(t_file* f, t_element* el)
{
    if (vide(f))
        printf("ERREUR!!! File vide.\n");   // Message d'erreur en cas de file vide.
    else {
        *el = f->file[f->debut];
        f->debut = (f->debut + 1) % MAXFILE;    // Si la file n'est pas vide, extraction d'un élément au début.
        f->total--; //  Décrémentation du nombre d'éléments.
    }
}