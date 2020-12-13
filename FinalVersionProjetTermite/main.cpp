#include <iostream>
#include <conio.h> //Pour détecter les touches
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <chrono>
#include "constante.h"
#include "grille.h"
#include "Termite.h"
#include "gui.h"



using namespace std;


/** Fonction principale du programme où la boucle d'affichage se trouve
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @return 0
**/
int main()
{
   
    //MODE POUR LE SPLASH SCREEN
    bool splashScreen = true;

    bool autoLap = false;
    int nbPasseAuto = 600;
    bool runningSimulation = true;


    //Ici les object avec le namespace "sf::"
    sf::RenderWindow window(sf::VideoMode(1500, 900), "Termitiere simulation");
    sf::RectangleShape line; // les lignes pour dessiner la grille et les sections
    sf::Text commands;
    sf::Text logs;
    sf::Text choiceMode;
    sf::Text finSimulation;
    sf::Text nbPasseText;
    sf::Text presentation;
    sf::Font font;
    sf::Text menu;
    sf::Text textIndication;
    sf::Text termiteAvecBrindille;
    sf::Texture termite;
    sf::Texture termitePossesion;
    sf::Sprite termiteSprite;
    sf::Texture logo;
    sf::Sprite logoSprite;
    sf::Texture feuille;
    sf::Sprite feuilleSprite;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::CircleShape pawnMagenta(30, 3);
    sf::CircleShape pawnMagenta2(30, 3);

    pawnMagenta.setFillColor(sf::Color::Magenta);
    pawnMagenta.rotate(90);
    pawnMagenta.setPosition(550,100);

    pawnMagenta2.setFillColor(sf::Color::Magenta);
    pawnMagenta2.rotate(270);
    pawnMagenta2.setPosition(970,158);

    
    
    menu.setFont(font);
    menu.setCharacterSize(25);
    menu.setString("     mode manuel  \n\nMODE AUTOMATIQUE");
    menu.setPosition(670, 300);
    menu.setFillColor(sf::Color::Magenta);
    menu.setStyle(sf::Text::Regular);

    choiceMode.setFont(font);
    choiceMode.setCharacterSize(45);
    choiceMode.setString("mode de simulation");
    choiceMode.setPosition(590,100);
    choiceMode.setStyle(sf::Text::Regular);

    //On défini l'apparence de mes logs (pour nbPasse)
    nbPasseText.setFont(font);
    nbPasseText.setCharacterSize(18);
    nbPasseText.setFillColor(sf::Color::Blue);
    nbPasseText.setPosition(35, 410);
    nbPasseText.setStyle(sf::Text::Regular);

    //On défini l'apparence de mes logs (pour termiteAvecBrindille)
    termiteAvecBrindille.setFont(font);
    termiteAvecBrindille.setCharacterSize(18);
    termiteAvecBrindille.setFillColor(sf::Color::Yellow);
    termiteAvecBrindille.setPosition(35, 480);
    termiteAvecBrindille.setStyle(sf::Text::Regular);
    

    //On défini l'apparence de mes logs
    logs.setFont(font);
    logs.setCharacterSize(18);
    logs.setFillColor(sf::Color::Magenta);
    logs.setPosition(35, 480);
    logs.setStyle(sf::Text::Regular);

    //On défini l'apparence de mes logs (pour finSimulation)
    finSimulation.setFont(font);
    finSimulation.setCharacterSize(35);
    finSimulation.setFillColor(sf::Color::Red);
    finSimulation.setPosition(35, 800);
    finSimulation.setString("FIN DE SIMULATION ! ");
    finSimulation.setStyle(sf::Text::Regular);

    presentation.setFont(font);
    presentation.setCharacterSize(20);
    presentation.setString("Theo Manea - Universite Paris Sud 2020-2021");
    presentation.setPosition(1100, 850);
    presentation.setFillColor(sf::Color::Magenta);
    presentation.setStyle(sf::Text::Regular);

    //On importe la police de caractère
    if (!font.loadFromFile("Fonts/Brookline.ttf"))
    {
        cout << "Oups erreur lors de l'importation de la police de caractere ..." << endl;
    }

    //On importe l'image détouré de la termite
    if (!termite.loadFromFile("Images/termite.png"))
    {
        cout << "Oups erreur lors de l'importation de l'image de la termite ..." << endl;
    }

    //On importe l'image détouré de la termite
    if (!termitePossesion.loadFromFile("Images/termitePossedeBrindille.png"))
    {
        cout << "Oups erreur lors de l'importation de l'image de la termite avec la possesion ..." << endl;
    }

    if (!buffer.loadFromFile("Sounds/eatingSound.wav"))
        return -1;

    
    sound.setBuffer(buffer);
    //sound.play();


    //On importe l'image détouré de la nourriture
    if (!feuille.loadFromFile("Images/feuille.png"))
    {
        cout << "Oups erreur lors de l'importation de l'image de la nourriture ..." << endl;
    }

    //On importe l'image détouré du logo
    if (!logo.loadFromFile("Images/Simul-Ant.png"))
    {
        cout << "Oups erreur lors de l'importation de l'image du logo ..." << endl;
    }
    else
    {
        logoSprite.setTexture(logo);
        logoSprite.setPosition(450, 400);
        logoSprite.setScale(sf::Vector2f(1.25f, 1.25f));
    }

    




    //Variable pour détecter les événements du clavier
    char key;
    int asciiValue;

    //Variable pour compter le nombre de passe
    int nombrePasse = 1;

    //Maintenant on peut créer un tableau de Termite
    Termite ter[NOMBRE_TERMITE];

    //Implantation de mon tableau bidimensionnel
    char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE];

    //On initialise ma termitière avec des espaces
    initialisationTableau(maTermitiere);

    //On lance la création de la termitière
    ajouteElement(maTermitiere, ter);

    cout << "----------------------------- ETAT INITIAL -----------------------------" << endl;

    //On l'affiche pour contrôler
    afficheTableau(maTermitiere);

    cout << "----------------------------- FIN ETAT INITIAL -----------------------------" << endl;

    


    while (window.isOpen())
    {
        string logsString = " "; //Chaîne que l'on va modifier par la suite
        string nbString = " ";

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if ((event.type == sf::Event::KeyPressed) && runningSimulation)
            {
                cout << endl << endl << "----------------------------- Etat a la passe numero : " << nombrePasse << " -----------------------------" << endl;

                if ((event.key.code == sf::Keyboard::Enter) && (autoLap == false))
                {
                    cout <<  " ==> On continue ..."  << endl;

                    //Si on continue, on doit maintenant bouger de façon probabiliste les termites
                    for (int i = 0; i < NOMBRE_TERMITE; i++)
                    {
                        deplacementAleatoire(maTermitiere, i, ter, nombrePasse);
                    }
                    
                    cout << endl;
                    afficheTableau(maTermitiere);

                    //On affiches les données des termites
                    for (int i = 0; i < NOMBRE_TERMITE; i++)
                    {
                        ter[i].displayInfo();
                    }

                    cout << endl << endl << "----------------------------- Fin de la passe numero : " << nombrePasse << " -----------------------------" << endl;
                    nombrePasse++;
                    
                }
                else if (event.key.code == sf::Keyboard::Period)
                {
                    cout  << " ==> Fin du programme ..."  << endl;
                    runningSimulation = false;
                    
                }
                else if (event.key.code == sf::Keyboard::Multiply)
                {
                    cout << " ==> On multiplie par deux" << endl;
                    nbPasseAuto *= 2;
                }
                else if (event.key.code == sf::Keyboard::Divide)
                {
                    cout << " ==> On divise par deux" << endl;
                    nbPasseAuto = nbPasseAuto / 2;

                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                //Nouvelle position stockées dans event.mouseMove.x et event.mouseMove.y
                int x(event.mouseMove.x);
                int y(event.mouseMove.y);

            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                //Position au clic stockée dans event.MouseButton.x et event.MouseButton.y
                int x(event.mouseButton.x);
                int y(event.mouseButton.y);

                

                if ((x >= 696 && x <= 817) && (y >= 300 && y <= 322))
                {
                    cout << "MODE MANUEL" << endl;
                    splashScreen = false;
                }
                else if ((x >= 670 && x <= 845) && (y >= 354 && y <= 373))
                {
                    cout << "MODE AUTOMATIQUE" << endl;

                    
                    cout << "Veuillez saisir le nombre de passe a realiser : " << endl;
                    cin >> nbPasseAuto;
                    splashScreen = false;
                    autoLap = true;

                }

            }
            if (autoLap == true && runningSimulation)
            {
                //Mode automatique ! 
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                cout << "Mode auto" << endl;
                nbPasseAuto--;

                cout << " ==> On continue ..." << endl;

                //Si on continue, on doit maintenant bouger de façon probabiliste les termites
                for (int i = 0; i < NOMBRE_TERMITE; i++)
                {
                    deplacementAleatoire(maTermitiere, i, ter, nombrePasse);
                }

                cout << endl;
                afficheTableau(maTermitiere);

                //On affiches les données des termites
                for (int i = 0; i < NOMBRE_TERMITE; i++)
                {
                    ter[i].displayInfo();
                }

                cout << endl << endl << "----------------------------- Fin de la passe numero : " << nombrePasse << " -----------------------------" << endl;
                nombrePasse++;


            }

        }

        //On actualise le texte nbPasseText
        nbPasseText.setString("Passe numero :  " + to_string(nombrePasse));

        window.clear();
        // C'est ici qu'on doit dessiner les objets 

        //On détermite le nombre de termite avec une brindille
        int nbTermiteAvecBrindille = 0;
        for (int bar = 0; bar <= NOMBRE_TERMITE; bar++)
        {
            if (ter[bar].porteNourriture == true)
            {
                
                nbTermiteAvecBrindille++;
            }
                
        }

        if (splashScreen)
        {
            window.draw(choiceMode);
            window.draw(menu);
            window.draw(pawnMagenta);
            window.draw(pawnMagenta2);
            window.draw(presentation);
            window.draw(logoSprite);
        }
        else
        {

            drawPlateau(window, line, textIndication, font); //On dessine le plateau
            dessineTermiteEtNourritture(maTermitiere, ter, window, termite, termiteSprite, feuille, feuilleSprite, termitePossesion);//On dessine les composants en fonction de la grille
            window.draw(nbPasseText);
            termiteAvecBrindille.setString("termites avec brindilles : " + to_string(nbTermiteAvecBrindille));
            window.draw(termiteAvecBrindille);

        }
        

        
        if(estSimulationFinie(maTermitiere))
            window.draw(finSimulation);
        
        
        if (autoLap)
        {
            if (nbPasseAuto == nombrePasse)
            {
                cout << "Fin de la simulation !! " << endl;
                
            }
        }
        
                

        //Jusque là
        window.display();
    }

    return 0;
}


