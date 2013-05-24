#include "statutsdlg.h"

StatutsDlg::StatutsDlg(QWidget *parent, Seance *seance) : QWidget(parent), pSeance(seance)
{
    QSize voyantSize(21, 21),
          LENiveauxSize(130, 25);

    QFont LEFont("Arial", 20),
          GBFont("Arial", 10),
          LENiveauFont("Arial", 11, 75);

    GBAppareillages = new QGroupBox("APPAREILLAGES");
    GBAppareillages->setFont(GBFont);

        LBPompe = new QLabel("POMPE");

            LBVoyantPompe = new QLabel;
            LBVoyantPompe->setMinimumSize(voyantSize);
            LBVoyantPompe->setMaximumSize(voyantSize);
            LBVoyantPompe->setStyleSheet(ROUGE);

            VLPompe = new QVBoxLayout;
            VLPompe->addWidget(LBVoyantPompe, 0, Qt::AlignHCenter);
            VLPompe->addWidget(LBPompe, 0, Qt::AlignHCenter);

        LBCentrale = new QLabel("CENTRALE HYDRAULIQUE");

            LBVoyantCentrale = new QLabel;
            LBVoyantCentrale->setMinimumSize(voyantSize);
            LBVoyantCentrale->setMaximumSize(voyantSize);
            LBVoyantCentrale->setStyleSheet(ROUGE);

            VLCentrale = new QVBoxLayout;
            VLCentrale->addWidget(LBVoyantCentrale, 0, Qt::AlignHCenter);
            VLCentrale->addWidget(LBCentrale, 0, Qt::AlignHCenter);

        GLAppareillages = new QGridLayout;
        GLAppareillages->addLayout(VLPompe, 0, 0);
        GLAppareillages->addLayout(VLCentrale, 0, 1, 1, 2);
        GBAppareillages->setLayout(GLAppareillages);

    GBNombreCycles = new QGroupBox("NOMBRE DE CYCLES");
    GBNombreCycles->setFont(GBFont);

        LBNombreCycles = new QLabel("EFFECTUES");

        LENombreCycles = new QLineEdit("1500");
        LENombreCycles->setMaximumSize(QSize(80, 40));
        LENombreCycles->setFont(LEFont);
        LENombreCycles->setAlignment(Qt::AlignHCenter);
        LENombreCycles->setReadOnly(true);

        VLNombreCycles = new QVBoxLayout;
        VLNombreCycles->addWidget(LENombreCycles, 0, Qt::AlignHCenter);
        VLNombreCycles->addWidget(LBNombreCycles, 0, Qt::AlignHCenter);
        GBNombreCycles->setLayout(VLNombreCycles);

    GBNiveaux = new QGroupBox("NIVEAUX");
    GBNiveaux->setFont(GBFont);

        LBNiveauAmont = new QLabel("NIVEAU AMONT");

            LBVoyantNiveauAmont = new QLabel;
            LBVoyantNiveauAmont->setMinimumSize(voyantSize);
            LBVoyantNiveauAmont->setMaximumSize(voyantSize);
            LBVoyantNiveauAmont->setStyleSheet(VERT);

            LENiveauAmont = new QLineEdit("418.50 mNGF");
            LENiveauAmont->setMaximumSize(LENiveauxSize);
            LENiveauAmont->setAlignment(Qt::AlignHCenter);
            LENiveauAmont->setFont(LENiveauFont);
            LENiveauAmont->setStyleSheet(BLEU);
            LENiveauAmont->setReadOnly(true);

            VLNiveauAmont = new QVBoxLayout;
            VLNiveauAmont->addWidget(LBVoyantNiveauAmont, 0, Qt::AlignHCenter);
            VLNiveauAmont->addWidget(LBNiveauAmont, 0, Qt::AlignHCenter);
            VLNiveauAmont->addWidget(LENiveauAmont, 0, Qt::AlignHCenter);

        LBNiveauAval = new QLabel("NIVEAU AVAL");

            LBVoyantNiveauAval = new QLabel;
            LBVoyantNiveauAval->setMinimumSize(voyantSize);
            LBVoyantNiveauAval->setMaximumSize(voyantSize);
            LBVoyantNiveauAval->setStyleSheet(VERT);

            LENiveauAval = new QLineEdit("415.50 mNGF");
            LENiveauAval->setMaximumSize(LENiveauxSize);
            LENiveauAval->setAlignment(Qt::AlignHCenter);
            LENiveauAval->setFont(LENiveauFont);
            LENiveauAval->setStyleSheet(BLEU);
            LENiveauAval->setReadOnly(true);

            VLNiveauAval = new QVBoxLayout;
            VLNiveauAval->addWidget(LBVoyantNiveauAval, 0, Qt::AlignHCenter);
            VLNiveauAval->addWidget(LBNiveauAval, 0, Qt::AlignHCenter);
            VLNiveauAval->addWidget(LENiveauAval, 0, Qt::AlignHCenter);

        LBNiveauHuile = new QLabel("NIVEAU HUILE");

            LBVoyantNiveauHuile = new QLabel;
            LBVoyantNiveauHuile->setMinimumSize(voyantSize);
            LBVoyantNiveauHuile->setMaximumSize(voyantSize);
            LBVoyantNiveauHuile->setStyleSheet(ORANGE);

            LENiveauHuile = new QLineEdit("2 L");
            LENiveauHuile->setMaximumSize(LENiveauxSize);
            LENiveauHuile->setAlignment(Qt::AlignHCenter);
            LENiveauHuile->setFont(LENiveauFont);
            LENiveauHuile->setStyleSheet(BLEU);
            LENiveauHuile->setReadOnly(true);

            VLNiveauHuile = new QVBoxLayout;
            VLNiveauHuile->addWidget(LBVoyantNiveauHuile, 0, Qt::AlignHCenter);
            VLNiveauHuile->addWidget(LBNiveauHuile, 0, Qt::AlignHCenter);
            VLNiveauHuile->addWidget(LENiveauHuile, 0, Qt::AlignHCenter);

        GLNiveaux = new QGridLayout;
        GLNiveaux->addLayout(VLNiveauAmont, 0, 0);
        GLNiveaux->addLayout(VLNiveauAval, 0, 1);
        GLNiveaux->addLayout(VLNiveauHuile, 0, 2);
        GBNiveaux->setLayout(GLNiveaux);

    GBDefauts = new QGroupBox("DEFAUTS");
    GBDefauts->setFont(GBFont);

        LBDefautTreuil = new QLabel("DEFAUT TREUIL");

            LBVoyantDefautTreuil = new QLabel;
            LBVoyantDefautTreuil->setMinimumSize(voyantSize);
            LBVoyantDefautTreuil->setMaximumSize(voyantSize);
            LBVoyantDefautTreuil->setStyleSheet(GRIS);

            HLDefautTreuil = new QHBoxLayout;
            HLDefautTreuil->addWidget(LBVoyantDefautTreuil);
            HLDefautTreuil->addWidget(LBDefautTreuil);

        LBDefautSurcharge = new QLabel("DEFAUT SURCHARGE ASCENSEUR");

            LBVoyantDefautSurcharge = new QLabel;
            LBVoyantDefautSurcharge->setMinimumSize(voyantSize);
            LBVoyantDefautSurcharge->setMaximumSize(voyantSize);
            LBVoyantDefautSurcharge->setStyleSheet(GRIS);

            HLDefautSurcharge = new QHBoxLayout;
            HLDefautSurcharge->addWidget(LBVoyantDefautSurcharge);
            HLDefautSurcharge->addWidget(LBDefautSurcharge);

        LBDefautVanne = new QLabel("DEFAUT VANNE");

            LBVoyantDefautVanne = new QLabel;
            LBVoyantDefautVanne->setMinimumSize(voyantSize);
            LBVoyantDefautVanne->setMaximumSize(voyantSize);
            LBVoyantDefautVanne->setStyleSheet(GRIS);

            HLDefautVanne = new QHBoxLayout;
            HLDefautVanne->addWidget(LBVoyantDefautVanne);
            HLDefautVanne->addWidget(LBDefautVanne);

        LBDefautCentrale = new QLabel("DEFAUT CENTRALE HYDRAULIQUE");

            LBVoyantDefautCentrale = new QLabel;
            LBVoyantDefautCentrale->setMinimumSize(voyantSize);
            LBVoyantDefautCentrale->setMaximumSize(voyantSize);
            LBVoyantDefautCentrale->setStyleSheet(GRIS);

            HLDefautCentrale = new QHBoxLayout;
            HLDefautCentrale->addWidget(LBVoyantDefautCentrale);
            HLDefautCentrale->addWidget(LBDefautCentrale);

        LBDefautPompe = new QLabel("DEFAUT POMPE");

            LBVoyantDefautPompe = new QLabel;
            LBVoyantDefautPompe->setMinimumSize(voyantSize);
            LBVoyantDefautPompe->setMaximumSize(voyantSize);
            LBVoyantDefautPompe->setStyleSheet(GRIS);

            HLDefautPompe = new QHBoxLayout;
            HLDefautPompe->addWidget(LBVoyantDefautPompe);
            HLDefautPompe->addWidget(LBDefautPompe);

        LBDefautMouCable = new QLabel("DEFAUT MOU DE CABLE");

            LBVoyantDefautMouCable = new QLabel;
            LBVoyantDefautMouCable->setMinimumSize(voyantSize);
            LBVoyantDefautMouCable->setMaximumSize(voyantSize);
            LBVoyantDefautMouCable->setStyleSheet(GRIS);

            HLDefautMouCable = new QHBoxLayout;
            HLDefautMouCable->addWidget(LBVoyantDefautMouCable);
            HLDefautMouCable->addWidget(LBDefautMouCable);

        LBDefautLimiteurEffort = new QLabel("DEFAUT LIMITEUR D'EFFORT");

            LBVoyantDefautLimiteurEffort = new QLabel;
            LBVoyantDefautLimiteurEffort->setMinimumSize(voyantSize);
            LBVoyantDefautLimiteurEffort->setMaximumSize(voyantSize);
            LBVoyantDefautLimiteurEffort->setStyleSheet(GRIS);

            HLDefautLimiteurEffort = new QHBoxLayout;
            HLDefautLimiteurEffort->addWidget(LBVoyantDefautLimiteurEffort);
            HLDefautLimiteurEffort->addWidget(LBDefautLimiteurEffort);

        LBDefautArretUrgence = new QLabel("DEFAUT ARRET D'URGENCE");

            LBVoyantDefautArretUrgence = new QLabel;
            LBVoyantDefautArretUrgence->setMinimumSize(voyantSize);
            LBVoyantDefautArretUrgence->setMaximumSize(voyantSize);
            LBVoyantDefautArretUrgence->setStyleSheet(GRIS);

            HLDefautArretUrgence = new QHBoxLayout;
            HLDefautArretUrgence->addWidget(LBVoyantDefautArretUrgence);
            HLDefautArretUrgence->addWidget(LBDefautArretUrgence);

        LBDefautCycle = new QLabel("DEFAUT CYCLE");

            LBVoyantDefautCycle = new QLabel;
            LBVoyantDefautCycle->setMinimumSize(voyantSize);
            LBVoyantDefautCycle->setMaximumSize(voyantSize);
            LBVoyantDefautCycle->setStyleSheet(GRIS);

            HLDefautCycle = new QHBoxLayout;
            HLDefautCycle->addWidget(LBVoyantDefautCycle);
            HLDefautCycle->addWidget(LBDefautCycle);

        LBDefautHuile = new QLabel("DEFAUT HUILE");

            LBVoyantDefautHuile = new QLabel;
            LBVoyantDefautHuile->setMinimumSize(voyantSize);
            LBVoyantDefautHuile->setMaximumSize(voyantSize);
            LBVoyantDefautHuile->setStyleSheet(GRIS);

            HLDefautHuile = new QHBoxLayout;
            HLDefautHuile->addWidget(LBVoyantDefautHuile);
            HLDefautHuile->addWidget(LBDefautHuile);

        GLDefauts = new QGridLayout;
        GLDefauts->addLayout(HLDefautTreuil, 0, 0);
        GLDefauts->addLayout(HLDefautSurcharge, 0, 1);
        GLDefauts->addLayout(HLDefautVanne, 1, 0);
        GLDefauts->addLayout(HLDefautCentrale, 1, 1);
        GLDefauts->addLayout(HLDefautPompe, 2, 0);
        GLDefauts->addLayout(HLDefautMouCable, 2, 1);
        GLDefauts->addLayout(HLDefautLimiteurEffort, 3, 0);
        GLDefauts->addLayout(HLDefautArretUrgence, 3, 1);
        GLDefauts->addLayout(HLDefautCycle, 4, 0);
        GLDefauts->addLayout(HLDefautHuile, 4, 1);
        GBDefauts->setLayout(GLDefauts);

    GLMain = new QGridLayout(this);
    GLMain->setVerticalSpacing(10);
    GLMain->setHorizontalSpacing(20);
    GLMain->addWidget(GBAppareillages, 0, 0, 1, 2);
    GLMain->addWidget(GBNombreCycles, 0, 2);
    GLMain->addWidget(GBNiveaux, 1, 0, 1, 3);
    GLMain->addWidget(GBDefauts, 2, 0, 1, 3);

    setLayout(GLMain);
}

void StatutsDlg::allumerVoyant(QLabel *voyant, QString clr)
{
    voyant->setStyleSheet(clr);
}
