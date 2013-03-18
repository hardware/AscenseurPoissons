#include "ihm.h"

IHM::IHM(QWidget *parent) : QWidget(parent)
{
    // Propriétés de la fenêtre principale
    setFixedSize(570,482);
    setWindowTitle(QString::fromUtf8("Ascenseur à poissons"));
    setWindowIcon(QIcon(":/files/img/icon-shem.jpg"));

    accueilDlg = new AccueilDlg(this);
    manuelDlg = new ManuelDlg(this);
    seanceDlg = new SeanceDlg(this);
    statutsDlg = new StatutsDlg(this);
    synoptiqueDlg = new SynoptiqueDlg(this);
    journalDlg = new JournalDlg(this);

    onglets = new QTabWidget;
    onglets->setFont(QFont("MS Shell Dlg 2", 11));
    onglets->addTab(accueilDlg, "ACCUEIL");
    onglets->addTab(manuelDlg, "MANUEL");
    onglets->addTab(seanceDlg, "SEANCE");
    onglets->addTab(statutsDlg, "STATUTS");
    onglets->addTab(synoptiqueDlg, "SYNOPTIQUE");
    onglets->addTab(journalDlg, "JOURNAL (2)");

    layout = new QVBoxLayout(this);
    layout->addWidget(onglets);

    setLayout(layout);
}
