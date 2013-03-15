#ifndef UI_H
#define UI_H

#include <QWidget>

namespace Ui {
class UI;
}

class UI : public QWidget
{
    Q_OBJECT
    
public:
    explicit UI(QWidget *parent = 0);
    ~UI();
    
private slots:
    void on_BP_Seance_Enregistrer_clicked();

private:
    Ui::UI *ui;
};

#endif // UI_H
