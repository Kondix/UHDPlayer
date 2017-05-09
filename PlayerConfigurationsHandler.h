//
// Created by barti on 18.04.17.
//

#ifndef UHDPLAYER_PLAYERCONFIGURATIONSHANDLER_H
#define UHDPLAYER_PLAYERCONFIGURATIONSHANDLER_H

#include <string>
#include <vector>
#include <fstream>
#include <MovieProperties.h>

class PlayerConfigurationsHandler {

public:

    PlayerConfigurationsHandler()
    {

    }

    ~PlayerConfigurationsHandler()
    {
        int count = moviesProperties.size();
        for(int i = 0; i < count; i++)
        {
            delete(moviesProperties[0]);
        }
    }

    PlayerConfigurationsHandler(std::string configTxtFilePath)
    {
        std::ifstream fileStream(configTxtFilePath);
        std::string line;
        std::string parameterName;
        std::string parameterValue;


        while(std::getline(fileStream,line))
        {
               if(line.find("config"))
               {
                   int idx = line.find("=");
                   configType = std::stoi(line.substr(idx+1, line.length()-1));
                   break;
               }
        }
        int iVideo = -1;

        while(fileStream >> parameterName >> parameterValue)
        {
            if(parameterName.find("video") != std::string::npos)
            {
                iVideo++;
                moviesProperties.push_back(new MovieProperties);
                moviesProperties[iVideo]->m_sName = parameterValue;
            }
            if(parameterName.find("path") != std::string::npos)
            {
                moviesProperties[iVideo]->m_sPath = parameterValue;
            }
            unsigned long nu = parameterName.find("width");
            if(parameterName.find("width") != std::string::npos)
            {
                moviesProperties[iVideo]->m_iWidth = std::stoi(parameterValue);
            }
            if(parameterName.find("height") != std::string::npos)
            {
                moviesProperties[iVideo]->m_iHeight = std::stoi(parameterValue);
            }
            if(parameterName.find("fps") != std::string::npos)
            {
                moviesProperties[iVideo]->m_iFps = std::stoi(parameterValue);
            }
            if(parameterName.find("depth") != std::string::npos)
            {
                moviesProperties[iVideo]->m_iFrameDepth = std::stoi(parameterValue);
            }
            if(parameterName.find("codec") != std::string::npos)
            {
                moviesProperties[iVideo]->m_sCodec = parameterValue;
            }
        }
        bIsConfigurationSetUp = true;
    }
private:
    int configType;
    std::vector<MovieProperties*> moviesProperties;
    bool bIsConfigurationSetUp = false;


public:
    int GetConfig()
    {
        return configType;
    }
    std::string GetPath(int index)
    {
        return moviesProperties[index]->m_sPath;
    }
    std::string GetName(int index)
    {
        return moviesProperties[index]->m_sName;
    }
    std::string GetCodec(int index)
    {
        return moviesProperties[index]->m_sCodec;
    }
    int GetWidth(int index)
    {
        return moviesProperties[index]->m_iWidth;
    }
    int GetHeight(int index)
    {
        return moviesProperties[index]->m_iHeight;
    }
    int GetFrameDepth(int index)
    {
        return moviesProperties[index]->m_iFrameDepth;
    }
    int GetFps(int index)
    {
        return moviesProperties[index]->m_iFps;
    }
    int GetMoviesCount()
    {
        return moviesProperties.size();
    }
    bool CheckConfiguration()
    {
        return  bIsConfigurationSetUp;
    }
    int GetRate(int index)
    {
        return moviesProperties[index]->rate;
    }
    void SetRate(int index, int t_rate)
    {
        moviesProperties[index]->rate = t_rate;
    }
};


#endif //UHDPLAYER_PLAYERCONFIGURATIONSHANDLER_H