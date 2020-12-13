#pragma once
#pragma once
#include <iostream>

using namespace std;

class Termite
{

	struct Coord
	{
		int ligne;
		int colonne;
	};


public:
	int id;
	string direction;
	Coord coordTermite;
	bool porteNourriture = false;
	int nombrePasseAvecBrindille = 6000;
	int lapSinceLastSet;
	bool alreadyPickedFood = false; //Par défaut on dit que aucune termite n'a pris de brindilles
	//Fonctions
	void displayInfo();



};
