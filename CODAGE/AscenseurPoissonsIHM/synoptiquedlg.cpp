#include "synoptiquedlg.h"

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
