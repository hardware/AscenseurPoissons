#ifndef ACCUEILDLG_H
#define ACCUEILDLG_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

/**
 * @class AccueilDlg
 * @brief Classe representant l'onglet Accueil
 */
class AccueilDlg : public QWidget
{
    // Macro permettant de préparer le compilateur à utiliser les signaux et slots de Qt
    Q_OBJECT

    QVBoxLayout *vbox;
    QLabel      *LBTitre, *LBImgCentrale, *LBVersion;

public:
    // Explicit : interdit au compilateur de réaliser une conversion de typage implicite
    explicit AccueilDlg(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ACCUEILDLG_H
