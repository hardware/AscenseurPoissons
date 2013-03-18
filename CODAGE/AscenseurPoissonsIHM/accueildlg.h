#ifndef ACCUEILDLG_H
#define ACCUEILDLG_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

class AccueilDlg : public QWidget
{
    Q_OBJECT

public:
    explicit AccueilDlg(QWidget *parent = 0);

private:
    QVBoxLayout *vbox;
    QLabel      *LBTitre, *LBImgCentrale, *LBVersion;
    
signals:
    
public slots:
    
};

#endif // ACCUEILDLG_H
