#ifndef VANNEATTRAIT_H
#define VANNEATTRAIT_H

#include "interfacecan.h"
#include "capteurs.h"

/**
 * @class VanneAttrait
 * @brief Classe representant la vanne d'attrait
 */
class VanneAttrait
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

    VanneAttrait(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur);

    void ecrireDonnee();
    void ouvrir();
    void fermer();

};

#endif // VANNEATTRAIT_H
