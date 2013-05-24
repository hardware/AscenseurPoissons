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

class JournalDlg : public QWidget
{
    Q_OBJECT

    Seance *pSeance;

public:
    explicit JournalDlg(QWidget *parent = 0, Seance *seance = 0);
    
private:
    QStringList listeLignes;

    QVBoxLayout *VLMain;
    QListWidget *LWLogs;
    QComboBox   *CBNiveaux;
    QLabel      *LBText;

public slots:
    void afficherLog(QListWidgetItem *item);
    void ajouterLog(QString ligne, QString niveau);
    void trierListe(QString &niveau);
    QStringList LireFichierLog();

signals:
    
};

#endif // JOURNALDLG_H
