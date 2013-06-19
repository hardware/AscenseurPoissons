#ifndef IHM_H
#define IHM_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>

#include "seance.h"
#include "accueildlg.h"
#include "manueldlg.h"
#include "seancedlg.h"
#include "statutsdlg.h"
#include "synoptiquedlg.h"
#include "journaldlg.h"

/**
 * @class IHM
 * @brief Classe representant l'IHM
 */
class IHM : public QWidget
{
    Q_OBJECT

    /**
     * Pointeur contenant l'adresse d'une instance de la classe Seance
     */
    Seance seance;

    QBoxLayout *layout;
    QTabWidget *onglets;

    /*
    Classes intermédiaires représentant les onglets de l'app
    */
    AccueilDlg *accueilDlg;
    ManuelDlg *manuelDlg;
    SeanceDlg *seanceDlg;
    StatutsDlg *statutsDlg;
    SynoptiqueDlg *synoptiqueDlg;
    JournalDlg *journalDlg;
    
public:
    explicit IHM(QWidget *parent = 0);


signals:

public slots:


};

#endif // IHM_H
