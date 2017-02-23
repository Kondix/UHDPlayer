#include "Controler.h"

    std::string sFileLocation = "/home/kjagielski/CLionProjects/UHDPlayer/sampleVideos/tractor.mp4";
    bool DisplayHandler::m_bDone = false;
    int main()
    {
        Controler ctrl(sFileLocation);
        ctrl.Run();
        return 0;
    }