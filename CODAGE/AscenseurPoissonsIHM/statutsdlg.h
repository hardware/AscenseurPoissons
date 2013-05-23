#ifndef STATUTSDLG_H
#define STATUTSDLG_H

#include "seance.h"
#include "types.h"

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QBoxLayout>
#include <QString>

class StatutsDlg : public QWidget
{
    Q_OBJECT

    Seance *pSeance;

    QGridLayout *GLMain, *GLAppareillages, *GLNiveaux, *GLDefauts;

    QVBoxLayout *VLPompe,       *VLCentrale,   *VLNombreCycles,
                *VLNiveauAmont, *VLNiveauAval, *VLNiveauHuile;

    QHBoxLayout *HLDefautTreuil,         *HLDefautVanne,    *HLDefautPompe,
                *HLDefautLimiteurEffort, *HLDefautCycle,    *HLDefautSurcharge,
                *HLDefautCentrale,       *HLDefautMouCable, *HLDefautArretUrgence,
                *HLDefautHuile;

    QGroupBox   *GBAppareillages, *GBNombreCycles, *GBNiveaux, *GBDefauts;

    QLineEdit   *LENombreCycles, *LENiveauAmont, *LENiveauAval, *LENiveauHuile;

    QLabel      *LBPompe, *LBCentrale, *LBNombreCycles,

                // Liste des niveaux
                *LBNiveauAmont, *LBNiveauAval, *LBNiveauHuile,

                // Liste des défauts
                *LBDefautTreuil,         *LBDefautVanne,    *LBDefautPompe,
                *LBDefautLimiteurEffort, *LBDefautCycle,    *LBDefautSurcharge,
                *LBDefautCentrale,       *LBDefautMouCable, *LBDefautArretUrgence,
                *LBDefautHuile;

public:

           // Liste des voyants
    QLabel *LBVoyantPompe, *LBVoyantCentrale,
           *LBVoyantNiveauAmont, *LBVoyantNiveauAval,
           *LBVoyantNiveauHuile,

           // Liste des voyants des défauts
           *LBVoyantDefautTreuil,         *LBVoyantDefautVanne,    *LBVoyantDefautPompe,
           *LBVoyantDefautLimiteurEffort, *LBVoyantDefautCycle,    *LBVoyantDefautSurcharge,
           *LBVoyantDefautCentrale,       *LBVoyantDefautMouCable, *LBVoyantDefautArretUrgence,
           *LBVoyantDefautHuile;


    explicit StatutsDlg(QWidget *parent = 0, Seance *ptSeance = 0);

signals:
    
public slots:
    void allumerVoyant(QLabel *voyant, QString clr);
    
};

#endif // STATUTSDLG_H
