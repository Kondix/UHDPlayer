#ifndef UHDPLAYER_TYPES_H
#define UHDPLAYER_TYPES_H

#include <string>
#include <vector>
#include <deque>
#include <mutex>

const int iFrameW = 1920;
const int iFrameH = 1080;
const int iFrameDepth = 12;
const int iBitByte = 8;
static int iMovieByteSize = 0;
const int iMaxFramesInQueue = 5;
static int64_t iFPS = 40000;
const std::string sConfigFileLocation = "/home/barti/CLionProjects/UHDPlayer/config.txt";
const std::string sFileLocation = "/home/barti/CLionProjects/UHDPlayer/sampleVideos/tractor.raw";
static std:: mutex g_mtx;


const bool bShouldPreloadCache = false;

typedef char* Frame;


class FramesHandler
{
private:
    std::deque<Frame> m_vFrames;
    int64_t m_iDts;
    int64_t m_iPts;

public:
    bool m_bNothingElseInFile = false;

public:
    FramesHandler() : m_vFrames(0), m_iDts(0), m_iPts(0) {}
    ~FramesHandler() {}

    void AddFrameToDeque    (Frame frame) { m_vFrames.push_back(frame); }
    void ClearFrames        ()            { m_vFrames.clear(); }
    void ClearFirstFrame    ()
    {
        Frame t_toDeleteFrame = m_vFrames.front();
        m_vFrames.erase(m_vFrames.begin());
        delete(t_toDeleteFrame);
    }
    int64_t& GetDts         ()            { return m_iDts; }
    Frame& GetFrame         (int iIdx)    { return m_vFrames[iIdx]; }
    size_t GetFramesCount   ()            { return m_vFrames.size(); }
    std::deque<Frame>& GetFrames()        { return m_vFrames; }
    int64_t& GetPts()                     { return m_iPts; }
    void SetDts(int64_t iDts)             { m_iDts = iDts; }
    void SetPts(int64_t iPts)             { m_iPts = iPts; }
};

#endif //UHDPLAYER_TYPES_H
