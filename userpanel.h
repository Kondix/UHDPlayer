#ifndef USERPANEL_H
#define USERPANEL_H

#include <QDialog>
#include "Controler.h"


namespace Ui {
class UserPanel;
}

class UserPanel : public QDialog
{
    Q_OBJECT

public:
    explicit UserPanel(QWidget *parent = 0);
    ~UserPanel();

private slots:
    void on_textEdit_textChanged();

    void on_pushButton_clicked();

    void on_five_toggled(bool checked);

    void on_four_toggled(bool checked);

    void on_three_toggled(bool checked);

    void on_two_toggled(bool checked);

    void on_one_toggled(bool checked);

    void on_proccedButton_clicked();

public:
    Ui::UserPanel *ui;
private:
    bool states[5];
};

#endif // USERPANEL_H
