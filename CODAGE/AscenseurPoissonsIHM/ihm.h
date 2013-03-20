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

class IHM : public QWidget
{
    Q_OBJECT

    Seance seance;
    
public:
    explicit IHM(QWidget *parent = 0);

private:
    QBoxLayout *layout;
    QTabWidget *onglets;

    // Classes intermédiaires représentant les onglets de l'app
    AccueilDlg *accueilDlg;
    ManuelDlg *manuelDlg;
    SeanceDlg *seanceDlg;
    StatutsDlg *statutsDlg;
    SynoptiqueDlg *synoptiqueDlg;
    JournalDlg *journalDlg;

signals:

public slots:


};

#endif // IHM_H
