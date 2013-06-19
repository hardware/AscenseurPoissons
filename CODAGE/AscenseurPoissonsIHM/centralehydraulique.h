#ifndef CENTRALEHYDRAULIQUE_H
#define CENTRALEHYDRAULIQUE_H

#include "interfacecan.h"
#include "capteurs.h"

/**
 * @class CentraleHydraulique
 * @brief Classe representant la centrale hydraulique
 */
class CentraleHydraulique
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

    CentraleHydraulique(InterfaceCAN *pIcan, Capteurs *pCapteurs, t_coffretPecheur *pCoffretPecheur);

    void ecrireDonnee();
    void demarrer();
    void arreter();

};

#endif // CENTRALEHYDRAULIQUE_H
