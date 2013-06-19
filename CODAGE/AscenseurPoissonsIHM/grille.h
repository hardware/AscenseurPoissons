#ifndef GRILLE_H
#define GRILLE_H

#include "interfacecan.h"
#include "capteurs.h"

/**
 * @class Grille
 * @brief Classe representant la Grille
 */
class Grille
{

    /**
     * Pointeur contenant l'adresse d'une instance de la classe InterfaceCAN
     */
    InterfaceCAN *pIcan;

    /**
     * Pointeur contenant l'adresse d'une instance de la classe Capteurs
     */
    Capteurs *pCapteurs;

    /**
     * Pointeur contenant l'adresse d'une instance de la classe t_coffretPecheur
     */
    t_coffretPecheur *pCoffretPecheur;

public:

    Grille(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur);

    void ouvrir();
    void fermer();

};

#endif // GRILLE_H
