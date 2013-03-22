#ifndef MANUELDLG_H
#define MANUELDLG_H

#include "seance.h"

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>

class ManuelDlg : public QWidget
{
    Q_OBJECT

    Seance *pSeance;

public:
    explicit ManuelDlg(QWidget *parent = 0, Seance *ptSeance = 0);

private:
    QGridLayout *GLMain, *GLCage;
    QGroupBox   *GBCage, *GBCentrale, *GBGrille, *GBPompe, *GBVanneAttrait;
    QHBoxLayout *hboxPompe, *hboxCentrale, *hboxVanneAttrait, *hboxGrille, *hboxCage;
    QPushButton *PBPompeDemarrer, *PBPompeArreter,
                *PBCentraleDemarrer, *PBCentraleArreter,
                *PBVanneAttraitOuvrir, *PBVanneAttraitFermer,
                *PBGrilleOuvrir, *PBGrilleFermer,
                *PBCageMPV, *PBCageMGV, *PBCageDPV, *PBCageDGV;
    
public slots:
    void demarrerPompe();
    void arreterPompe();
    void demarrerCentrale();
    void arreterCentrale();

signals:
    
};

#endif // MANUELDLG_H
