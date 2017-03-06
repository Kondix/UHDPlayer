#include "Controler.h"
#include "FileOpener.h"
#include "RawDataHandler.h"

#include <iostream>
#include <fstream>

const int iFrameW = 1920;
const int iFrameH = 1080;
const int iFrameDepth = 32;
const int iBitByte = 12;

std::string sFileLocation = "/home/barti/CLionProjects/UHDPlayer/sampleVideos/tractorraw";
bool DisplayHandler::m_bDone = false;

class MyImemData
{
public:
    MyImemData() : mFrame(0), mDts(0), mPts(0) {}
    ~MyImemData() {}
    char* mFrame;
    int64_t mDts;
    int64_t mPts;
};

int MyImemGetCallback (void *data, const char *cookie, int64_t *dts, int64_t *pts, unsigned *flags, size_t * bufferSize, void ** buffer)
{
    MyImemData* imem = (MyImemData*)data;

    int64_t uS = 33333; // 60 fps

    *bufferSize = iFrameH*iFrameW*iFrameDepth/iBitByte;
    *buffer = imem->mFrame;
    *dts = *pts = imem->mDts = imem->mPts = imem->mPts + uS;

}

int MyImemReleaseCallback (void *data, const char *cookie, size_t bufferSize, void * buffer)
{
    return 0;
}
    int main()
    {
        RawDataHandler rdh(sFileLocation);

        const int iSize = iFrameH*iFrameW*iFrameDepth/iBitByte;
        char cStr[iSize];
        rdh.GetFrame(iSize, cStr);

        std::ofstream RawImageFile;
        RawImageFile.open ("RawImageFile.txt");
        RawImageFile << cStr;
        RawImageFile.close();

        MyImemData myImemData;
        myImemData.mFrame = cStr;

        std::vector<const char*> options;
        options.push_back("--no-video-title-show");

        char imemDataArg[256];
        sprintf(imemDataArg, "--imem-data=%p", &myImemData);
        options.push_back(imemDataArg);

        char imemGetArg[256];
        sprintf(imemGetArg, "--imem-get=%#p", MyImemGetCallback);
        options.push_back(imemGetArg);

        char imemReleaseArg[256];
        sprintf(imemReleaseArg, "--imem-release=%#p", MyImemReleaseCallback);
        options.push_back(imemReleaseArg);

        options.push_back("--imem-cookie=\"IMEM\"");
        options.push_back("--imem-codec=RV24");
        options.push_back("--imem-cookie=test");
        // Video data.
        options.push_back("--imem-cat=2");
        options.push_back("--imem-fps=30");
        char imemWidthArg[256];
        sprintf(imemWidthArg, "--imem-width=%d", iFrameW);
        options.push_back(imemWidthArg);

        char imemHeightArg[256];
        sprintf(imemHeightArg, "--imem-height=%d", iFrameH);
        options.push_back(imemHeightArg);

        char imemChannelsArg[256];
        sprintf(imemChannelsArg, "--imem-channels=%d", iFrameDepth);
        options.push_back(imemChannelsArg);

        options.push_back("--verbose=2");

        Controler ctrl(sFileLocation, options);
        ctrl.Run();

        return 0;
    }