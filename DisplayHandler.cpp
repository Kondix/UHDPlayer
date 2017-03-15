#include "DisplayHandler.h"

void DisplayHandler::AddMedia()
{
    libvlc_media_player_set_media(m_pMediaPlayer, m_pMedia);
}

int DisplayHandler::AttachEvent(libvlc_event_type_t iEventType)
{
    return libvlc_event_attach(m_pEventManager, iEventType, HandleEvent, nullptr);
}

void DisplayHandler::HandleEvent(const libvlc_event_t* pEvt, void*)
{
    switch(pEvt->type)
    {
        case libvlc_MediaPlayerEndReached:
            std::cout << "MediaPlayerEndReached" << std::endl;
            m_bDone = true;
            break;
        default:
            std::cout << libvlc_event_type_name(pEvt->type) << std::endl;
    }
}

void DisplayHandler::Play(FramesHandler& framesHandler, RawDataHandler& rdh)
{
    libvlc_media_player_play(m_pMediaPlayer);

    while (!m_bDone) {

       // sleep(1);
    }

    ReleaseMedia();
}

void DisplayHandler::ReleaseMedia()
{
    libvlc_media_release(m_pMedia);
}