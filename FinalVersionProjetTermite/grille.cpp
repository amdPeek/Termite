#include <iostream>
#include <string>
#include <typeinfo>
#include <time.h>
#include <SFML/Audio.hpp>
#include <vector>
#include "constante.h"
#include "Termite.h"

using namespace std;



/** Fonction qui détermine si la simulation est finie
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @return un booleen
**/
bool estSimulationFinie(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE])
{
    
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int y = 0; y < TAILLE_GRILLE; y++)
        {
            //Il faut gérer les cas limites

            if ((i - 1 <= 0) && ((y != 0) && (y != TAILLE_GRILLE)) )
            {
                if ( (maTermitiere[i][y-1] == ' ') || (maTermitiere[i][y+1] == ' ') || (maTermitiere[i+1][y] == ' ') || (maTermitiere[i+1][y+1] == ' ') || (maTermitiere[i+1][y-1] == ' '))
                {
                    //Si on satisfait cette condition c'est que la brindille est seule
                    return false;
                }
                
            }
            else if ((y - 1 <= 0) && ((i != 0) && (i != TAILLE_GRILLE)) )
            {
                if ((maTermitiere[i-1][y] == ' ') || (maTermitiere[i+1][y] == ' ') || (maTermitiere[i][y+1] == ' ') || (maTermitiere[i+1][y + 1] == ' ') || (maTermitiere[i-1][y+1] == ' '))
                {
                    //Si on satisfait cette condition c'est que la brindille est seule
                    return false;
                }
            }
            else if ((i + 1 >= TAILLE_GRILLE) && ((y != 0) && (y != TAILLE_GRILLE)))
            {
                if ((maTermitiere[i][y-1] == ' ') || (maTermitiere[i][y+1] == ' ') || (maTermitiere[i-1][y] == ' ') || (maTermitiere[i-1][y+1] == ' ') || (maTermitiere[i-1][y-1] == ' '))
                {
                    //Si on satisfait cette condition c'est que la brindille est seule
                    return false;
                }
            }
            else if ((y + 1 >= TAILLE_GRILLE) && ((i != 0) && (i != TAILLE_GRILLE)))
            {
                if ((maTermitiere[i-1][y] == ' ') || (maTermitiere[i+1][y] == ' ') || (maTermitiere[i][y-1] == ' ') || (maTermitiere[i - 1][y - 1] == ' ') || (maTermitiere[i+1][y - 1] == ' '))
                {
                    //Si on satisfait cette condition c'est que la brindille est seule
                    return false;
                }
            }
            else if (i == 0 && y == 0)
            {
                //Coin Nord Ouest
                if ((maTermitiere[0][1] == ' ') || (maTermitiere[1][0] == ' ') || (maTermitiere[1][1] == ' '))
                {
                    return false;
                }
            }
            else if (i == 0 && (y == TAILLE_GRILLE - 1) )
            {
                //Coin Nord Est
                if ((maTermitiere[0][TAILLE_GRILLE - 1 ] == ' ') || (maTermitiere[1][TAILLE_GRILLE - 1] == ' ') || (maTermitiere[1][TAILLE_GRILLE - 2] == ' '))
                {
                    return false;
                }
            }
            else if ( (i == TAILLE_GRILLE - 1)  && (y == 0) )
            {
                //Coin Sud ouest
                if ((maTermitiere[TAILLE_GRILLE - 1][0] == ' ') || (maTermitiere[TAILLE_GRILLE - 2][0] == ' ') || (maTermitiere[TAILLE_GRILLE - 1][1] == ' '))
                {
                    return false;
                }
            }
            else if ((i == TAILLE_GRILLE - 1) && (y == TAILLE_GRILLE - 1))
            {
                //Coin Sud Est
                if ((maTermitiere[TAILLE_GRILLE - 1][TAILLE_GRILLE - 1] == ' ') || (maTermitiere[TAILLE_GRILLE - 1][TAILLE_GRILLE - 2] == ' ') || (maTermitiere[TAILLE_GRILLE - 2][TAILLE_GRILLE - 1] == ' '))
                {
                    return false;
                }
            }
            else
            {
                //On est pas aux extrêmités du terrain donc on peut ne pas se soucier des index
                if ( (maTermitiere[i][y] == ' ') || (maTermitiere[i][y+1] == ' ') || (maTermitiere[i][y-1] == ' ') || (maTermitiere[i+1][y] == ' ') || (maTermitiere[i-1][y] == ' ') || (maTermitiere[i+1][y+1] == ' ') || (maTermitiere[i-1][y+1] == ' ') || (maTermitiere[i-1][y-1] == ' ') || (maTermitiere[i+1][y-1] == ' ')  )
                {
                    return false;
                }
            }
        }
    }


    return true;
}

/** Fonction qui détermine si une brindille est connexe avec d'autres brindilles (existence d'un tas autrement dit)
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @param la ligne de la brindille
* @param la colonne de la brindille
* @return un booleen
**/
bool estConnexe(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], int ligneBrindille, int colonneBrindille)
{
    if ((maTermitiere[ligneBrindille + 1][colonneBrindille] == '*') || (maTermitiere[ligneBrindille - 1][colonneBrindille] == '*') || (maTermitiere[ligneBrindille][colonneBrindille + 1] == '*') || (maTermitiere[ligneBrindille][colonneBrindille - 1] == '*') || (maTermitiere[ligneBrindille + 1][colonneBrindille + 1] == '*') || (maTermitiere[ligneBrindille + 1][colonneBrindille - 1] == '*') || (maTermitiere[ligneBrindille - 1][colonneBrindille + 1] == '*') || (maTermitiere[ligneBrindille - 1][colonneBrindille - 1] == '*'))
        return false;
    else
        return true;
    
}

/** Fonction qui détermine si la case devant un termite est disponible (qu'elle soit vide et qu'il n'y ait pas de termite, mais peut avoir une brindille )
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @param la ligne du termite
* @param la colonne du termite
* @return un booleen
**/
bool estVide(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], int ligne, int colonne)
{
    if ((ligne < 0 || ligne >= TAILLE_GRILLE) || (colonne < 0 || colonne >= TAILLE_GRILLE))
    {
        //Cela signifie qu'on sort de la grille
        return false;
    }
    else
    {
        //Sinon on peut continuer car ces coordonnées sont à l'intérieur de ma grille
        if (maTermitiere[ligne][colonne] == ' ')
            return true;
        else if( (maTermitiere[ligne][colonne] == '\\') || (maTermitiere[ligne][colonne] == '/') || (maTermitiere[ligne][colonne] == '|') || (maTermitiere[ligne][colonne] == '-'))
        {
            cout << endl << endl << "J'ai rencontre un termite sur ma direction donc je bouge pas." << endl << endl;
            return false;
        }

    }


}


