#include "seance.h"

Seance::Seance()
{
    etatSeance = _MANU;

    PV = 0;
    GV = 0;
    tempsPeche = 0;
    tempsVidange = 0;
    periodicite = 0;

    pCapteurs      = new Capteurs(&iCan);
    pIcan          = new InterfaceCANDlg(&iCan);
    pPompe         = new Pompe(&iCan, pCapteurs);
    pCentrale      = new CentraleHydraulique(&iCan, pCapteurs);
    pVanneAttrait  = new VanneAttrait(&iCan, pCapteurs);
    pCageAscenseur = new CageAscenseur(&iCan, pCapteurs);
    pGrille        = new Grille(&iCan, pCapteurs);
}

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

void Seance::setSeance(int PV, int GV, int tempsPeche, int tempsVidange, int nbCycles, int periodicite)
{
    this->PV = PV;
    this->GV = GV;
    this->tempsPeche = tempsPeche;
    this->tempsVidange = tempsVidange;
    this->nbCycles = nbCycles;
    this->periodicite = periodicite;
}

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

void Seance::setEtatSeance(t_EtatSeance etatSeance)
{
    this->etatSeance = etatSeance;
}
