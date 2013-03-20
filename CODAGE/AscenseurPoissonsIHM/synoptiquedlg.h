#ifndef SYNOPTIQUEDLG_H
#define SYNOPTIQUEDLG_H

#include "seance.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

class SynoptiqueDlg : public QWidget
{
    Q_OBJECT

    Seance *pSeance;

public:
    explicit SynoptiqueDlg(QWidget *parent = 0, Seance *ptSeance = 0);

private:
    QVBoxLayout *VLMain;
    QLabel *LBSchema;
    QProgressBar *PrBAscenseur;
    
signals:
    
public slots:
    
};

#endif // SYNOPTIQUEDLG_H
