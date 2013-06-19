#include "accueildlg.h"

/**
 * @fn AccueilDlg::AccueilDlg(QWidget *parent)
 * @brief Constructeur paramétré
 *
 * Ce constructeur pemet de définir l'organisation des widgets
 * de l'onglet Accueil.
 *
 * @param parent[in] Pointeur sur le widget parent
 */
AccueilDlg::AccueilDlg(QWidget *parent) : QWidget(parent)
{
    LBTitre = new QLabel;
    LBTitre->setAlignment(Qt::AlignHCenter);
    LBTitre->setFont(QFont("Arial", 11));
    LBTitre->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    LBTitre->setText("INTERFACE DE CONTROLE DE L'ASCENSEUR A POISSONS");

    LBImgCentrale = new QLabel;
    LBImgCentrale->setPixmap(QPixmap(":/files/img/centrale.jpg"));

    LBVersion = new QLabel;
    LBVersion->setText("v1.0");
    LBVersion->setAlignment(Qt::AlignRight);
    LBVersion->setFont(QFont("Arial", 9, 75));

    vbox = new QVBoxLayout(this);
    vbox->addWidget(LBTitre);
    vbox->addWidget(LBImgCentrale);
    vbox->addWidget(LBVersion);

    setLayout(vbox);
}
