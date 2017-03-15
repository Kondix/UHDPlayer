#include "Controler.h"

void Controler::Run(FramesHandler& framesHandler, RawDataHandler& rdh)
{
    m_DisplayHandler->AttachEvent(libvlc_MediaPlayerEndReached);
    m_DisplayHandler->Play(framesHandler, rdh);
}