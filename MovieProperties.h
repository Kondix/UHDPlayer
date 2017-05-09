//
// Created by barti on 18.04.17.
//
#include <string>

#ifndef UHDPLAYER_MOVIEPROPERTIES_H
#define UHDPLAYER_MOVIEPROPERTIES_H


class MovieProperties {

public:
    std::string m_sPath;
    std::string m_sName;
    int m_iWidth;
    int m_iHeight;
    int m_iFrameDepth;
    int m_iFps;
    std:: string m_sCodec;
    int rate = 0;

    MovieProperties()
    {

    }
    MovieProperties(std::string t_path, std::string t_name, int t_width, int t_height, int t_frameDepth, int t_fps, std::string t_Codec)
    {
        m_sPath = t_path;
        m_sName = t_name;
        m_iWidth = t_width;
        m_iHeight = t_height;
        m_iFrameDepth = t_frameDepth;
        m_iFps = t_fps;
        m_sCodec = t_Codec;
        rate = 0;
    }

};


#endif //UHDPLAYER_MOVIEPROPERTIES_H
