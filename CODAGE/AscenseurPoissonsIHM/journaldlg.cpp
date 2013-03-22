#include "journaldlg.h"

JournalDlg::JournalDlg(QWidget *parent, Seance *ptSeance) : QWidget(parent), pSeance(ptSeance)
{
    LWLogs = new QListWidget;
    LWLogs->setFont(QFont("Arial", 10));
    LWLogs->addItems(LireFichierLog());

    VLMain = new QVBoxLayout(this);
    VLMain->addWidget(LWLogs);

    setLayout(VLMain);

    QObject::connect(LWLogs, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(afficherLog(QListWidgetItem*)));
}

void JournalDlg::afficherLog(QListWidgetItem *item)
{
    QMessageBox::information(this, "INFORMATION", item->text());
}

QStringList JournalDlg::LireFichierLog()
{
    QString ligne;
    QFile file(QApplication::applicationDirPath() + "/logs.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        while ( ! in.atEnd() )
        {
            ligne = in.readLine();
            listeLignes.push_back(ligne);
        }
    }

    return listeLignes;
}
