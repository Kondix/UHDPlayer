#include "Controler.h"
#include "FileOpener.h"
#include "RawDataHandler.h"

const int iFrameW = 1920;
const int iFrameH = 1080;
const int iFrameDepth = 32;
const int iBitByte = 8;

std::string sFileLocation = "/home/kjagielski/CLionProjects/UHDPlayer/sampleVideos/tractor.raw";
    bool DisplayHandler::m_bDone = false;

int myImemGetCallback (void *data, const char *cookie, int64_t *dts, int64_t *pts, unsigned *flags, size_t * bufferSize, void ** buffer)
{

}

int MyImemReleaseCallback (void *data, const char *cookie, size_t bufferSize, void * buffer)
{
    return 0;
}

    int main()
    {
        RawDataHandler rdh(sFileLocation);
        rdh.GetFrame(iFrameH*iFrameW*iFrameDepth/iBitByte);



        std::vector<const char*> options;
        options.push_back("--no-video-title-show");
        options.push_back("--imem-data=" + &data);
        options.push_back("--imem-get=" + myImemGetCallback);
        options.push_back("--imem-release=" + MyImemReleaseCallback);
        options.push_back("--imem-cookie=\"IMEM\"");
        options.push_back("--imem-codec=I420");
        // Video data.
        options.push_back("--imem-cat=2");

        options.push_back("--imem-width=" + iFrameW);
        options.push_back("--imem-height=" + iFrameH);
        options.push_back("--imem-channels=" + iFrameDepth);

        Controler ctrl(sFileLocation, options);
        ctrl.Run();
        return 0;
    }