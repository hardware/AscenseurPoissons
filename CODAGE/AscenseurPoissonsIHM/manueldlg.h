#ifndef MANUELDLG_H
#define MANUELDLG_H

#include "seance.h"
#include "statutsdlg.h"
#include "journaldlg.h"
#include "ascpihmdef.h"

#include <QWidget>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>

class ManuelDlg : public QWidget
{
    Q_OBJECT

    Seance *pSeance;
    StatutsDlg *pStatutsDlg;
    JournalDlg *pJournalDlg;

public:
    explicit ManuelDlg(
        QWidget *parent = 0,
        Seance *seance = 0,
        StatutsDlg *statutsDlg = 0,
        JournalDlg *journalDlg = 0
    );

private:
    QGridLayout *GLMain, *GLCage;
    QGroupBox   *GBCage, *GBCentrale, *GBGrille, *GBPompe, *GBVanneAttrait;
    QHBoxLayout *hboxPompe, *hboxCentrale, *hboxVanneAttrait, *hboxGrille, *hboxCage;
    QPushButton *PBPompeDemarrer,
                *PBCentraleDemarrer, *PBCentraleArreter,
                *PBVanneAttraitOuvrir, *PBVanneAttraitFermer,
                *PBGrilleOuvrir, *PBGrilleFermer,
                *PBCageMPV, *PBCageMGV, *PBCageDPV, *PBCageDGV;
    
public slots:
    void on_PBPompeDemarrer_clicked();
    void on_PBCentraleDemarrer_clicked();
    void on_PBCentraleArreter_clicked();
    void on_PBVanneAttraitOuvrir_clicked();
    void on_PBVanneAttraitFermer_clicked();
    void on_PBGrilleOuvrir_clicked();
    void on_PBGrilleFermer_clicked();
    void on_PBMonterPV_clicked();
    void on_PBMonterGV_clicked();
    void on_PBDescendrePV_clicked();
    void on_PBDescendreGV_clicked();

signals:
    void allumerVoyant(QLabel *voyant);
    
};

#endif // MANUELDLG_H
