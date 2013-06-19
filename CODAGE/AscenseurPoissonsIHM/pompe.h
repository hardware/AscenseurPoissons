#ifndef POMPE_H
#define POMPE_H

#include "capteurs.h"
#include "interfacecan.h"

/**
 * @class Pompe
 * @brief Classe representant la pompe
 */
class Pompe
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

    Pompe(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur);

    void ecrireDonnee();
    void demarrer();
    bool detecterArret();
};

#endif // POMPE_H
