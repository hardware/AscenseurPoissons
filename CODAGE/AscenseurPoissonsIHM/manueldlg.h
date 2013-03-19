#ifndef MANUELDLG_H
#define MANUELDLG_H

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>

class ManuelDlg : public QWidget
{
    Q_OBJECT

public:
    explicit ManuelDlg(QWidget *parent = 0);

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
