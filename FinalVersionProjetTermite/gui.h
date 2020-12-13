#pragma once
#include "Termite.h"


void dessineTermiteEtNourritture(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], Termite ter[NOMBRE_TERMITE], sf::RenderWindow& window, sf::Texture& termite, sf::Sprite& termiteSprite, sf::Texture& nourriture, sf::Sprite& nourritureSprite, sf::Texture& termitePossesion);
void drawPlateau(sf::RenderWindow& window, sf::RectangleShape& line, sf::Text textIndication, sf::Font font);