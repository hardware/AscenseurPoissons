#include "journalevenements.h"

JournalEvenements::JournalEvenements() {}

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
