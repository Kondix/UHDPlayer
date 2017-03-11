//
// Created by barti on 11.03.17.
//

#ifndef UHDPLAYER_THREADSHANDLER_H
#define UHDPLAYER_THREADSHANDLER_H

#include <thread>
#include <mutex>
#include <vector>
#include "Controler.h"

class Threadshandler {

private:
    std::vector<std::thread*> m_ThreadsVector;

public:
    std:: mutex m_mtx;

public:
    void AddThread(std::thread *thread)
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
    void JoinAll()
    {
        for(auto& item : m_ThreadsVector)
            (*item).detach();
    }
//    std::thread GetThread(int idx)
//    {
//        return m_ThreadsVector[idx];
//    }

    void GetFrameToBuffer(RawDataHandler *rawDataHandler, FramesHandler *framesHandler, int iFrameSize, char *buffer)
    {
        while (!DisplayHandler::m_bDone) {

            m_mtx.lock();
            rawDataHandler->GetFrame(iFrameSize, buffer);
            framesHandler->AddFrame(buffer);
           // std::cout<<framesHandler->GetFramesCount();
            m_mtx.unlock();
        }
    }
};


#endif //UHDPLAYER_THREADSHANDLER_H
