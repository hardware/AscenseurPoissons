#ifndef SEANCEDLG_H
#define SEANCEDLG_H

#include "seance.h"
#include "types.h"

#include <QWidget>
#include <QBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSettings>
#include <QMessageBox>
#include <QApplication>

class SeanceDlg : public QWidget
{
    Q_OBJECT

    Seance *pSeance;

public:
    explicit SeanceDlg(QWidget *parent = 0, Seance *ptSeance = 0);
    
private:
    QVBoxLayout *vbox, *vboxTempsPeche, *vboxTempsVidange;
    QHBoxLayout *hbox;
    QGridLayout *GLMain;
    QGridLayout *GLPv, *GLGv, *GLTempsPeche, *GLTempsVidange, *GLNombreCycles, *GLPeriodicite;
    QGroupBox   *GBPv, *GBGv, *GBTempsPeche, *GBTempsVidange, *GBNombreCycles, *GBPeriodicite;
    QLineEdit   *LEPv, *LEGv, *LETempsPeche, *LETempsVidange, *LENombreCycles, *LEPeriodicite;
    QPushButton *PBPvPlus, *PBPvMoins,
                *PBGvPlus, *PBGvMoins,
                *PBTempsPechePlus,   *PBTempsPecheMoins,
                *PBTempsVidangePlus, *PBTempsVidangeMoins,
                *PBNombreCyclesPlus, *PBNombreCyclesMoins,
                *PBPeriodicitePlus,  *PBPeriodiciteMoins,
                *PBSeanceEnregistrer, *PBSeanceLancer, *PBSeanceArreter;

    QLabel *LBTempsPeche, *LBTempsVidange, *LBPeriodicite;
    QSettings *params;

public slots:
    void augmenterPV();
    void augmenterGV();
    void augmenterTempsPeche();
    void augmenterTempsVidange();
    void augmenterNombreCycles();
    void augmenterPeriodicite();

    void diminuerPV();
    void diminuerGV();
    void diminuerTempsPeche();
    void diminuerTempsVidange();
    void diminuerNombreCycles();
    void diminuerPeriodicite();

    void enregistrerParametres();
    void lancerAutomatisation();
    void arreterAutomatisation();

signals:
    
};

#endif // SEANCEDLG_H
