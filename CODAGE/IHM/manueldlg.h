#ifndef MANUELDLG_H
#define MANUELDLG_H

#include <QWidget>

class ManuelDlg : public QWidget
{
    Q_OBJECT
public:
    explicit ManuelDlg(QWidget *parent = 0);
    
signals:
    
public slots:

private slots:
    void on_BP_Pompe_Demarrer_clicked();
    
};

#endif // MANUELDLG_H
