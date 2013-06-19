#ifndef JOURNALDLG_H
#define JOURNALDLG_H

#include "seance.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QDateTime>
#include <QComboBox>
#include <QLabel>

/**
 * @class JournalDlg
 * @brief Classe representant l'onglet Journal
 */
class JournalDlg : public QWidget
{
    Q_OBJECT

    /**
     * Pointeur contenant l'adresse d'une instance de la classe Seance
     */
    Seance *pSeance;

    /**
     * Liste contenant les lignes du fichier log
     */
    QStringList listeLignes;

    QVBoxLayout *VLMain;
    QListWidget *LWLogs;
    QComboBox   *CBNiveaux;
    QLabel      *LBText;

public:
    explicit JournalDlg(QWidget *parent = 0, Seance *seance = 0);


public slots:
    void afficherLog(QListWidgetItem *item);
    bool ajouterLog(QString ligne, QString niveau);
    void trierListe(QString &niveau);
    QStringList LireFichierLog();

signals:
    
};

#endif // JOURNALDLG_H
