﻿#include "ihm.h"

IHM::IHM(QWidget *parent) : QWidget(parent)
{
    // Propriétés de la fenêtre principale
    setFixedSize(570,482);
    setWindowTitle(QString::fromUtf8("Ascenseur à poissons"));
    setWindowIcon(QIcon(":/files/img/icon-shem.jpg"));

    accueilDlg = new AccueilDlg(this);
    manuelDlg = new ManuelDlg(this, &seance);
    seanceDlg = new SeanceDlg(this, &seance);
    statutsDlg = new StatutsDlg(this, &seance);
    synoptiqueDlg = new SynoptiqueDlg(this, &seance);
    journalDlg = new JournalDlg(this, &seance);

    onglets = new QTabWidget;
    onglets->setFont(QFont("MS Shell Dlg 2", 11));
    onglets->addTab(accueilDlg, "ACCUEIL");
    onglets->addTab(manuelDlg, "MANUEL");
    onglets->addTab(seanceDlg, "SEANCE");
    onglets->addTab(statutsDlg, "STATUTS");
    onglets->addTab(synoptiqueDlg, "SYNOPTIQUE");
    onglets->addTab(journalDlg, "JOURNAL");

    layout = new QVBoxLayout(this);
    layout->addWidget(onglets);

    setLayout(layout);
}
