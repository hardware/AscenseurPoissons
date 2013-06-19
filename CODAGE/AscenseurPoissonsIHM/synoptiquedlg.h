#ifndef SYNOPTIQUEDLG_H
#define SYNOPTIQUEDLG_H

#include "seance.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

/**
 * @class SynoptiqueDlg
 * @brief Classe representant l'onglet Synoptique
 */
class SynoptiqueDlg : public QWidget
{
    Q_OBJECT

    /**
     * Pointeur contenant l'adresse d'une instance de la classe Seance
     */
    Seance *pSeance;

public:
    explicit SynoptiqueDlg(QWidget *parent = 0, Seance *seance = 0);

private:
    QVBoxLayout *VLMain;
    QLabel *LBSchema;
    QProgressBar *PrBAscenseur;
    
signals:
    
public slots:
    
};

#endif // SYNOPTIQUEDLG_H
