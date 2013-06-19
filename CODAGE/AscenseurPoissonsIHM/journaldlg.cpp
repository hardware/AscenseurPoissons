#include "journaldlg.h"

/**
 * @fn JournalDlg::JournalDlg(QWidget *parent, Seance *seance)
 * @brief Constructeur paramétré
 *
 * Ce constructeur pemet de définir l'organisation des widgets
 * de l'onglet Journal, de créer les slots permettant l'affichage
 * des logs ainsi que le trie des évènements.
 *
 * @param parent[in] Pointeur sur le widget parent
 * @param seance[in] Pointeur sur l'instance de la classe Seance
 */
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

/**
 * @fn void JournalDlg::afficherLog(QListWidgetItem *item)
 * @brief Permet d'afficher un évènement particulier
 *
 * Ensuite on initialise chaque onglet avec les instances des classes intermédiaires.
 *
 * @param item[in] L'évènement à afficher
 */
void JournalDlg::afficherLog(QListWidgetItem *item)
{
    QMessageBox::information(this, "INFORMATION", item->text());
}

/**
 * @fn QStringList JournalDlg::LireFichierLog()
 * @brief Permet de lire le fichier de log
 *
 * @return Retourne la liste des évènements contenus dans le fichier de log
 */
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

/**
 * @fn bool JournalDlg::ajouterLog(QString ligne, QString niveau)
 * @brief Permet de lire le fichier de log
 *
 * @param ligne[in] Message de l'évènement
 * @param niveau[in] Niveau de gravité de l'évènement
 *
 * @return Retourne TRUE si l'évènement a bien été ajouté
 */
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

/**
 * @fn void JournalDlg::trierListe(QString &niveau)
 * @brief Permet de trier la liste des évènements
 *
 * @param niveau[in] Niveau de gravité de l'évènement
 */
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
