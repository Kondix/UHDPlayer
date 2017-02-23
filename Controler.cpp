#include "Controler.h"

void Controler::Run()
{
    m_DisplayHandler->AttachEvent(libvlc_MediaPlayerEndReached);
    m_DisplayHandler->Play();
}