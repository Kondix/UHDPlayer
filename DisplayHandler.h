#include <unistd.h>
#include <vlc/vlc.h>
#include <string>
#include <vector>
#include <iostream>

#ifndef UHDPLAYER_DISPLAYHANDLER_H
#define UHDPLAYER_DISPLAYHANDLER_H


class DisplayHandler {
private:
    libvlc_media_player_t* m_pMediaPlayer;
    libvlc_event_manager_t* m_pEventManager;
    libvlc_media_t* m_pMedia;
    libvlc_instance_t* m_libvlc_instance;

private:
    void AddMedia();

public:

    DisplayHandler(libvlc_instance_t* pVLCInstance, libvlc_media_t* pMedia) : m_pMedia(pMedia), m_libvlc_instance(pVLCInstance)
    {
//        std::vector<const char*> options;
//        std::vector<const char*>::iterator option;
//        options.push_back(":sout=#transcode{venc=ffmpeg{keyint=1,min-keyint=1,tune=zerolatency,bframes=0,vbv-bufsize=1200}, vcodec=mp2v,vb=800}:rtp{sdp=rtsp://:1234/BigDog}");
//
////        // Set media options
//       for(option = options.begin(); option != options.end(); option++)
//           libvlc_media_add_option(m_pMedia, *option);
////        }
//
//
////        m_pMediaPlayer = libvlc_media_player_new_from_media(m_pMedia);
////        ReleaseMedia();
        m_pMediaPlayer = libvlc_media_player_new(pVLCInstance);
        m_pEventManager = libvlc_media_player_event_manager(m_pMediaPlayer);
        AddMedia();
    };

public:
    static bool m_bDone;

public:
    int AttachEvent(libvlc_event_type_t iEventType);
    static void HandleEvent(const libvlc_event_t* pEvt, void*);
    void Play();
    void ReleaseMedia();

};


#endif //UHDPLAYER_DISPLAYHANDLER_H
