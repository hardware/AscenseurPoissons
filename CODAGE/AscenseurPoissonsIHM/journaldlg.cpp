#include "journaldlg.h"

JournalDlg::JournalDlg(QWidget *parent, Seance *seance) : QWidget(parent), pSeance(seance)
{
    LWLogs = new QListWidget;
    LWLogs->setFont(QFont("Arial", 10));
    LWLogs->addItems(LireFichierLog());

    LBText = new QLabel;
    LBText->setFont(QFont("Arial", 11));
    LBText->setText("Selectionner un niveau d'alerte :");

    CBNiveaux = new QComboBox;
    CBNiveaux->setFont(QFont("Arial", 18));
    CBNiveaux->addItem("INFO");
    CBNiveaux->addItem("NOTICE");
    CBNiveaux->addItem("WARNING");
    CBNiveaux->addItem("DEFAULT");
    CBNiveaux->addItem("ERROR");
    CBNiveaux->addItem("CRITICAL");
    CBNiveaux->addItem("ALERT");
    CBNiveaux->addItem("EMERG");

    VLMain = new QVBoxLayout(this);
    VLMain->addWidget(LWLogs);
    VLMain->addWidget(LBText);
    VLMain->addWidget(CBNiveaux);

    setLayout(VLMain);

    QObject::connect(LWLogs, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(afficherLog(QListWidgetItem*)));
    QObject::connect(CBNiveaux, SIGNAL(currentIndexChanged(QString&)), this, SLOT(trierListe(QString&)));
}

void JournalDlg::afficherLog(QListWidgetItem *item)
{
    QMessageBox::information(this, "INFORMATION", item->text());
}

QStringList JournalDlg::LireFichierLog()
{
    QString ligne;
    QFile file(QApplication::applicationDirPath() + "/journal.log");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        while ( ! in.atEnd() )
        {
            ligne = in.readLine();
            listeLignes.push_back(ligne);
        }

        file.close();
    }

    return listeLignes;
}

bool JournalDlg::ajouterLog(QString ligne, QString niveau)
{
     QFile file(QApplication::applicationDirPath() + "/journal.log");

     if(file.open(QFile::Append | QFile::Text))
     {
        ligne = QDateTime::currentDateTime().toString("MMM d hh:mm:ss") + " [" + niveau + "] - " + ligne;
        QTextStream out(&file);
        out << ligne << "\n";
        file.close();

        listeLignes.push_back(ligne);
        LWLogs->addItem(ligne);

        return true;
     }
     else
         return false;
}

void JournalDlg::trierListe(QString &niveau)
{
    QStringList liste;
    QList<QListWidgetItem*> tmpList = LWLogs->findItems(niveau, Qt::MatchContains);

    for (int i = 0; i < tmpList.size(); i++)
    {
        liste.append(tmpList.at(i)->text());
    }

    LWLogs->clear();
    LWLogs->addItems(liste);
}
