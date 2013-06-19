#include "ihm.h"

/**
 * @fn IHM::IHM(QWidget *parent)
 * @brief Constructeur paramétré
 *
 * Ce constructeur pemet de définir l'organisation
 * et les propriétés de l'IHM. C'est là aussi que
 * toutes les classes d'interface intermédiaires
 * sont créées.
 *
 * Ensuite on initialise chaque onglet avec les instances des classes intermédiaires.
 *
 * @param parent[in] Pointeur sur le widget parent
 */
IHM::IHM(QWidget *parent) : QWidget(parent)
{
    // Propriétés de la fenêtre principale
    setFixedSize(570,482);
    setWindowTitle("Ascenseur à poissons");
    setWindowIcon(QIcon(":/files/img/icon-shem.jpg"));

    accueilDlg = new AccueilDlg(this);
    statutsDlg = new StatutsDlg(this, &seance);
    journalDlg = new JournalDlg(this, &seance);
    manuelDlg = new ManuelDlg(this, &seance, statutsDlg, journalDlg);
    seanceDlg = new SeanceDlg(this, &seance);
    synoptiqueDlg = new SynoptiqueDlg(this, &seance);

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
