#ifndef UHDPLAYER_THREADSHANDLER_H
#define UHDPLAYER_THREADSHANDLER_H

#include <thread>
#include <vector>
#include "Controler.h"
#include "videopanel.h"
#include "userpanel.h"

class ThreadsHandler {

private:
    std::vector<std::thread*> m_ThreadsVector;

public:
    void AddThread(std::thread* thread);
    void CreateNFramesGetterThreads(int countOfThreads, RawDataHandler *rawDataHandler, FramesHandler *framesHandler, int iFrameSize);
    void GetFrameToBuffer(RawDataHandler *rawDataHandler, FramesHandler *framesHandler, int iFrameSize);
    void LoadFrameAndAddToQueue(int iFrameSize, FramesHandler* framesHandler, RawDataHandler* rawDataHandler);
    void PreloadCache(int iFrameSize, FramesHandler* framesHandler, RawDataHandler* rawDataHandler);
    void StopPlayBackThread(VideoPanel* video, UserPanel* userPanel);
    void StopPlayBack(VideoPanel* video, UserPanel* userPanel);
};


#endif //UHDPLAYER_THREADSHANDLER_H
