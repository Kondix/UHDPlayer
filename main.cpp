#include "Callbacks.h"
#include "Controler.h"
#include "ImemOptionsHandler.h"
#include "RawDataHandler.h"

bool DisplayHandler::m_bDone = false;

    int main()
    {
        RawDataHandler rdh(sFileLocation);

        const int iSize = iFrameH*iFrameW*iFrameDepth/iBitByte;
        char cStr[iSize];
        rdh.GetFrame(iSize, cStr);

        FramesHandler framesHandler;
        framesHandler.AddFrame(cStr);

        ImemOptionsHandler optionsHandler;
        optionsHandler.AddOption("--no-video-title-show");
        optionsHandler.AddOption("--imem-codec=I420");
        optionsHandler.AddOption("--imem-cookie=test");
        optionsHandler.AddOption("--imem-cat=2");
        optionsHandler.AddOption("--verbose=2");

        char imemDataArg[256];
        sprintf(imemDataArg, "--imem-data=%p", &framesHandler);
        optionsHandler.AddOption(imemDataArg);

        char imemGetArg[256];
        sprintf(imemGetArg, "--imem-get=%#p", Callbacks::MyImemGetCallback);
        optionsHandler.AddOption(imemGetArg);

        char imemReleaseArg[256];
        sprintf(imemReleaseArg, "--imem-release=%#p", Callbacks::MyImemReleaseCallback);
        optionsHandler.AddOption(imemReleaseArg);

        char imemWidthArg[256];
        sprintf(imemWidthArg, "--imem-width=%d", iFrameW);
        optionsHandler.AddOption(imemWidthArg);

        char imemHeightArg[256];
        sprintf(imemHeightArg, "--imem-height=%d", iFrameH);
        optionsHandler.AddOption(imemHeightArg);

        char imemChannelsArg[256];
        sprintf(imemChannelsArg, "--imem-channels=%d", iFrameDepth);
        optionsHandler.AddOption(imemChannelsArg);

        Controler ctrl(sFileLocation, optionsHandler.GetOptions());
        ctrl.Run();

        return 0;
    }