#include "manueldlg.h"

ManuelDlg::ManuelDlg(QWidget *parent) : QWidget(parent)
{
    // Taille des boutons
    QSize PBSize(80, 70);
    QSize PBCageSize(230, 40);

    // Police de caractère des widgets
    QFont GBFont("Arial", 11);
    QFont PBFont("Arial", 9);

    // GROUP BOX 1 : POMPE FLYGT
    GBPompe = new QGroupBox("POMPE FLYGT");
    GBPompe->setFont(GBFont);

        PBPompeDemarrer = new QPushButton("DEMARRER");
        PBPompeDemarrer->setMaximumSize(PBSize);
        PBPompeDemarrer->setFont(PBFont);
        PBPompeDemarrer->setCursor(Qt::PointingHandCursor);

        PBPompeArreter = new QPushButton("ARRETER");
        PBPompeArreter->setMaximumSize(PBSize);
        PBPompeArreter->setFont(PBFont);
        PBPompeArreter->setCursor(Qt::PointingHandCursor);
        PBPompeArreter->setEnabled(false);

        hboxPompe = new QHBoxLayout(GBPompe);
        hboxPompe->addWidget(PBPompeDemarrer);
        hboxPompe->addWidget(PBPompeArreter);
        GBPompe->setLayout(hboxPompe);

    // GROUP BOX 2 : CENTRALE HYDRAULIQUE
    GBCentrale = new QGroupBox("CENTRALE HYDRAULIQUE");
    GBCentrale->setFont(GBFont);

        PBCentraleDemarrer = new QPushButton("DEMARRER");
        PBCentraleDemarrer->setMaximumSize(PBSize);
        PBCentraleDemarrer->setFont(PBFont);
        PBCentraleDemarrer->setCursor(Qt::PointingHandCursor);

        PBCentraleArreter  = new QPushButton("ARRETER");
        PBCentraleArreter->setMaximumSize(PBSize);
        PBCentraleArreter->setFont(PBFont);
        PBCentraleArreter->setCursor(Qt::PointingHandCursor);
        PBCentraleArreter->setEnabled(false);

        hboxCentrale = new QHBoxLayout(GBCentrale);
        hboxCentrale->addWidget(PBCentraleDemarrer);
        hboxCentrale->addWidget(PBCentraleArreter);
        GBCentrale->setLayout(hboxCentrale);

    // GROUP BOX 3 : VANNE D'ATTRAIT
    GBVanneAttrait = new QGroupBox("VANNE D'ATTRAIT");
    GBVanneAttrait->setFont(GBFont);

        PBVanneAttraitOuvrir = new QPushButton("OUVRIR");
        PBVanneAttraitOuvrir->setMaximumSize(PBSize);
        PBVanneAttraitOuvrir->setFont(PBFont);
        PBVanneAttraitOuvrir->setCursor(Qt::PointingHandCursor);
        PBVanneAttraitOuvrir->setEnabled(false);

        PBVanneAttraitFermer = new QPushButton("FERMER");
        PBVanneAttraitFermer->setMaximumSize(PBSize);
        PBVanneAttraitFermer->setFont(PBFont);
        PBVanneAttraitFermer->setCursor(Qt::PointingHandCursor);
        PBVanneAttraitFermer->setEnabled(false);

        hboxVanneAttrait = new QHBoxLayout(GBVanneAttrait);
        hboxVanneAttrait->addWidget(PBVanneAttraitOuvrir);
        hboxVanneAttrait->addWidget(PBVanneAttraitFermer);
        GBVanneAttrait->setLayout(hboxVanneAttrait);

    // GROUP BOX 4 : GRILLE DE L'ASCENSEUR
    GBGrille = new QGroupBox("GRILLE");
    GBGrille->setFont(GBFont);

        PBGrilleOuvrir = new QPushButton("OUVRIR");
        PBGrilleOuvrir->setMaximumSize(PBSize);
        PBGrilleOuvrir->setFont(PBFont);
        PBGrilleOuvrir->setCursor(Qt::PointingHandCursor);
        PBGrilleOuvrir->setEnabled(false);

        PBGrilleFermer = new QPushButton("FERMER");
        PBGrilleFermer->setMaximumSize(PBSize);
        PBGrilleFermer->setFont(PBFont);
        PBGrilleFermer->setCursor(Qt::PointingHandCursor);
        PBGrilleFermer->setEnabled(false);

        hboxGrille = new QHBoxLayout(GBGrille);
        hboxGrille->addWidget(PBGrilleOuvrir);
        hboxGrille->addWidget(PBGrilleFermer);
        GBGrille->setLayout(hboxGrille);

    // GROUP BOX 5 : CAGE DE L'ASCENSEUR
    GBCage = new QGroupBox("CAGE");
    GBCage->setFont(GBFont);

        PBCageMPV = new QPushButton("MONTER EN PETITE VITESSE");
        PBCageMPV->setMaximumSize(PBCageSize);
        PBCageMPV->setFont(PBFont);
        PBCageMPV->setCursor(Qt::PointingHandCursor);
        PBCageMGV = new QPushButton("MONTER EN GRANDE VITESSE");
        PBCageMGV->setMaximumSize(PBCageSize);
        PBCageMGV->setFont(PBFont);
        PBCageMGV->setCursor(Qt::PointingHandCursor);
        PBCageDPV = new QPushButton("DESCENDRE EN PETITE VITESSE");
        PBCageDPV->setMaximumSize(PBCageSize);
        PBCageDPV->setFont(PBFont);
        PBCageDPV->setCursor(Qt::PointingHandCursor);
        PBCageDGV = new QPushButton("DESCENDRE EN GRANDE VITESSE");
        PBCageDGV->setMaximumSize(PBCageSize);
        PBCageDGV->setFont(PBFont);
        PBCageDGV->setCursor(Qt::PointingHandCursor);

        GLCage = new QGridLayout(GBCage);
        GLCage->addWidget(PBCageMPV, 0, 0);
        GLCage->addWidget(PBCageMGV, 0, 1);
        GLCage->addWidget(PBCageDPV, 1, 0);
        GLCage->addWidget(PBCageDGV, 1, 1);
        GBCage->setLayout(GLCage);

    // Layout principal
    GLMain = new QGridLayout(this);
    // Ajout ajoute les GroupBox au layout principal
    GLMain->addWidget(GBPompe, 0, 0);
    GLMain->addWidget(GBCentrale, 0, 1);
    GLMain->addWidget(GBVanneAttrait, 1, 0);
    GLMain->addWidget(GBGrille, 1, 1);
    GLMain->addWidget(GBCage, 2, 0, 1, 2);

    setLayout(GLMain);

    // Signaux & slots
    QObject::connect(PBPompeDemarrer, SIGNAL(clicked()), this, SLOT(demarrerPompe()));
    QObject::connect(PBPompeArreter, SIGNAL(clicked()), this, SLOT(arreterPompe()));
    QObject::connect(PBCentraleDemarrer, SIGNAL(clicked()), this, SLOT(demarrerCentrale()));
    QObject::connect(PBCentraleArreter, SIGNAL(clicked()), this, SLOT(arreterCentrale()));
}

void ManuelDlg::demarrerPompe()
{
    PBPompeDemarrer->setDisabled(true);
    PBPompeArreter->setEnabled(true);
}

void ManuelDlg::arreterPompe()
{
    PBPompeArreter->setDisabled(true);
    PBPompeDemarrer->setEnabled(true);
}

void ManuelDlg::demarrerCentrale()
{
    PBCentraleDemarrer->setDisabled(true);
    PBCentraleArreter->setEnabled(true);
    PBVanneAttraitOuvrir->setEnabled(true);
    PBVanneAttraitFermer->setEnabled(true);
    PBGrilleOuvrir->setEnabled(true);
    PBGrilleFermer->setEnabled(true);
}

void ManuelDlg::arreterCentrale()
{
    PBCentraleDemarrer->setEnabled(true);
    PBCentraleArreter->setDisabled(true);
    PBVanneAttraitOuvrir->setDisabled(true);
    PBVanneAttraitFermer->setDisabled(true);
    PBGrilleOuvrir->setDisabled(true);
    PBGrilleFermer->setDisabled(true);
}
