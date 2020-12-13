#include <SFML/Graphics.hpp>
#include "constante.h"
#include "Termite.h"
#include "gui.h"


/** Fonction qui dessine la/les termites et la nourriture
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @param un tableau de termites
* @param l'objet window
* @param la texture de la termite
* @param le sprite de la termite
* @param la texture de la nourriture
* @param le sprite de nourriture
* @param la texture de la termite avec de la nourriture
* @param le sprite de la termite avec de la nourriture
* @param un tableau de termites
* @return void
**/
void dessineTermiteEtNourritture(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], Termite ter[NOMBRE_TERMITE], sf::RenderWindow& window, sf::Texture& termite, sf::Sprite& termiteSprite, sf::Texture& nourriture, sf::Sprite& nourritureSprite, sf::Texture& termitePossesion)
{
    

    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int y = 0; y < TAILLE_GRILLE; y++)
        {
            if ((maTermitiere[i][y] != '*') && (maTermitiere[i][y] != ' '))
            {
                int id = 0;
                //C'est donc une termite, il faut trouver son id
                for (int u = 0; u < NOMBRE_TERMITE; u++)
                {
                    
                    if ((ter[u].coordTermite.ligne == i) && (ter[u].coordTermite.colonne == y))
                    {
                        
                        id = u;
                        

                        //On configure notre Sprite avec la texture de la termite
                        if(ter[id].porteNourriture)
                            termiteSprite.setTexture(termitePossesion);
                        else
                            termiteSprite.setTexture(termite);

                        //On remet la rotation en mode normal
                        termiteSprite.setRotation(0.f);

                        //Maintenant on doit l'orienter en fonction de la direction
                        if (ter[id].direction == "N")
                        {
                            termiteSprite.setRotation(0.f);
                            termiteSprite.setPosition(sf::Vector2f(450 + ter[id].coordTermite.colonne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 8, 100 + ter[id].coordTermite.ligne * (700 / TAILLE_GRILLE)));

                        }
                        else if (ter[id].direction == "NE")
                        {
                            termiteSprite.setRotation(45.f);
                            termiteSprite.setPosition(sf::Vector2f(450 + ter[id].coordTermite.colonne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 4, 100 + ter[id].coordTermite.ligne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 3));

                        }
                        else if (ter[id].direction == "E")
                        {
                            termiteSprite.setRotation(90.f);
                            termiteSprite.setPosition(sf::Vector2f(450 + ter[id].coordTermite.colonne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 3, 100 + ter[id].coordTermite.ligne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 1.5));

                        }
                        else if (ter[id].direction == "SE")
                        {
                            termiteSprite.setRotation(135.f);
                            termiteSprite.setPosition(sf::Vector2f(450 + ter[id].coordTermite.colonne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 1, 100 + ter[id].coordTermite.ligne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 1));

                        }
                        else if (ter[id].direction == "S")
                        {
                            termiteSprite.setRotation(180.f);
                            termiteSprite.setPosition(sf::Vector2f(450 + ter[id].coordTermite.colonne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 2, 100 + ter[id].coordTermite.ligne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE)));

                        }
                        else if (ter[id].direction == "SW")
                        {
                            termiteSprite.setRotation(225.f);
                            termiteSprite.setPosition(sf::Vector2f(450 + ter[id].coordTermite.colonne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 7, 100 + ter[id].coordTermite.ligne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE)));

                        }
                        else if (ter[id].direction == "W")
                        {
                            termiteSprite.setRotation(270.f);
                            termiteSprite.setPosition(sf::Vector2f(450 + ter[id].coordTermite.colonne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 8, 100 + ter[id].coordTermite.ligne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 1));

                        }
                        else if (ter[id].direction == "NW")
                        {
                            termiteSprite.setRotation(315.f);
                            termiteSprite.setPosition(sf::Vector2f(450 + ter[id].coordTermite.colonne * (700 / TAILLE_GRILLE) + (700 / TAILLE_GRILLE) / 8, 100 + ter[id].coordTermite.ligne * (700 / TAILLE_GRILLE)));
                        }

                        // Maintenant on doit redimensionner l'image en fonction de TAILLE_GRILLE

                        //on obtient la resolution de la texture dans un Vector2u
                        sf::Vector2u resol = termite.getSize();

                        //On obtient la longueur
                        int longueurTexture = resol.x;

                        //De même pour la largeur
                        int largeurTexture = resol.y;

                        //On peut redimensionner l'image
                        termiteSprite.setScale(sf::Vector2f(0.15f, 0.15f));

                        //on peut maintenant dessiner
                        window.draw(termiteSprite);
                    }
                }

                   
            }
            else if (maTermitiere[i][y] == '*')
            {
                //On peut donc dessiner une feuille
                //On configure notre Sprite avec la texture de la nourriture
                nourritureSprite.setTexture(nourriture);

                //Maintenant on doit redimensionner l'image en fonction de TAILLE_GRILLE

                //on obtient la resolution de la texture dans un Vector2u
                sf::Vector2u resol = nourriture.getSize();

                //On obtient la longueur
                int longueurTexture = resol.x;

                //De même pour la largeur
                int largeurTexture = resol.y;

                //On peut redimensionner l'image
                nourritureSprite.setScale(sf::Vector2f(0.12f, 0.12f));

                //Maintenant il faut les placer
                nourritureSprite.setPosition(sf::Vector2f(450 + y * (700 / TAILLE_GRILLE), 100 + i * (700 / TAILLE_GRILLE)));

                //on peut dessiner
                window.draw(nourritureSprite);
                
            }
        }
    }

    
}


