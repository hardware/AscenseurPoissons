#include "manueldlg.h"

ManuelDlg::ManuelDlg(
        QWidget *parent,
        Seance *seance,
        StatutsDlg *statutsDlg,
        JournalDlg *journalDlg
) : QWidget(parent),
    pSeance(seance),
    pStatutsDlg(statutsDlg),
    pJournalDlg(journalDlg)
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
        PBPompeDemarrer->setObjectName("PBPompeDemarrer");

        hboxPompe = new QHBoxLayout(GBPompe);
        hboxPompe->addWidget(PBPompeDemarrer);
        GBPompe->setLayout(hboxPompe);

    // GROUP BOX 2 : CENTRALE HYDRAULIQUE
    GBCentrale = new QGroupBox("CENTRALE HYDRAULIQUE");
    GBCentrale->setFont(GBFont);

        PBCentraleDemarrer = new QPushButton("DEMARRER");
        PBCentraleDemarrer->setMaximumSize(PBSize);
        PBCentraleDemarrer->setFont(PBFont);
        PBCentraleDemarrer->setCursor(Qt::PointingHandCursor);
        PBCentraleDemarrer->setObjectName("PBCentraleDemarrer");

        PBCentraleArreter  = new QPushButton("ARRETER");
        PBCentraleArreter->setMaximumSize(PBSize);
        PBCentraleArreter->setFont(PBFont);
        PBCentraleArreter->setCursor(Qt::PointingHandCursor);
        PBCentraleArreter->setEnabled(false);
        PBCentraleArreter->setObjectName("PBCentraleArreter");

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
        PBVanneAttraitOuvrir->setObjectName("PBVanneAttraitOuvrir");

        PBVanneAttraitFermer = new QPushButton("FERMER");
        PBVanneAttraitFermer->setMaximumSize(PBSize);
        PBVanneAttraitFermer->setFont(PBFont);
        PBVanneAttraitFermer->setCursor(Qt::PointingHandCursor);
        PBVanneAttraitFermer->setEnabled(false);
        PBVanneAttraitFermer->setObjectName("PBVanneAttraitFermer");

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
        PBGrilleOuvrir->setObjectName("PBGrilleOuvrir");

        PBGrilleFermer = new QPushButton("FERMER");
        PBGrilleFermer->setMaximumSize(PBSize);
        PBGrilleFermer->setFont(PBFont);
        PBGrilleFermer->setCursor(Qt::PointingHandCursor);
        PBGrilleFermer->setEnabled(false);
        PBGrilleFermer->setObjectName("PBGrilleFermer");

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
        PBCageMPV->setObjectName("PBMonterPV");

        PBCageMGV = new QPushButton("MONTER EN GRANDE VITESSE");
        PBCageMGV->setMaximumSize(PBCageSize);
        PBCageMGV->setFont(PBFont);
        PBCageMGV->setCursor(Qt::PointingHandCursor);
        PBCageMGV->setObjectName("PBMonterGV");

        PBCageDPV = new QPushButton("DESCENDRE EN PETITE VITESSE");
        PBCageDPV->setMaximumSize(PBCageSize);
        PBCageDPV->setFont(PBFont);
        PBCageDPV->setCursor(Qt::PointingHandCursor);
        PBCageDPV->setObjectName("PBDescendrePV");

        PBCageDGV = new QPushButton("DESCENDRE EN GRANDE VITESSE");
        PBCageDGV->setMaximumSize(PBCageSize);
        PBCageDGV->setFont(PBFont);
        PBCageDGV->setCursor(Qt::PointingHandCursor);
        PBCageDGV->setObjectName("PBDescendreGV");

        GLCage = new QGridLayout(GBCage);
        GLCage->addWidget(PBCageMPV, 0, 0);
        GLCage->addWidget(PBCageMGV, 0, 1);
        GLCage->addWidget(PBCageDPV, 1, 0);
        GLCage->addWidget(PBCageDGV, 1, 1);
        GBCage->setLayout(GLCage);

    // Layout principal
    GLMain = new QGridLayout(this);
    // Ajout les GroupBox au layout principal
    GLMain->addWidget(GBPompe, 0, 0);
    GLMain->addWidget(GBCentrale, 0, 1);
    GLMain->addWidget(GBVanneAttrait, 1, 0);
    GLMain->addWidget(GBGrille, 1, 1);
    GLMain->addWidget(GBCage, 2, 0, 1, 2);

    setLayout(GLMain);

    QMetaObject::connectSlotsByName(this);
}

void ManuelDlg::on_PBPompeDemarrer_clicked()
{
    PBPompeDemarrer->setDisabled(true);

    pStatutsDlg->allumerVoyant(pStatutsDlg->LBVoyantPompe, VERT);
    pJournalDlg->ajouterLog("La pompe est en marche", INFO);

    pSeance->testerAppareillages(_DEM_POMPE);
}

void ManuelDlg::on_PBCentraleDemarrer_clicked()
{
    PBCentraleDemarrer->setDisabled(true);
    PBCentraleArreter->setEnabled(true);
    PBVanneAttraitOuvrir->setEnabled(true);
    PBVanneAttraitFermer->setEnabled(true);
    PBGrilleOuvrir->setEnabled(true);
    PBGrilleFermer->setEnabled(true);

    pStatutsDlg->allumerVoyant(pStatutsDlg->LBVoyantCentrale, VERT);
    pJournalDlg->ajouterLog("La centrale est en marche", INFO);

    pSeance->testerAppareillages(_DEM_CENTRALE);
}

void ManuelDlg::on_PBCentraleArreter_clicked()
{
    PBCentraleDemarrer->setEnabled(true);
    PBCentraleArreter->setDisabled(true);
    PBVanneAttraitOuvrir->setDisabled(true);
    PBVanneAttraitFermer->setDisabled(true);
    PBGrilleOuvrir->setDisabled(true);
    PBGrilleFermer->setDisabled(true);

    pStatutsDlg->allumerVoyant(pStatutsDlg->LBVoyantCentrale, ROUGE);
    pJournalDlg->ajouterLog("La centrale est à l'arrêt", INFO);

    pSeance->testerAppareillages(_ARRET_CENTRALE);
}

void ManuelDlg::on_PBVanneAttraitOuvrir_clicked()
{
    pSeance->testerAppareillages(_OUVRIR_VANNE);
}

void ManuelDlg::on_PBVanneAttraitFermer_clicked()
{
    pSeance->testerAppareillages(_FERMER_VANNE);
}

void ManuelDlg::on_PBGrilleOuvrir_clicked()
{
    pSeance->testerAppareillages(_OUVRIR_GRILLE);
}

void ManuelDlg::on_PBGrilleFermer_clicked()
{
    pSeance->testerAppareillages(_FERMER_GRILLE);
}

void ManuelDlg::on_PBMonterPV_clicked()
{
    pSeance->testerAppareillages(_MONTER_CAGE);
}

void ManuelDlg::on_PBMonterGV_clicked()
{
    pSeance->testerAppareillages(_MONTER_CAGE);
}

void ManuelDlg::on_PBDescendrePV_clicked()
{
    pSeance->testerAppareillages(_DESCENDRE_CAGE);
}

void ManuelDlg::on_PBDescendreGV_clicked()
{
    pSeance->testerAppareillages(_DESCENDRE_CAGE);
}
