#ifndef ACCUEILDLG_H
#define ACCUEILDLG_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

class AccueilDlg : public QWidget
{
    // Macro permettant de préparer le compilateur à utiliser les signaux et slots de Qt
    Q_OBJECT

public:
    // Explicit : interdit au compilateur de réaliser une conversion de typage implicite
    explicit AccueilDlg(QWidget *parent = 0);

private:
    QVBoxLayout *vbox;
    QLabel      *LBTitre, *LBImgCentrale, *LBVersion;
    
signals:
    
public slots:
    
};

#endif // ACCUEILDLG_H
