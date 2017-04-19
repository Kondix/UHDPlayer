#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>
#include <VLCQtCore/Common.h>
#include <QtGui/QScreen>
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

        QScreen* screen = app.primaryScreen();
        QRect screenRect = screen->availableGeometry();
        int height = screenRect.height();
        int width = screenRect.width();

        //VideoPanel w(ctrl.m_DisplayHandler->m_pMediaPlayer);
        //PlayerConfigurationsHandler config(sConfigFileLocation);

        MainWindow w(width,height);
        w.show();

        //ctrl.Run();

        return app.exec();
    }