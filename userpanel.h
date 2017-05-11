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
    explicit UserPanel(int w, int h, PlayerConfigurationsHandler* playerConfigurationsHandler, QWidget *parent = 0);
    ~UserPanel();

private slots:
    void nothing()
    {
        return;
    };

    void on_textEdit_textChanged();

    void on_pushButton_clicked();

    void on_five_toggled(bool checked);

    void on_four_toggled(bool checked);

    void on_three_toggled(bool checked);

    void on_two_toggled(bool checked);

    void on_one_toggled(bool checked);

    void on_proccedButton_clicked();

    void WriteToFile();

    void on_proccedButton_2_clicked();

    void on_proccedButton_3_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_activated(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_highlighted(int index);

    void on_five_2_toggled(bool checked);

    void on_four_2_toggled(bool checked);

    void on_two_2_toggled(bool checked);

    void on_three_2_toggled(bool checked);

    void on_six_2_toggled(bool checked);

    void on_seven_2_toggled(bool checked);

    void on_one_2_toggled(bool checked);

    void on_proccedButton_4_clicked();

    void StartPlayback();

public:

    PlayerConfigurationsHandler* GetConfigHandler()
    {
        return configurationsHandler;
    }



public:
    Ui::UserPanel *ui;
public:
    QTimer* mTimer;
    bool states[5];
    bool states2[7];
    std::string testsOutputToFileString;
    PlayerConfigurationsHandler* configurationsHandler;
    int iActualPlayedMovie = 0;
    int height;
    int width;

    void UncheckToggles() const;
};

#endif // USERPANEL_H
