#ifndef JOURNALEVENEMENTS_H
#define JOURNALEVENEMENTS_H

#include <QFile>
#include <QStringList>
#include <QApplication>
#include <QDateTime>
#include <QTextStream>

/**
 * @class JournalEvenements
 * @brief Classe representant le journal
 */
class JournalEvenements
{

    /**
     * Liste contenant les lignes du fichier log
     */
    QStringList listeLignes;

public:
    JournalEvenements();

    bool ajouterLog(QString ligne, QString niveau);

};

#endif // JOURNALEVENEMENTS_H
