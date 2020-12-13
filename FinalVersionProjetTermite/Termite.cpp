#include <iostream>
#include "Termite.h"
#include "constante.h"

/** Fonction affichant les propriétés et les valeurs de(s) termite(s) 
* @return void
**/
void Termite::displayInfo()
{
    
     cout << " C'est la termite numero : " << id << " et elle se trouve a la ligne " << coordTermite.ligne << " et a la colonne " << coordTermite.colonne << ". Direction : " << direction << ". Porte nourriture :" << porteNourriture << ". Nombre passe avant repos : " << nombrePasseAvecBrindille << endl;

}