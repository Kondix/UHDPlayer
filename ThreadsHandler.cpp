//
// Created by barti on 11.03.17.
//

#include "ThreadsHandler.h"


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

        m_mtx.lock();
        if(framesHandler->GetFramesCount()<iMaxFramesInQueue)
        {
            char* buffer = new char[iFrameSize];
            framesHandler->m_bNothingElseInFile = !rawDataHandler->LoadFrameToFromStreamToBuffer(iFrameSize, buffer);
            if(framesHandler->m_bNothingElseInFile)
                return;
            framesHandler->AddFrameToDeque(buffer);
        }
        m_mtx.unlock();
        //std::this_thread::sleep_for(std::chrono::microseconds(40000));
    }
    if(framesHandler->m_bNothingElseInFile)
        return;

}