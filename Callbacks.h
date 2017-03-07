#ifndef UHDPLAYER_CALLBACKS_H
#define UHDPLAYER_CALLBACKS_H

#include <cstdint>
#include <unistd.h>
#include "Types.h"


namespace Callbacks
{
    int MyImemGetCallback (void *data, const char *cookie, int64_t *dts, int64_t *pts, unsigned *flags, size_t * bufferSize, void ** buffer)
    {
        FramesHandler* framesHandler = (FramesHandler*)data;

        *bufferSize = iFrameH*iFrameW*iFrameDepth/iBitByte;
        *buffer = framesHandler->GetFrame(0);

        int64_t iSetUp = framesHandler->GetPts() + iFPS;
        framesHandler->SetDts(iSetUp);
        framesHandler->SetPts(iSetUp);
        *dts = *pts = iSetUp;

        return 0;
    }

    int MyImemReleaseCallback (void *data, const char *cookie, size_t bufferSize, void * buffer)
    {
        return 0;
    }
}

#endif //UHDPLAYER_CALLBACKS_H
