#include "Controler.h"

void Controler::Run(FramesHandler& framesHandler, RawDataHandler& rdh, char* cBuffer)
{
    m_DisplayHandler->AttachEvent(libvlc_MediaPlayerEndReached);
    m_DisplayHandler->Play(framesHandler, rdh, cBuffer);
}