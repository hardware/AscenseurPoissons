#include "journalevenements.h"

JournalEvenements::JournalEvenements() {}

/**
 * @fn bool JournalDlg::ajouterLog(QString ligne, QString niveau)
 * @brief Permet de lire le fichier de log
 *
 * @param ligne[in] Message de l'évènement
 * @param niveau[in] Niveau de gravité de l'évènement
 *
 * @return Retourne TRUE si l'évènement a bien été ajouté
 */
bool JournalEvenements::ajouterLog(QString ligne, QString niveau)
{
     QFile file(QApplication::applicationDirPath() + "/journal.log");

     if(file.open(QFile::Append | QFile::Text))
     {
        ligne = QDateTime::currentDateTime().toString("MMM d hh:mm:ss") + " [" + niveau + "] - " + ligne;
        QTextStream out(&file);
        out << ligne << "\n";
        file.close();

        listeLignes.push_back(ligne);

        return true;
     }
     else
         return false;
}
