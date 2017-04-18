#ifndef USERPANEL_H
#define USERPANEL_H

#include <QDialog>
#include "Controler.h"
#include "PlayerConfigurationsHandler.h"


namespace Ui {
class UserPanel;
}

class UserPanel : public QDialog
{
    Q_OBJECT

public:
    explicit UserPanel(PlayerConfigurationsHandler* playerConfigurationsHandler, QWidget *parent = 0);
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

    void on_pushButton_released();

    void StartPlayback();

    void WriteToFile();


public:
    Ui::UserPanel *ui;
private:
    bool states[5];
    std::string testsOutputToFileString;
    PlayerConfigurationsHandler* configurationsHandler;
    int iActualPlayedMovie = 0;
};

#endif // USERPANEL_H