/** Fonction qui dessine la grille et les indications
* @param l'objet RenderWindow
* @param l'objet line
* @return void
**/
void drawPlateau(sf::RenderWindow& window, sf::RectangleShape& line, sf::Text textIndication, sf::Font font)
{
    //Ligne du sud
    line.setSize(sf::Vector2f(700, 3));
    line.setPosition(450, 100);
    line.setFillColor(sf::Color::Red);
    window.draw(line);

    //Ligne du nord
    line.setSize(sf::Vector2f(700, 3));
    line.setPosition(450, 800);
    line.setFillColor(sf::Color::Red);
    window.draw(line);

    //Ligne de l'ouest
    line.setSize(sf::Vector2f(3, 700));
    line.setPosition(450, 100);
    line.setFillColor(sf::Color::Red);
    window.draw(line);

    //Ligne de l'Est
    line.setSize(sf::Vector2f(3, 700));
    line.setPosition(1150, 100);
    line.setFillColor(sf::Color::Red);
    window.draw(line);

    //Ligne verticale (logs)
    line.setSize(sf::Vector2f(3, 1500));
    line.setPosition(350, 0);
    line.setFillColor(sf::Color::White);
    window.draw(line);

    //Ligne horizontale (consignes)
    line.setSize(sf::Vector2f(350, 3));
    line.setPosition(0, 300);
    line.setFillColor(sf::Color::White);
    window.draw(line);


    //ça c'était les lignes qui était fixe, maintenant on remplit la grille en fonction de la constante TAILLE_GRILLE
    //Boucle pour les lignes horizontales
    /*for (int i = 1; i < TAILLE_GRILLE; i++)
    {
        line.setSize(sf::Vector2f(700, 3));
        line.setPosition(450, (700 / TAILLE_GRILLE) * i + 100);
        line.setFillColor(sf::Color::Red);
        window.draw(line);
    }

    //Boucle pour les lignes verticales
    for (int i = 1; i < TAILLE_GRILLE; i++)
    {
        line.setSize(sf::Vector2f(3, 700));
        line.setPosition((700 / TAILLE_GRILLE) * i + 450, 100);
        line.setFillColor(sf::Color::Red);
        window.draw(line);
    }*/

    //Texte pour les indications
    textIndication.setFont(font);
    textIndication.setString("COMMANDES :");
    textIndication.setCharacterSize(24);
    textIndication.setFillColor(sf::Color::Yellow);
    textIndication.setStyle(sf::Text::Underlined);
    textIndication.setPosition(20, 20);
    window.draw(textIndication);

    textIndication.setFont(font);
    textIndication.setString("TOUCHE ENTREE => POURSUITE (mode manuel) ");
    textIndication.setCharacterSize(18);
    textIndication.setFillColor(sf::Color::Green);
    textIndication.setStyle(sf::Text::Regular);
    textIndication.setPosition(35, 80);
    window.draw(textIndication);

    textIndication.setFont(font);
    textIndication.setString(" * => nbPasse multiplie par deux  ");
    textIndication.setCharacterSize(18);
    textIndication.setFillColor(sf::Color::Cyan);
    textIndication.setStyle(sf::Text::Regular);
    textIndication.setPosition(35, 140);
    window.draw(textIndication);

    textIndication.setFont(font);
    textIndication.setString(" / => nbPasse divise par deux  ");
    textIndication.setCharacterSize(18);
    textIndication.setFillColor(sf::Color::Magenta);
    textIndication.setStyle(sf::Text::Regular);
    textIndication.setPosition(35, 200);
    window.draw(textIndication);

    textIndication.setFont(font);
    textIndication.setString(" . => INTERRUPTION  ");
    textIndication.setCharacterSize(18);
    textIndication.setStyle(sf::Text::Regular);
    textIndication.setFillColor(sf::Color::Red);
    textIndication.setPosition(35, 260);
    window.draw(textIndication);

    //Maintenant on affiche le texte pour la section logs
    textIndication.setFont(font);
    textIndication.setString(" LOGS : ");
    textIndication.setCharacterSize(24);
    textIndication.setFillColor(sf::Color::Yellow);
    textIndication.setPosition(20, 350);
    textIndication.setStyle(sf::Text::Underlined);
    window.draw(textIndication);
}