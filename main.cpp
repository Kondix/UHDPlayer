#include "Controler.h"
#include "FileOpener.h"
#include "RawDataHandler.h"

const int iFrameH = 1920;
const int iFrameW = 1080;
const int iFrameDepth = 32;
const int iBitByte = 8;

std::string sFileLocation = "/home/kjagielski/CLionProjects/UHDPlayer/sampleVideos/tractor.raw";
    bool DisplayHandler::m_bDone = false;
    int main()
    {
        RawDataHandler rdh(sFileLocation);
        rdh.GetFrame(iFrameH*iFrameW*iFrameDepth/iBitByte);
        //FileOpener fo(sFileLocation);
        //Controler ctrl(sFileLocation);
        //ctrl.Run();
        return 0;
    }