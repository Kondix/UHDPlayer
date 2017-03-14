//
// Created by barti on 11.03.17.
//

#ifndef UHDPLAYER_THREADSHANDLER_H
#define UHDPLAYER_THREADSHANDLER_H

#include <thread>
#include <vector>
#include "Controler.h"

class Threadshandler {

private:
    std::vector<std::thread*> m_ThreadsVector;

public:


public:
    void AddThread(std::thread* thread)
    {
        m_ThreadsVector.push_back(thread);
    }
    void CreateNFramesGetterThreads(int countOfThreads, RawDataHandler *rawDataHandler, FramesHandler *framesHandler, int iFrameSize, char *buffer)
    {
        for (int i = 0; i < countOfThreads; ++i) {
            std::thread thread = std::thread(&Threadshandler::GetFrameToBuffer, this, rawDataHandler, framesHandler, iFrameSize, buffer);
            thread.detach();
            AddThread(&thread);
        }
    }

    void GetFrameToBuffer(RawDataHandler *rawDataHandler, FramesHandler *framesHandler, int iFrameSize, char *buffer)
    {
        while (!DisplayHandler::m_bDone && !rawDataHandler->GetEof())
        {

            m_mtx.lock();
            if(framesHandler->GetFramesCount()<3)
            {
            rawDataHandler->GetFrame(iFrameSize, buffer);
            framesHandler->AddFrame(buffer);
            }
            m_mtx.unlock();
            //std::this_thread::sleep_for(std::chrono::microseconds(40000));
        }
        if(rawDataHandler->GetEof())
            return;

    }
};


#endif //UHDPLAYER_THREADSHANDLER_H
