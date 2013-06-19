#include "seance.h"

/**
 * @fn Seance::Seance()
 * @brief Constructeur paramétré
 *
 * Définit l'état de la séance en mode MANU, initialise
 * paramètres de la séance et les champ de bits
 * correspondant au coffret pêcheur et au sommet
 * ascenseur.
 */
Seance::Seance()
{
    // Par défaut la séance est en mode manuel
    etatSeance = _MANU;

    // Initialisation des paramètres de la séance
    PV = 0;
    GV = 0;
    tempsPeche = 0;
    tempsVidange = 0;
    periodicite = 0;

    // Initialisation du champ de bits (tous les bits à 1)
    coffretPecheur.sTor.val         = 0xFFFF;
    coffretPecheur.eTor.val         = 0xFFFFFF;
    coffretPecheur.eAnalogique.val  = 0xFFFFFFFF;
    sommetAscenseur.sTor.val        = 0xFF;
    sommetAscenseur.eTor.val        = 0xFFFFFF;

    // Allocation dynamique
    pCapteurs      = new Capteurs(&iCan);
    pIcan          = new InterfaceCANDlg(&iCan);
    pPompe         = new Pompe(&iCan, pCapteurs, &coffretPecheur);
    pCentrale      = new CentraleHydraulique(&iCan, pCapteurs, &coffretPecheur);
    pVanneAttrait  = new VanneAttrait(&iCan, pCapteurs, &coffretPecheur);
    pCageAscenseur = new CageAscenseur(&iCan, pCapteurs, &coffretPecheur);
    pGrille        = new Grille(&iCan, pCapteurs, &coffretPecheur);
}

/**
 * @fn Seance::~Seance()
 * @brief Desctructeur par défaut
 *
 * Permet de libérer les zones mémoire allouées prédécement avec l'opérateur new
 */
Seance::~Seance()
{
    delete pPompe;
    delete pCentrale;
    delete pVanneAttrait;
    delete pCageAscenseur;
    delete pGrille;
    delete pCapteurs;
    delete pIcan;
}

/**
 * @fn void Seance::setSeance(int PV, int GV, int tempsPeche, int tempsVidange, int nbCycles, int periodicite)
 * @brief Méthode d'accès permettant de définir les paramètres de la séance
 */
void Seance::setSeance(int PV, int GV, int tempsPeche, int tempsVidange, int nbCycles, int periodicite)
{
    this->PV = PV;
    this->GV = GV;
    this->tempsPeche = tempsPeche;
    this->tempsVidange = tempsVidange;
    this->nbCycles = nbCycles;
    this->periodicite = periodicite;
}

/**
 * @fn bool Seance::enregistrer()
 * @brief Permet d'enregistrer les paramètres de la séance dans un fichier de configuration
 *
 * @return Retourne TRUE si les paramètres ont bien été enregistrés
 */
bool Seance::enregistrer()
{
    // Enregistrement des paramètres dans un fichier de configuration .ini
    params = new QSettings(QApplication::applicationDirPath() + "/seance.ini", QSettings::IniFormat);

    params->beginGroup("seance");
    params->setValue("PV", PV);
    params->setValue("GV", GV);
    params->setValue("TempsPeche", tempsPeche);
    params->setValue("TempsVidange", tempsVidange);
    params->setValue("NbCycles", nbCycles);
    params->setValue("Periodicite", periodicite);
    params->endGroup();

    if(params->status() != QSettings::NoError)
        return false; // Une erreur est survenue lors de l'enregistrement
    else
        return true;
}

/**
 * @fn void Seance::testerAppareillages(t_TypeTest type)
 * @brief Permet d'enregistrer les paramètres de la séance dans un fichier de configuration
 *
 * Permet de tester chaque appareillage si l'état de la
 * séance a été définit en manuel.
 *
 * @param type[in] Type de test
 */
void Seance::testerAppareillages(t_TypeTest type)
{
    if(etatSeance == _MANU)
    {
        switch(type)
        {
        case _DEM_POMPE :      pPompe->demarrer();
            break;
        case _ARRET_POMPE :    pPompe->detecterArret();
            break;
        case _OUVRIR_VANNE :   pVanneAttrait->ouvrir();
            break;
        case _FERMER_VANNE :   pVanneAttrait->fermer();
            break;
        case _MONTER_CAGE :    pCageAscenseur->monter();
            break;
        case _DESCENDRE_CAGE : pCageAscenseur->descendre();
            break;
        case _OUVRIR_GRILLE :  pGrille->ouvrir();
            break;
        case _FERMER_GRILLE :  pGrille->fermer();
            break;
        case _DEM_CENTRALE :   pCentrale->demarrer();
            break;
        case _ARRET_CENTRALE : pCentrale->arreter();
            break;
        }
    }
}

/**
 * @fn void Seance::setEtatSeance(t_EtatSeance etatSeance)
 * @brief Permet de définir l'état de la séance
 *
 * @param etatSeance[in] Etat de la séance
 */
void Seance::setEtatSeance(t_EtatSeance etatSeance)
{
    this->etatSeance = etatSeance;
}