/** Fonction qui donnent à chaque termite une direction déterminée de façon aléatoire
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @param l'id du termite
* @param le tableau de termite
* @param le numéro du tour actuel
* @return void
**/
void deplacementAleatoire(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], int idTermite, Termite ter[NOMBRE_TERMITE], int passeActuelle)
{
    //On récupère les coordonnées actuelles au cas où on peut bouger
    int oldRow = ter[idTermite].coordTermite.ligne;
    int oldColumn = ter[idTermite].coordTermite.colonne;

    //déclare un tableau de string de taille 
    vector<string>  directionAlea;

    //Tableau contenant les directions de déplacements du termite (à modifier)
    vector<string> direction{ "N","NE","E","SE","S","SW","W","NW" };

    //On rempli les 18 ème premières cases avec la direction actuelle
    for (int i = 0; i < 17; i++)
    {
        directionAlea.push_back(ter[idTermite].direction);
    }

    int indexDirectionActuelle = 0;

    //il faut qu'on trouve l'index de la position actuelle dans direction
    for (int foo = 0; foo < direction.size(); foo++)
    {
        if (direction[foo] == ter[idTermite].direction)
            indexDirectionActuelle = foo;
    }

    if ((indexDirectionActuelle != 0) && (indexDirectionActuelle != (direction.size() - 1)))
    {
        //Cela veut dire que c'est pas le début ou le dernier élement
        directionAlea.push_back(direction[indexDirectionActuelle - 1]);
        directionAlea.push_back(direction[indexDirectionActuelle + 1]);
    }
    else if (indexDirectionActuelle == 0)
    {
        //On est au début, donc il faut prendre le suivant et le dernier
        directionAlea.push_back(direction[indexDirectionActuelle + 1]);
        directionAlea.push_back(direction[direction.size() - 1]);
    }
    else if (indexDirectionActuelle == (direction.size() - 1))
    {
        //On est à la fin donc il faut prendre le précédent et le premier
        directionAlea.push_back(direction[indexDirectionActuelle - 1]);
        directionAlea.push_back(direction[0]);
    }

    //Maintenant on doit choisir un nombre entre 0 et 19 pour choisir la direction
    int nbAlea = (rand() % 19) ;
    string nouvelleDirection = " ";

    cout << "Le nombre aleatoire est : " << nbAlea << endl;

    //On affiche ensuite directionAlea
    cout << endl << endl << "Voici le tableau de direction aleatoire pour la termite numero " << idTermite + 1 << endl;

    for (int it = 0; it < directionAlea.size(); it++)
    {
        if (it == nbAlea)
        {
            nouvelleDirection = directionAlea[it];
        }
        cout << "Tour numero :" << it << " ";
        cout << directionAlea.at(it) << " " << endl;
    }

    cout << endl;

    cout << endl <<  "la nouvelle direction de la termite " << idTermite + 1 << " est : " << nouvelleDirection << endl;

    //Maintenant on change la direction de la termite
    ter[idTermite].direction = nouvelleDirection;

    int ligneTermite = ter[idTermite].coordTermite.ligne;
    int colonneTermite = ter[idTermite].coordTermite.colonne;

    //Maintenant on peut modifier la grille avec le caractère adéquat
    if (nouvelleDirection == "N")
    {
        
        if ((estVide(maTermitiere, ligneTermite - 1, colonneTermite) == true) && (ter[idTermite].porteNourriture == false) && (ter[idTermite].nombrePasseAvecBrindille > 0 ))
        {
            cout << "Condition 1" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite - 1][colonneTermite] = '|';
            ter[idTermite].coordTermite.ligne--;
        }
        else if ( (maTermitiere[ligneTermite - 1][colonneTermite] == '*') && (ter[idTermite].porteNourriture == false))
        {
            cout << "Condition 2" << endl;

            if (ter[idTermite].alreadyPickedFood == false)
            {
                cout << "C'est la premiere fois que la termite " << idTermite << "a l'oportunite de prendre une brindille" << endl;
                //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                if (estConnexe(maTermitiere, ligneTermite - 1, colonneTermite) == false)
                {
                    cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                    //C'est un tas connexe donc on reste sur notre position
                    maTermitiere[ligneTermite][colonneTermite] = '|';
                }
                else
                {
                    cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                    //là on trouve de la nourriture, donc on va sur la case de la nourriture
                    maTermitiere[oldRow][oldColumn] = ' ';
                    maTermitiere[ligneTermite - 1][colonneTermite] = '|';
                    ter[idTermite].coordTermite.ligne--;
                    ter[idTermite].porteNourriture = true;
                    ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    

                    //Si on a pu prendre la brindille on peut changer le booleen
                    ter[idTermite].alreadyPickedFood = true;
                }
            }
            else
            {
                cout << "la termite n'est pas a sa premiere brindille, date derniere prise : passe numero " << ter[idTermite].lapSinceLastSet << endl;
                cout << "passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE" << passeActuelle - ter[idTermite].lapSinceLastSet << endl;

                if ((passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE)
                {
                    //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                    if (estConnexe(maTermitiere, ligneTermite - 1, colonneTermite) == false)
                    {
                        cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                        //C'est un tas connexe donc on reste sur notre position
                        maTermitiere[ligneTermite][colonneTermite] = '|';
                    }
                    else
                    {
                        cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                        //là on trouve de la nourriture, donc on va sur la case de la nourriture
                        maTermitiere[oldRow][oldColumn] = ' ';
                        maTermitiere[ligneTermite - 1][colonneTermite] = '|';
                        ter[idTermite].coordTermite.ligne--;
                        ter[idTermite].porteNourriture = true;
                        ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    }
                }
                else
                {
                    cout << endl << "Le termite ne peut pas prendre cette brindille, car elle doit encore attendre" << endl;
                    //Du coup on reste sur place et on maintient le cap
                    //On modifie juste la grille
                    maTermitiere[ligneTermite][colonneTermite] = '|';
                }
            }

            

            
        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille == 0))
        {
            //Il faut impérativement déposer la brindille
            cout << "Condition 3" << endl;
            if (estVide(maTermitiere, ligneTermite - 1, colonneTermite) == true)//Nord
            {
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '|';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite - 1, colonneTermite + 1) == true)//Nord-Est
            {
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite + 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '/';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite - 1, colonneTermite - 1) == true)//Nord-Ouest
            {
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '\\';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else
            {
                //Si jamais il ne peut pas poser vers les 8 points cardinaux, il est enfermé
                cout << endl << "La termite " << idTermite + 1 << " est enferme." << endl;
                ter[idTermite].nombrePasseAvecBrindille++;
            }

        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille != 0) && (estVide(maTermitiere, ligneTermite - 1, colonneTermite) == true))
        {
            cout << "Condition 4" << endl;
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite - 1][colonneTermite] = '|';
            ter[idTermite].coordTermite.ligne--;
        }
        else if (ligneTermite - 1 <= 0)
        {
            vector<string> direction{"E","W"};
            cout << "Condition 5" << endl;
            //Maintenant on doit choisir un nombre entre 0 et 1 pour choisir la direction
            int nbAlea = rand() % 2;
            string nouvelleDirection = " ";

            if (nbAlea == 0)
            {
                nouvelleDirection = direction.front();
            }
            else
            {
                nouvelleDirection = direction.back();
            }

            //On corrige notre direction

            ter[idTermite].direction = nouvelleDirection;

            
            maTermitiere[ligneTermite][colonneTermite] = '-';
            



        }
        else
        {
            cout << "Condition 6" << endl;
            maTermitiere[ligneTermite][colonneTermite] = '|';
        }
        
    }
    else if (nouvelleDirection == "S")
    {
        if ((estVide(maTermitiere, ligneTermite + 1, colonneTermite) == true) && (ter[idTermite].porteNourriture == false) && (ter[idTermite].nombrePasseAvecBrindille > 0))
        {
            cout << "Condition 1" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite + 1][colonneTermite] = '|';
            ter[idTermite].coordTermite.ligne++;
        }
        else if ((maTermitiere[ligneTermite + 1][colonneTermite] == '*') && (ter[idTermite].porteNourriture == false))
        {
            cout << "Condition 2" << endl;

            if (ter[idTermite].alreadyPickedFood == false)
            {
                cout << "C'est la premiere fois que la termite " << idTermite << "a l'oportunite de prendre une brindille" << endl;
                //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                if (estConnexe(maTermitiere, ligneTermite + 1, colonneTermite) == false)
                {
                    cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                    //C'est un tas connexe donc on reste sur notre position
                    maTermitiere[ligneTermite][colonneTermite] = '|';
                }
                else
                {
                    cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                    //là on trouve de la nourriture, donc on va sur la case de la nourriture
                    maTermitiere[oldRow][oldColumn] = ' ';
                    maTermitiere[ligneTermite + 1][colonneTermite] = '|';
                    ter[idTermite].coordTermite.ligne++;
                    ter[idTermite].porteNourriture = true;
                    ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    
                    ter[idTermite].alreadyPickedFood = true;
                }
            }
            else
            {
                cout << "la termite n'est pas a sa premiere brindille, date derniere prise : passe numero " << ter[idTermite].lapSinceLastSet << endl;
                cout << "passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE" << passeActuelle - ter[idTermite].lapSinceLastSet << endl;

                if ((passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE)
                {
                    //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                    if (estConnexe(maTermitiere, ligneTermite + 1, colonneTermite) == false)
                    {
                        cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                        //C'est un tas connexe donc on reste sur notre position
                        maTermitiere[ligneTermite][colonneTermite] = '|';
                    }
                    else
                    {
                        cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                        //là on trouve de la nourriture, donc on va sur la case de la nourriture
                        maTermitiere[oldRow][oldColumn] = ' ';
                        maTermitiere[ligneTermite + 1][colonneTermite] = '|';
                        ter[idTermite].coordTermite.ligne++;
                        ter[idTermite].porteNourriture = true;
                        ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                        
                    }
                }
                else
                {
                    cout << endl << "Le termite ne peut pas prendre cette brindille, car elle doit encore attendre" << endl;
                    //Du coup on reste sur place et on maintient le cap
                    //On modifie juste la grille
                    maTermitiere[ligneTermite][colonneTermite] = '|';
                }
            }

            
            
        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille == 0))
        {
            cout << "Condition 3" << endl;
            if (estVide(maTermitiere, ligneTermite + 1, colonneTermite) == true)//Sud
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '|';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite + 1, colonneTermite + 1) == true)//Sud-Est
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite + 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '\\';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite + 1, colonneTermite - 1) == true)//Sud-Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '/';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else
            {
                //Si jamais il ne peut pas poser vers les 8 points cardinaux, il est enfermé
                cout << endl << "La termite " << idTermite + 1 << " est enferme." << endl;
                ter[idTermite].nombrePasseAvecBrindille++;
            }

        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille != 0) && (estVide(maTermitiere, ligneTermite + 1, colonneTermite) == true))
        {
            cout << "Condition 4" << endl;
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite + 1][colonneTermite] = '|';
            ter[idTermite].coordTermite.ligne++;
        }
        else if (ligneTermite + 1 >= TAILLE_GRILLE)
        {
            vector<string> direction{ "E","W" };
            cout << "Condition 5" << endl;
            cout << endl <<  "La termite " << idTermite << " est a la limite de la grille, il faut tourner " << endl;

            //Maintenant on doit choisir un nombre entre 0 et 1 pour choisir la direction
            int nbAlea = rand() % 2;
            string nouvelleDirection = " ";

            if (nbAlea == 0)
            {
                nouvelleDirection = direction.front();
            }
            else
            {
                nouvelleDirection = direction.back();
            }

            //On corrige notre direction

            ter[idTermite].direction = nouvelleDirection;

            maTermitiere[ligneTermite][colonneTermite] = '-';



        }
        else
        {
            cout << "Condition 6" << endl;
            cout << "Oups, la termite" << idTermite + 1 << "ne bouge pas" << endl;
            maTermitiere[ligneTermite][colonneTermite] = '|';
        }
    }
    else if (nouvelleDirection == "E")
    {
        if ((estVide(maTermitiere, ligneTermite, colonneTermite + 1) == true) && (ter[idTermite].porteNourriture == false) && (ter[idTermite].nombrePasseAvecBrindille > 0))
        {
            cout << "Condition 1" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se déplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite][colonneTermite + 1] = '-';
            ter[idTermite].coordTermite.colonne++;
        }
        else if ((maTermitiere[ligneTermite][colonneTermite + 1] == '*') && (ter[idTermite].porteNourriture == false))
        {
            cout << "Condition 2" << endl;

            if (ter[idTermite].alreadyPickedFood == false)
            {
                cout << "C'est la premiere fois que la termite " << idTermite << "a l'oportunite de prendre une brindille" << endl;
                //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                if (estConnexe(maTermitiere, ligneTermite, colonneTermite + 1) == false)
                {
                    cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                    //C'est un tas connexe donc on reste sur notre position
                    maTermitiere[ligneTermite][colonneTermite] = '-';
                }
                else
                {
                    cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                    //là on trouve de la nourriture, donc on va sur la case de la nourriture
                    maTermitiere[oldRow][oldColumn] = ' ';
                    maTermitiere[ligneTermite][colonneTermite + 1] = '-';
                    ter[idTermite].coordTermite.colonne++;
                    ter[idTermite].porteNourriture = true;
                    ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    ter[idTermite].alreadyPickedFood = true;
                }
            }
            else
            {
                
                cout << "la termite n'est pas a sa premiere brindille, date derniere prise : passe numero " << ter[idTermite].lapSinceLastSet << endl;
                cout << "passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE" << passeActuelle - ter[idTermite].lapSinceLastSet << endl;

                if ((passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE)
                {
                    //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                    if (estConnexe(maTermitiere, ligneTermite, colonneTermite + 1) == false)
                    {
                        cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                        //C'est un tas connexe donc on reste sur notre position
                        maTermitiere[ligneTermite][colonneTermite] = '-';
                    }
                    else
                    {
                        cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                        //là on trouve de la nourriture, donc on va sur la case de la nourriture
                        maTermitiere[oldRow][oldColumn] = ' ';
                        maTermitiere[ligneTermite][colonneTermite + 1] = '-';
                        ter[idTermite].coordTermite.colonne++;
                        ter[idTermite].porteNourriture = true;
                        ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                        
                    }
                }
                else
                {
                    cout << endl << "Le termite ne peut pas prendre cette brindille, car elle doit encore attendre" << endl;
                    //Du coup on reste sur place et on maintient le cap
                    //On modifie juste la grille
                    maTermitiere[ligneTermite][colonneTermite] = '-';
                }
            }


            
            
        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille == 0))
        {
            cout << "Condition 3" << endl;
            if (estVide(maTermitiere, ligneTermite, colonneTermite + 1) == true)//Est
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite][colonneTermite + 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '-';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite + 1, colonneTermite + 1) == true)//Sud-Est
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite + 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '\\';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite - 1, colonneTermite - 1) == true)//Nord-Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '\\';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si jamais il ne peut pas poser vers les 8 points cardinaux, il est enfermé
                cout << endl << "La termite " << idTermite + 1 << " est enferme." << endl;
                ter[idTermite].nombrePasseAvecBrindille++;
            }

        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille != 0) && (estVide(maTermitiere, ligneTermite, colonneTermite + 1) == true))
        {
            cout << "Condition 4" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se déplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite][colonneTermite + 1] = '-';
            ter[idTermite].coordTermite.colonne++;
        }
        else if (colonneTermite + 1 >= TAILLE_GRILLE)
        {
            cout << "Condition 5" << endl;
            vector<string> direction{ "N","S" };
            cout << endl << "La termite " << idTermite << " est a la limite de la grille " << endl;
            //Maintenant on doit choisir un nombre entre 0 et 1 pour choisir la direction
            int nbAlea = rand() % 2;
            string nouvelleDirection = " ";

            if (nbAlea == 0)
            {
                nouvelleDirection = direction.front();
            }
            else
            {
                nouvelleDirection = direction.back();
            }

            //On corrige notre direction

            ter[idTermite].direction = nouvelleDirection;
            maTermitiere[ligneTermite][colonneTermite] = '-';


        }
        else
        {
            cout << "Condition 6" << endl;
            maTermitiere[ligneTermite][colonneTermite] = '|';
        }
    }
    else if (nouvelleDirection == "W")
    {
        if ((estVide(maTermitiere, ligneTermite, colonneTermite - 1) == true) && (ter[idTermite].porteNourriture == false) && (ter[idTermite].nombrePasseAvecBrindille > 0))
        {
            cout << "Condition 1" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite][colonneTermite - 1] = '-';
            ter[idTermite].coordTermite.colonne--;
        }
        else if ((maTermitiere[ligneTermite][colonneTermite - 1] == '*') && (ter[idTermite].porteNourriture == false))
        {
            cout << "Condition 2" << endl;

            if (ter[idTermite].alreadyPickedFood == false)
            {
                cout << "C'est la premiere fois que la termite " << idTermite << "a l'oportunite de prendre une brindille" << endl;
                //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                if (estConnexe(maTermitiere, ligneTermite, colonneTermite - 1) == false)
                {
                    cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                    //C'est un tas connexe donc on reste sur notre position
                    maTermitiere[ligneTermite][colonneTermite] = '-';
                }
                else
                {
                    cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                    //là on trouve de la nourriture, donc on va sur la case de la nourriture
                    maTermitiere[oldRow][oldColumn] = ' ';
                    maTermitiere[ligneTermite][colonneTermite - 1] = '-';
                    ter[idTermite].coordTermite.colonne--;
                    ter[idTermite].porteNourriture = true;
                    ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    ter[idTermite].alreadyPickedFood = true;
                }
            }
            else
            {
                cout << "la termite n'est pas a sa premiere brindille, date derniere prise : passe numero " << ter[idTermite].lapSinceLastSet << endl;
                
                cout << "passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE" << passeActuelle - ter[idTermite].lapSinceLastSet<< endl;
                if ((passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE)
                {
                    //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                    if (estConnexe(maTermitiere, ligneTermite, colonneTermite - 1) == false)
                    {
                        cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                        //C'est un tas connexe donc on reste sur notre position
                        maTermitiere[ligneTermite][colonneTermite] = '-';
                    }
                    else
                    {
                        cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                        //là on trouve de la nourriture, donc on va sur la case de la nourriture
                        maTermitiere[oldRow][oldColumn] = ' ';
                        maTermitiere[ligneTermite][colonneTermite - 1] = '-';
                        ter[idTermite].coordTermite.colonne--;
                        ter[idTermite].porteNourriture = true;
                        ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                        
                    }
                }
                else
                {
                    cout << endl << "Le termite ne peut pas prendre cette brindille, car elle doit encore attendre" << endl;
                    //Du coup on reste sur place et on maintient le cap
                    //On modifie juste la grille
                    maTermitiere[ligneTermite][colonneTermite] = '-';
                }
            }

            
            
        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille == 0))
        {
            cout << "Condition 3" << endl;
            if (estVide(maTermitiere, ligneTermite, colonneTermite - 1) == true)//Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '-';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite - 1, colonneTermite - 1) == true)//Nord-Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '\\';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite + 1, colonneTermite - 1) == true)//Sud-Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '/';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else
            {
                //Si jamais il ne peut pas poser vers les 8 points cardinaux, il est enfermé
                cout << endl << "La termite " << idTermite + 1 << " est enferme." << endl;
                ter[idTermite].nombrePasseAvecBrindille++;
            }

        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille != 0) && (estVide(maTermitiere, ligneTermite, colonneTermite - 1) == true))
        {
            cout << "Condition 4" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite][colonneTermite - 1] = '-';
            ter[idTermite].coordTermite.colonne--;
        }
        else if (colonneTermite - 1 <= 0)
        {
            cout << "Condition 5" << endl;
            vector<string> direction{ "N","S" };
            cout << endl << "La termite " << idTermite << " est a la limite de la grille" << endl;
            //Maintenant on doit choisir un nombre entre 0 et 1 pour choisir la direction
            int nbAlea = rand() % 2;
            string nouvelleDirection = " ";

            if (nbAlea == 0)
            {
                nouvelleDirection = direction.front();
            }
            else
            {
                nouvelleDirection = direction.back();
            }

            //On corrige notre direction

            ter[idTermite].direction = nouvelleDirection;
            maTermitiere[ligneTermite][colonneTermite] = '|';


        }
        else
        {
        cout << "Condition 6" << endl;
        maTermitiere[ligneTermite][colonneTermite] = '-';
        }
    }
    else if (nouvelleDirection == "SE")
    {
        if ((estVide(maTermitiere, ligneTermite + 1, colonneTermite + 1) == true) && (ter[idTermite].porteNourriture == false) && (ter[idTermite].nombrePasseAvecBrindille > 0))
        {
            cout << "Condition 1" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite + 1][colonneTermite + 1] = '\\';
            ter[idTermite].coordTermite.ligne++;
            ter[idTermite].coordTermite.colonne++;
        }
        else if ((maTermitiere[ligneTermite + 1][colonneTermite + 1] == '*') && (ter[idTermite].porteNourriture == false))
        {
            cout << "Condition 2" << endl;

            if (ter[idTermite].alreadyPickedFood == false)
            {
                cout << "C'est la premiere fois que la termite " << idTermite << "a l'oportunite de prendre une brindille" << endl;
                //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                if (estConnexe(maTermitiere, ligneTermite + 1, colonneTermite + 1) == false)
                {
                    cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                    //C'est un tas connexe donc on reste sur notre position
                    maTermitiere[ligneTermite][colonneTermite] = '\\';
                }
                else
                {
                    cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                    //là on trouve de la nourriture, donc on va sur la case de la nourriture
                    maTermitiere[oldRow][oldColumn] = ' ';
                    maTermitiere[ligneTermite + 1][colonneTermite + 1] = '\\';
                    ter[idTermite].coordTermite.ligne++;
                    ter[idTermite].coordTermite.colonne++;
                    ter[idTermite].porteNourriture = true;
                    ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    ter[idTermite].alreadyPickedFood = true;
                }
            }
            else
            {
                cout << "la termite n'est pas a sa premiere brindille, date derniere prise : passe numero " << ter[idTermite].lapSinceLastSet << endl;
                cout << "passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE" << passeActuelle - ter[idTermite].lapSinceLastSet << endl;

                if ((passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE)
                {
                    //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                    if (estConnexe(maTermitiere, ligneTermite + 1, colonneTermite + 1) == false)
                    {
                        cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                        //C'est un tas connexe donc on reste sur notre position
                        maTermitiere[ligneTermite][colonneTermite] = '\\';
                    }
                    else
                    {
                        cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                        //là on trouve de la nourriture, donc on va sur la case de la nourriture
                        maTermitiere[oldRow][oldColumn] = ' ';
                        maTermitiere[ligneTermite + 1][colonneTermite + 1] = '\\';
                        ter[idTermite].coordTermite.ligne++;
                        ter[idTermite].coordTermite.colonne++;
                        ter[idTermite].porteNourriture = true;
                        ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    }
                }
                else
                {
                    cout << endl << "Le termite ne peut pas prendre cette brindille, car elle doit encore attendre" << endl;
                    //Du coup on reste sur place et on maintient le cap
                    //On modifie juste la grille
                    maTermitiere[ligneTermite][colonneTermite] = '\\';
                }
            }

            
            
        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille == 0))
        {
            cout << "Condition 3" << endl;
            if (estVide(maTermitiere, ligneTermite + 1, colonneTermite + 1) == true)//Sud-Est
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite + 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '\\';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite + 1, colonneTermite) == true)//Sud
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '|';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite, colonneTermite + 1) == true)//Est
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite][colonneTermite + 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '-';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite - 1, colonneTermite) == true)
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '|';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else
            {
                //Si jamais il ne peut pas poser vers les 8 points cardinaux, il est enfermé
                cout << endl << "La termite " << idTermite + 1 << " est enferme." << endl;
                ter[idTermite].nombrePasseAvecBrindille++;
            }

        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille != 0) && (estVide(maTermitiere, ligneTermite + 1, colonneTermite + 1) == true))
        {
            cout << "Condition 4" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite + 1][colonneTermite + 1] = '\\';
            ter[idTermite].coordTermite.ligne++;
            ter[idTermite].coordTermite.colonne++;
        }
        else if ((ligneTermite + 1 >= TAILLE_GRILLE) || (colonneTermite + 1 >= TAILLE_GRILLE))
        {
            cout << "Condition 5" << endl;
            vector<string> direction{ "N","W" };
            cout << endl << "La termite " << idTermite << " est a la limite de la grille" << endl;
            //Maintenant on doit choisir un nombre entre 0 et 1 pour choisir la direction
            int nbAlea = rand() % 2;
            string nouvelleDirection = " ";

            if (nbAlea == 0)
            {
                nouvelleDirection = direction.front();
            }
            else
            {
                nouvelleDirection = direction.back();
            }

            //On corrige notre direction

            ter[idTermite].direction = nouvelleDirection;

            if(nouvelleDirection == "N")
                maTermitiere[ligneTermite][colonneTermite] = '|';
            else if(nouvelleDirection == "W")
                maTermitiere[ligneTermite][colonneTermite] = '-';


        }
        else
        {
        cout << "Condition 6" << endl;
            maTermitiere[ligneTermite][colonneTermite] = '\\';
        }
    }
    else if (nouvelleDirection == "SW")
    {
        if ((estVide(maTermitiere, ligneTermite + 1, colonneTermite - 1) == true) && (ter[idTermite].porteNourriture == false) && (ter[idTermite].nombrePasseAvecBrindille > 0))
        {
            cout << "Condition 1" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precesdente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite + 1][colonneTermite - 1] = '/';
            ter[idTermite].coordTermite.ligne++;
            ter[idTermite].coordTermite.colonne--;
        }
        else if ((maTermitiere[ligneTermite + 1][colonneTermite - 1] == '*') && (ter[idTermite].porteNourriture == false))
        {
            cout << "Condition 2" << endl;

            if (ter[idTermite].alreadyPickedFood == false)
            {
                cout << "C'est la premiere fois que la termite " << idTermite << "a l'oportunite de prendre une brindille" << endl;
                //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                if (estConnexe(maTermitiere, ligneTermite + 1, colonneTermite - 1) == false)
                {
                    cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                    //C'est un tas connexe donc on reste sur notre position
                    maTermitiere[ligneTermite][colonneTermite] = '/';
                }
                else
                {
                    cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                    //là on trouve de la nourriture, donc on va sur la case de la nourriture
                    maTermitiere[oldRow][oldColumn] = ' ';
                    maTermitiere[ligneTermite + 1][colonneTermite - 1] = '/';
                    ter[idTermite].coordTermite.ligne++;
                    ter[idTermite].coordTermite.colonne--;
                    ter[idTermite].porteNourriture = true;
                    ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    ter[idTermite].alreadyPickedFood = true;
                }
            }
            else
            {
                cout << "la termite n'est pas a sa premiere brindille, date derniere prise : passe numero " << ter[idTermite].lapSinceLastSet << endl;
                cout << "passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE" << passeActuelle - ter[idTermite].lapSinceLastSet<< endl;

                if ((passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE)
                {
                    //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                    if (estConnexe(maTermitiere, ligneTermite + 1, colonneTermite - 1) == false)
                    {
                        cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                        //C'est un tas connexe donc on reste sur notre position
                        maTermitiere[ligneTermite][colonneTermite] = '/';
                    }
                    else
                    {
                        cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                        //là on trouve de la nourriture, donc on va sur la case de la nourriture
                        maTermitiere[oldRow][oldColumn] = ' ';
                        maTermitiere[ligneTermite + 1][colonneTermite - 1] = '/';
                        ter[idTermite].coordTermite.ligne++;
                        ter[idTermite].coordTermite.colonne--;
                        ter[idTermite].porteNourriture = true;
                        ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                        
                    }
                }
                else
                {
                    cout << endl << "Le termite ne peut pas prendre cette brindille, car elle doit encore attendre" << endl;
                    //Du coup on reste sur place et on maintient le cap
                    //On modifie juste la grille
                    maTermitiere[ligneTermite][colonneTermite] = '/';
                }
            }

            

            
        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille == 0))
        {
            cout << "Condition 3" << endl;
            if (estVide(maTermitiere, ligneTermite + 1, colonneTermite - 1) == true)//Sud-Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '/';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite + 1, colonneTermite) == true)//Sud
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite + 1][colonneTermite] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '|';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite, colonneTermite - 1) == true)//Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '-';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else
            {
                //Si jamais il ne peut pas poser vers les 8 points cardinaux, il est enfermé
                cout << endl << "La termite " << idTermite + 1 << " est enferme." << endl;
                ter[idTermite].nombrePasseAvecBrindille++;
            }

        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille != 0) && (estVide(maTermitiere, ligneTermite + 1, colonneTermite + 1) == true))
        {
            cout << "Condition 4" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precesdente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite + 1][colonneTermite - 1] = '/';
            ter[idTermite].coordTermite.ligne++;
            ter[idTermite].coordTermite.colonne--;
        }
        else if ((ligneTermite + 1 >= TAILLE_GRILLE) || (colonneTermite - 1 <= 0))
        {
            cout << "Condition 5" << endl;
            vector<string> direction{ "N","E" };
            cout << endl << "La termite " << idTermite << " est a la limite de la grille" << endl;
            //Maintenant on doit choisir un nombre entre 0 et 1 pour choisir la direction
            int nbAlea = rand() % 2;
            string nouvelleDirection = " ";

            if (nbAlea == 0)
            {
                nouvelleDirection = direction.front();
            }
            else
            {
                nouvelleDirection = direction.back();
            }

            //On corrige notre direction

            ter[idTermite].direction = nouvelleDirection;

            if(nouvelleDirection == "N")
                maTermitiere[ligneTermite][colonneTermite] = '|';
            else if(nouvelleDirection == "E")
                maTermitiere[ligneTermite][colonneTermite] = '-';


        }
        else
        {
            cout << "Condition 6" << endl;
            maTermitiere[ligneTermite][colonneTermite] = '/';
        }
    }
    else if (nouvelleDirection == "NE")
    {
        if ((estVide(maTermitiere, ligneTermite - 1, colonneTermite + 1) == true) && (ter[idTermite].porteNourriture == false) && (ter[idTermite].nombrePasseAvecBrindille > 0))
        {
            cout << "Condition 1" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite - 1][colonneTermite + 1] = '/';
            ter[idTermite].coordTermite.ligne--;
            ter[idTermite].coordTermite.colonne++;

        }
        else if ((maTermitiere[ligneTermite - 1][colonneTermite + 1] == '*') && (ter[idTermite].porteNourriture == false))
        {
            cout << "Condition 2" << endl;

            if (ter[idTermite].alreadyPickedFood == false)
            {
                cout << "C'est la premiere fois que la termite " << idTermite << "a l'oportunite de prendre une brindille" << endl;
                //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                if (estConnexe(maTermitiere, ligneTermite - 1, colonneTermite + 1) == false)
                {
                    cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                    //C'est un tas connexe donc on reste sur notre position
                    maTermitiere[ligneTermite][colonneTermite] = '/';
                }
                else
                {
                    cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                    //là on trouve de la nourriture, donc on va sur la case de la nourriture
                    maTermitiere[oldRow][oldColumn] = ' ';
                    maTermitiere[ligneTermite - 1][colonneTermite + 1] = '/';
                    ter[idTermite].coordTermite.ligne--;
                    ter[idTermite].coordTermite.colonne++;
                    ter[idTermite].porteNourriture = true;
                    ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    ter[idTermite].alreadyPickedFood = true;
                }
            }
            else
            {
                cout << "la termite n'est pas a sa premiere brindille, date derniere prise : passe numero " << ter[idTermite].lapSinceLastSet << endl;
                cout << "passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE" << passeActuelle - ter[idTermite].lapSinceLastSet << endl;

                if ((passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE)
                {
                    //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                    if (estConnexe(maTermitiere, ligneTermite - 1, colonneTermite + 1) == false)
                    {
                        cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                        //C'est un tas connexe donc on reste sur notre position
                        maTermitiere[ligneTermite][colonneTermite] = '/';
                    }
                    else
                    {
                        cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                        //là on trouve de la nourriture, donc on va sur la case de la nourriture
                        maTermitiere[oldRow][oldColumn] = ' ';
                        maTermitiere[ligneTermite - 1][colonneTermite + 1] = '/';
                        ter[idTermite].coordTermite.ligne--;
                        ter[idTermite].coordTermite.colonne++;
                        ter[idTermite].porteNourriture = true;
                        ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    }
                }
                else
                {
                    cout << endl << "Le termite ne peut pas prendre cette brindille, car elle doit encore attendre" << endl;
                    //Du coup on reste sur place et on maintient le cap
                    //On modifie juste la grille
                    maTermitiere[ligneTermite][colonneTermite] = '/';
                }
            }


            

            
        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille == 0))
        {
            cout << "Condition 3" << endl;
            if (estVide(maTermitiere, ligneTermite - 1, colonneTermite + 1) == true)//Nord-Est
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite + 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '/';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite - 1, colonneTermite) == true)//Nord
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '|';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;

            }
            else if (estVide(maTermitiere, ligneTermite, colonneTermite + 1) == true)//Est
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite][colonneTermite + 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '-';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else
            {
                //Si jamais il ne peut pas poser vers les 8 points cardinaux, il est enfermé
                cout << endl << "La termite " << idTermite + 1 << " est enferme." << endl;
                ter[idTermite].nombrePasseAvecBrindille++;
            }


        }
        else if ((ligneTermite - 1 <= 0) || (colonneTermite + 1 >= TAILLE_GRILLE))
        {
            cout << "Condition 5" << endl;
            vector<string> direction{ "W","S" };
            cout << endl << "La termite " << idTermite << " est a la limite de la grille" << endl;
            //Maintenant on doit choisir un nombre entre 0 et 1 pour choisir la direction
            int nbAlea = rand() % 2;
            string nouvelleDirection = " ";

            if (nbAlea == 0)
            {
                nouvelleDirection = direction.front();
            }
            else
            {
                nouvelleDirection = direction.back();
            }

            //On corrige notre direction

            ter[idTermite].direction = nouvelleDirection;

            if(nouvelleDirection == "W")
                maTermitiere[ligneTermite][colonneTermite] = '-';
            else if(nouvelleDirection == "S")
                maTermitiere[ligneTermite][colonneTermite] = '|';


        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille != 0) && (estVide(maTermitiere, ligneTermite - 1, colonneTermite + 1) == true))
        {
        cout << "Condition 4" << endl;
        //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
        cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precesdente" << endl;
        maTermitiere[oldRow][oldColumn] = ' ';
        maTermitiere[ligneTermite - 1][colonneTermite + 1] = '/';
        ter[idTermite].coordTermite.ligne--;
        ter[idTermite].coordTermite.colonne++;
        }
        else
        {
            cout << "Condition 6" << endl;
            maTermitiere[ligneTermite][colonneTermite] = '/';
        }
    }
    else if (nouvelleDirection == "NW")
    {
        if ((estVide(maTermitiere, ligneTermite - 1, colonneTermite - 1) == true) && (ter[idTermite].porteNourriture == false) && (ter[idTermite].nombrePasseAvecBrindille > 0))
        {
            cout << "Condition 1" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precedente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite - 1][colonneTermite - 1] = '\\';
            ter[idTermite].coordTermite.ligne--;
            ter[idTermite].coordTermite.colonne--;
        }
        else if ((maTermitiere[ligneTermite - 1][colonneTermite - 1] == '*') && (ter[idTermite].porteNourriture == false))
        {
            cout << "Condition 2" << endl;

            if (ter[idTermite].alreadyPickedFood == false)
            {
                cout << "C'est la premiere fois que la termite " << idTermite << "a l'oportunite de prendre une brindille" << endl;
                //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                if (estConnexe(maTermitiere, ligneTermite - 1, colonneTermite - 1) == false)
                {
                    cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                    //C'est un tas connexe donc on reste sur notre position
                    maTermitiere[ligneTermite][colonneTermite] = '\\';
                }
                else
                {
                    cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                    //là on trouve de la nourriture, donc on va sur la case de la nourriture
                    maTermitiere[oldRow][oldColumn] = ' ';
                    maTermitiere[ligneTermite - 1][colonneTermite - 1] = '\\';
                    ter[idTermite].coordTermite.ligne--;
                    ter[idTermite].coordTermite.colonne--;
                    ter[idTermite].porteNourriture = true;
                    ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    ter[idTermite].alreadyPickedFood = true;
                }
            }
            else
            {
                if ((passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE)
                {
                    cout << "la termite n'est pas a sa premiere brindille, date derniere prise : passe numero " << ter[idTermite].lapSinceLastSet << endl;
                    cout << "passeActuelle - ter[idTermite].lapSinceLastSet) >= NOMBRE_DEPLACEMENT_AVANT_REPOSE" << passeActuelle - ter[idTermite].lapSinceLastSet << endl;

                    //On a dans notre direction une brindille, mais faut vérifier si elle n'est pas connexe
                    if (estConnexe(maTermitiere, ligneTermite - 1, colonneTermite - 1) == false)
                    {
                        cout << "La termite " << idTermite << " ne peut pas prendre la brindille car elle est connexe ! " << endl;
                        //C'est un tas connexe donc on reste sur notre position
                        maTermitiere[ligneTermite][colonneTermite] = '\\';
                    }
                    else
                    {
                        cout << endl << "Le termite numero " << idTermite + 1 << " possède maintenant une brindille" << endl;
                        //là on trouve de la nourriture, donc on va sur la case de la nourriture
                        maTermitiere[oldRow][oldColumn] = ' ';
                        maTermitiere[ligneTermite - 1][colonneTermite - 1] = '\\';
                        ter[idTermite].coordTermite.ligne--;
                        ter[idTermite].coordTermite.colonne--;
                        ter[idTermite].porteNourriture = true;
                        ter[idTermite].nombrePasseAvecBrindille = NOMBRE_DEPLACEMENT_AVANT_REPOSE;
                    }
                }
                else
                {
                    cout << endl << "Le termite ne peut pas prendre cette brindille, car elle doit encore attendre" << endl;
                    //Du coup on reste sur place et on maintient le cap
                    //On modifie juste la grille
                    maTermitiere[ligneTermite][colonneTermite] = '\\';
                }
            }

            
            
        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille == 0))
        {
            cout << "Condition 3" << endl;
            if (estVide(maTermitiere, ligneTermite - 1, colonneTermite - 1) == true)//Nord-Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '\\';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else if (estVide(maTermitiere, ligneTermite - 1, colonneTermite) == true)//Nord
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite - 1][colonneTermite] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '|';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;

            }
            else if (estVide(maTermitiere, ligneTermite, colonneTermite - 1) == true)//Ouest
            {
                cout << "La termite " << idTermite << " pose la brindille" << endl;
                //Si la case est libre on pose la brindille ici
                maTermitiere[ligneTermite][colonneTermite - 1] = '*';
                maTermitiere[ligneTermite][colonneTermite] = '-';
                ter[idTermite].porteNourriture = false;
                ter[idTermite].lapSinceLastSet = passeActuelle;
                ter[idTermite].nombrePasseAvecBrindille = 6000;
            }
            else
            {
                //Si jamais il ne peut pas poser vers les 8 points cardinaux, il est enfermé
                cout << endl << "La termite " << idTermite + 1 << " est enferme." << endl;
                ter[idTermite].nombrePasseAvecBrindille++;
            }



        }
        else if ((ligneTermite - 1 <= 0) || (colonneTermite - 1 <= 0))
        {
            cout << "Condition 5" << endl;
            vector<string> direction{ "E","S" };
            cout << endl << "La termite " << idTermite << " est a la limite de la grille" << endl;
            //Maintenant on doit choisir un nombre entre 0 et 1 pour choisir la direction
            int nbAlea = rand() % 2;
            string nouvelleDirection = " ";

            if (nbAlea == 0)
            {
                nouvelleDirection = direction.front();
            }
            else
            {
                nouvelleDirection = direction.back();
            }

            //On corrige notre direction

            ter[idTermite].direction = nouvelleDirection;

            if(nouvelleDirection == "E")
                maTermitiere[ligneTermite][colonneTermite] = '-';
            else if(nouvelleDirection == "S")
                maTermitiere[ligneTermite][colonneTermite] = '|';


        }
        else if ((ter[idTermite].porteNourriture == true) && (ter[idTermite].nombrePasseAvecBrindille != 0) && (estVide(maTermitiere, ligneTermite - 1, colonneTermite - 1) == true))
        {
            cout << "Condition 4" << endl;
            //Si il y a aucun problème et qu'on peut se déplacer on nettoie notre position précédente
            cout << endl << "il y a aucun probleme et qu'on peut se deplacer on nettoie notre position precesdente" << endl;
            maTermitiere[oldRow][oldColumn] = ' ';
            maTermitiere[ligneTermite - 1][colonneTermite - 1] = '\\';
            ter[idTermite].coordTermite.ligne--;
            ter[idTermite].coordTermite.colonne--;
        }
        else
        {
            cout << "Condition 6" << endl;
            maTermitiere[ligneTermite][colonneTermite] = '\\';
        }
    }

    //Si il possède une brindille, on enlève 1 au nombre de pas restant
    if (ter[idTermite].porteNourriture)
        ter[idTermite].nombrePasseAvecBrindille--;



}


