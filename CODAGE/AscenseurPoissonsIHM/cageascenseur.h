#ifndef CAGEASCENSEUR_H
#define CAGEASCENSEUR_H

#include "interfacecan.h"
#include "capteurs.h"

/**
 * @class CageAscenseur
 * @brief Classe representant la cage d'ascenseur
 */
class CageAscenseur
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

    CageAscenseur(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur);

    void monter();
    void descendre();

};

#endif // CAGEASCENSEUR_H
