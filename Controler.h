#include <unistd.h>
#include <vlc/vlc.h>
#include <string>
#include <iostream>
#include <vector>
#include "DisplayHandler.h"
#include "Types.h"
#include "RawDataHandler.h"


#ifndef UHDPLAYER_CONTROLER_H
#define UHDPLAYER_CONTROLER_H

class Controler {
private:
    libvlc_instance_t* m_VLCInstance;
    libvlc_media_t* m_pMedia;
    DisplayHandler* m_DisplayHandler;
public:
    Controler(std::string sFileLocation)
    {
        m_VLCInstance = libvlc_new(0, nullptr);
        m_pMedia = libvlc_media_new_path(m_VLCInstance, sFileLocation.c_str());
        m_DisplayHandler = new DisplayHandler(m_VLCInstance, m_pMedia);
    };

    Controler(std::string sFileLocation, std::vector<const char*> vcOptions)
    {
        m_VLCInstance = libvlc_new(int(vcOptions.size()), vcOptions.data());
        m_pMedia = libvlc_media_new_location (m_VLCInstance, "imem://");
        m_DisplayHandler = new DisplayHandler(m_VLCInstance, m_pMedia);
    };

    virtual ~Controler()
    {
        libvlc_release(m_VLCInstance);
        delete m_DisplayHandler;
    };

public:
    void Run(FramesHandler& framesHandler, RawDataHandler& rdh);
};


#endif //UHDPLAYER_CONTROLER_H
