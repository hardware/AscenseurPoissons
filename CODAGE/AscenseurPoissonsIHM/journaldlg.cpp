#include "journaldlg.h"

JournalDlg::JournalDlg(QWidget *parent) : QWidget(parent)
{
    QListWidgetItem *item = new QListWidgetItem(QString::fromUtf8("Jan 28 12:21:37 [DEFAUT] - Un défaut est survenu au niveau de la pompe FLYGT"));
    item->setForeground(QBrush(QColor("red")));

    LWLogs = new QListWidget;
    LWLogs->setFont(QFont("Arial", 10));
    LWLogs->addItem(QString::fromUtf8("Jan 28 12:21:37 [INFO] - Une séance vient d'être paramétrée"));
    LWLogs->addItem(item);

    VLMain = new QVBoxLayout(this);
    VLMain->addWidget(LWLogs);

    setLayout(VLMain);
}
