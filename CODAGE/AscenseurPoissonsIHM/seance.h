#ifndef SEANCE_H
#define SEANCE_H

#include "interfacecan.h"
#include "interfacecandlg.h"
#include "pompe.h"
#include "centralehydraulique.h"
#include "vanneattrait.h"
#include "cageascenseur.h"
#include "grille.h"
#include "capteurs.h"

#include <QApplication>
#include <QSettings>

/**
 * @class JournalEvenements
 * @brief Classe representant une séance
 */
class Seance
{
    /**
     * Cette attribut permet de définir les paramètres de la séance
     */
    QSettings *params;

    /*
      Classes représentants les appareillages
    */
    Pompe *pPompe;
    CentraleHydraulique *pCentrale;
    VanneAttrait *pVanneAttrait;
    CageAscenseur *pCageAscenseur;
    Grille *pGrille;
    Capteurs *pCapteurs;

    /**
     * Interface CAN
     */
    InterfaceCAN iCan;

    /**
     * Pointeur contenant l'adresse d'une instance de la classe InterfaceCANDlg
     */
    InterfaceCANDlg *pIcan;

    /**
     * Etats de la séance
     */
    t_EtatSeance etatSeance;

    /**
     * Champ de bits réprésentant le noeud du coffret pêcheur
     */
    t_coffretPecheur coffretPecheur;

    /**
     * Champ de bits réprésentant le noeud du sommet ascenseur
     */
    t_sommetAscenseur sommetAscenseur;

    /**
     * Paramètres de la séance
     */
    int PV, GV, tempsPeche, tempsVidange, nbCycles, periodicite;

public:

    Seance();
    ~Seance();

    void setSeance(int PV, int GV, int tempsPeche, int tempsVidange, int nbCycles, int periodicite);
    bool enregistrer();
    void testerAppareillages(t_TypeTest type);
    void setEtatSeance(t_EtatSeance etatSeance);

};

#endif // SEANCE_H
