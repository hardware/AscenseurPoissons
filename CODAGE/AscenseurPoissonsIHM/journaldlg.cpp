#include "journaldlg.h"

JournalDlg::JournalDlg(QWidget *parent, Seance *ptSeance) : QWidget(parent), pSeance(ptSeance)
{
    QListWidgetItem *item = new QListWidgetItem(QString::fromUtf8("Jan 28 12:21:37 [DEFAUT] - Un défaut est survenu au niveau de la pompe FLYGT"));
    item->setForeground(QBrush(QColor("red")));
    item->setToolTip("DEFAUT");

    LWLogs = new QListWidget;
    LWLogs->setFont(QFont("Arial", 10));
    LWLogs->addItem(QString::fromUtf8("Jan 28 12:21:37 [INFO] - Une séance vient d'être paramétrée"));
    LWLogs->addItem(item);

    VLMain = new QVBoxLayout(this);
    VLMain->addWidget(LWLogs);

    setLayout(VLMain);

    QObject::connect(LWLogs, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(afficherLog(QListWidgetItem*)));
}

void JournalDlg::afficherLog(QListWidgetItem *item)
{
    if(item->toolTip() == "DEFAUT")
        QMessageBox::critical(this, item->toolTip(), item->text());
    else
        QMessageBox::information(this, item->toolTip(), item->text());

}
