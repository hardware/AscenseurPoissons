#include "seance.h"

Seance::Seance()
{
    PV = 0;
    GV = 0;
    tempsPeche = 0;
    tempsVidange = 0;
    periodicite = 0;

    pPompe = new Pompe(&iCan);
    pCentrale = new CentraleHydraulique(&iCan);
    pVanneAttrait = new VanneAttrait(&iCan);
    pCageAscenseur = new CageAscenseur(&iCan);
    pGrille = new Grille(&iCan);
    pCapteurs = new Capteurs(&iCan);
}

Seance::~Seance()
{
    delete pPompe;
    delete pCentrale;
    delete pVanneAttrait;
    delete pCageAscenseur;
    delete pGrille;
    delete pCapteurs;
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
