﻿#ifndef JOURNALDLG_H
#define JOURNALDLG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMessageBox>

class JournalDlg : public QWidget
{
    Q_OBJECT

public:
    explicit JournalDlg(QWidget *parent = 0);
    
private:
    QVBoxLayout *VLMain;
    QListWidget *LWLogs;

public slots:
    void afficherLog(QListWidgetItem *item);

signals:
    
};

#endif // JOURNALDLG_H