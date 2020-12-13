#pragma once
#include "constante.h"
#include "Termite.h"
#include <SFML/Audio.hpp>

bool estSimulationFinie(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE]);
bool estConnexe(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], int ligneBrindille, int colonneBrindille);
bool estVide(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], int ligne, int colonne);
void deplacementAleatoire(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], int idTermite, Termite ter[NOMBRE_TERMITE], int passeActuelle);
void ajouteElement(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], Termite ter[NOMBRE_TERMITE]);
void afficheTableau(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE]);
void initialisationTableau(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE]);