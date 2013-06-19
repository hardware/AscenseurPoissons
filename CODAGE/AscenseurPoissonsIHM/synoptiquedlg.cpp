#include "synoptiquedlg.h"

/**
 * @fn SynoptiqueDlg::SynoptiqueDlg(QWidget *parent, Seance *seance)
 * @brief Constructeur paramétré
 *
 * Ce constructeur pemet de définir l'organisation des widgets
 * de l'onglet Synoptique
 *
 * @param parent[in] Pointeur sur le widget parent
 * @param seance[in] Pointeur sur l'instance de la classe Seance
 */
SynoptiqueDlg::SynoptiqueDlg(QWidget *parent, Seance *seance) : QWidget(parent), pSeance(seance)
{
    LBSchema = new QLabel;
    LBSchema->setPixmap(QPixmap(":/files/img/schema.png"));

    PrBAscenseur = new QProgressBar(LBSchema);
    PrBAscenseur->setOrientation(Qt::Vertical);
    PrBAscenseur->setGeometry(203, 110, 20, 214);
    PrBAscenseur->setValue(20);

    VLMain = new QVBoxLayout(this);
    VLMain->addWidget(LBSchema, 0, Qt::AlignCenter);

    setLayout(VLMain);
}
