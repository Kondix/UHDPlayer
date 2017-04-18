#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>
#include <VLCQtCore/Common.h>
#include "ImemOptionsHandler.h"
#include "adminpanel.h"
#include "userpanel.h"
#include "mainwindow.h"
#include "videopanel.h"
#include "PlayerConfigurationsHandler.h"


bool DisplayHandler::m_bDone = false;

    int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);

        //VideoPanel w(ctrl.m_DisplayHandler->m_pMediaPlayer);
        //PlayerConfigurationsHandler config(sConfigFileLocation);

        MainWindow w;
        w.show();

        //ctrl.Run();

        return app.exec();
    }