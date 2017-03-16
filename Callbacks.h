#ifndef UHDPLAYER_CALLBACKS_H
#define UHDPLAYER_CALLBACKS_H

#include <cstdint>
#include <unistd.h>
#include "Types.h"
#include "ThreadsHandler.h"

namespace Callbacks
{

    int MyImemGetCallback (void* data, const char* , int64_t *dts, int64_t *pts, unsigned* , size_t* bufferSize, void** buffer)
    {
        g_mtx.lock();
        FramesHandler* framesHandler = (FramesHandler*)data;

        *bufferSize = iFrameH*iFrameW*iFrameDepth/iBitByte;

        if (framesHandler->GetFramesCount() > 0)
        {
            *buffer = framesHandler->GetFrame(0);

            int64_t iSetUp = framesHandler->GetPts() + iFPS;

            framesHandler->SetDts(iSetUp);
            framesHandler->SetPts(iSetUp);
            *dts = *pts = iSetUp;
        }
        g_mtx.unlock();
        return 0;
    }

    int MyImemReleaseCallback (void* data, const char* , size_t , void* )
    {
        g_mtx.lock();
        FramesHandler* framesHandler = (FramesHandler*)data;
        if (framesHandler->GetFramesCount() > 1)
        {
            framesHandler->ClearFirstFrame();
        }
        if(framesHandler->m_bNothingElseInFile && framesHandler->GetFramesCount() <= 1)
        {
            framesHandler->ClearFrames();
            DisplayHandler::m_bDone = true;
        }
        g_mtx.unlock();
        return 0;
    }
}

#endif //UHDPLAYER_CALLBACKS_H