/** Fonction qui ajoute une première fois des éléments  la matrixe (executée une seule fois)
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @param le tableau de termite
* @return void
**/
void ajouteElement(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE], Termite ter[NOMBRE_TERMITE])
{

    string direction[8] = { "N","E","W","S","NE","NW","SE","SW" }; //Tableau contenant les directions de déplacements du termite

    //Cette boucle implémente les termites.
    cout << to_string(NOMBRE_TERMITE) << " termites ont ete implantees" << endl;

    //Initialisation de rand
    srand(time(NULL));

    for (int i = 0; i < NOMBRE_TERMITE; i++)
    {

        ter[i].id = i + 1;

        int ligne = rand() % TAILLE_GRILLE;
        int colonne = rand() % TAILLE_GRILLE;

        while (estVide(maTermitiere, ligne, colonne) == false)
        {
            int ligne = rand() % TAILLE_GRILLE;
            int colonne = rand() % TAILLE_GRILLE;
        }


        ter[i].coordTermite.ligne = ligne;
        ter[i].coordTermite.colonne = colonne;

        //Maintenant on affecte aléatoirement une direction au termite
        int aleaDirection = rand() % 8;
        ter[i].direction = direction[aleaDirection];

        //Puis on modifie la grille en fonction de la direction
        switch (aleaDirection)
        {
        case 0:
            maTermitiere[ligne][colonne] = '|';
            break;
        case 1:
            maTermitiere[ligne][colonne] = '-';
            break;
        case 2:
            maTermitiere[ligne][colonne] = '-';
            break;
        case 3:
            maTermitiere[ligne][colonne] = '|';
            break;
        case 4:
            maTermitiere[ligne][colonne] = '/';
            break;
        case 5:
            maTermitiere[ligne][colonne] = '\\';
            break;
        case 6:
            maTermitiere[ligne][colonne] = '\\';
            break;
        case 7:
            maTermitiere[ligne][colonne] = '/';
            break;
        }

        ter[i].displayInfo();

    }

    //Boucle pour implémenter de la nourriture
    for (int i = 0; i < NOMBRE_BRINDILLES; i++)
    {
        int ligne = rand() % TAILLE_GRILLE;
        int colonne = rand() % TAILLE_GRILLE;

        while (estVide(maTermitiere, ligne, colonne) == false)
        {
            int ligne = rand() % TAILLE_GRILLE;
            int colonne = rand() % TAILLE_GRILLE;
        }

        //Changer les coordonnées dans maGrille par '*'
        maTermitiere[ligne][colonne] = '*';
    }

}


/** Fonction qui affiche la grille (la termitière)
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @return void
**/
void afficheTableau(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE])
{
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int y = 0; y < TAILLE_GRILLE; y++)
        {
            std::cout << maTermitiere[i][y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

}

/** Fonction qui initialise notre grille
* @param une matrice bi-dimensionnelle de caractère (la termitière)
* @return void
**/
void initialisationTableau(char maTermitiere[TAILLE_GRILLE][TAILLE_GRILLE])
{
    //Initialise chaque case avec  un espace
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int y = 0; y < TAILLE_GRILLE; y++)
        {
            maTermitiere[i][y] = ' ';
        }

    }
}