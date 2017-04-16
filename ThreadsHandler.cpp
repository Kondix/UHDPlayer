#include "ThreadsHandler.h"
#include "videopanel.h"


void ThreadsHandler::AddThread(std::thread* thread)
{
m_ThreadsVector.push_back(thread);
}

void ThreadsHandler::CreateNFramesGetterThreads(int countOfThreads, RawDataHandler *rawDataHandler, FramesHandler *framesHandler, int iFrameSize)
{
    for (int i = 0; i < countOfThreads; ++i) {
        std::thread thread = std::thread(&ThreadsHandler::GetFrameToBuffer, this, rawDataHandler, framesHandler, iFrameSize);
        thread.detach();
        AddThread(&thread);
    }
}
void ThreadsHandler::GetFrameToBuffer(RawDataHandler *rawDataHandler, FramesHandler *framesHandler, int iFrameSize)
{
    while (!DisplayHandler::m_bDone)
    {
        g_mtx.lock();
        if(framesHandler->GetFramesCount()<iMaxFramesInQueue)
        {
            LoadFrameAndAddToQueue(iFrameSize, framesHandler, rawDataHandler);
        }
        g_mtx.unlock();
    }
    if(framesHandler->m_bNothingElseInFile)
        return;
}

void ThreadsHandler::PreloadCache(int iFrameSize, FramesHandler* framesHandler, RawDataHandler* rawDataHandler)
{
    while (!framesHandler->m_bNothingElseInFile)
    {
        LoadFrameAndAddToQueue(iFrameSize, framesHandler, rawDataHandler);
    }
}

void ThreadsHandler::LoadFrameAndAddToQueue(int iFrameSize, FramesHandler* framesHandler, RawDataHandler* rawDataHandler)
{
    char* buffer = new char[iFrameSize];
    framesHandler->m_bNothingElseInFile = !rawDataHandler->LoadFrameToFromStreamToBuffer(iFrameSize, buffer);
    if(framesHandler->m_bNothingElseInFile)
        return;
    framesHandler->AddFrameToDeque(buffer);
};


void ThreadsHandler::StopPlayBackThread(libvlc_media_player_t* mp, Controler* controler, VideoPanel* video)
{
    std::thread thread = std::thread(&ThreadsHandler::StopPlayBack, this, mp, controler, video);
    thread.join();
}

void ThreadsHandler::StopPlayBack(libvlc_media_player_t* mp, Controler* controler, VideoPanel* video)
{
    while (!DisplayHandler::m_bDone) {

        sleep(1);

    }

    libvlc_media_player_stop(mp);
    delete controler;
    delete video;

}