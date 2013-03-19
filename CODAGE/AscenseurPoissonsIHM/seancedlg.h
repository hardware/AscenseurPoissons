﻿#ifndef SEANCEDLG_H
#define SEANCEDLG_H

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

public:
    explicit SeanceDlg(QWidget *parent = 0);
    
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
    void diminuerPV();
    void enregistrerParametres();

signals:
    
};

#endif // SEANCEDLG_H