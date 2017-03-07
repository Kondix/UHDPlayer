#ifndef UHDPLAYER_TYPES_H
#define UHDPLAYER_TYPES_H

#include <string>
#include <vector>

const int iFrameW = 1920;
const int iFrameH = 1080;
const int iFrameDepth = 32;
const int iBitByte = 8;
const int iMovieByteSize = iFrameW*iFrameH*iFrameDepth/iBitByte;
const int64_t iFPS = 33333;
const std::string sFileLocation = "/home/kjagielski/CLionProjects/UHDPlayer/sampleVideos/tractor.raw";

typedef char* Frame;

class FramesHandler
{
private:
    std::vector<Frame> m_vFrames;
    int64_t m_iDts;
    int64_t m_iPts;

public:
    FramesHandler() : m_vFrames(0), m_iDts(0), m_iPts(0) {}
    ~FramesHandler() {}

    int64_t& GetDts() { return m_iDts; }
    Frame& GetFrame(int iIdx) { return m_vFrames[iIdx]; }
    size_t GetFramesCount() { return m_vFrames.size(); }
    std::vector<Frame>& GetFrames() { return m_vFrames; }
    int64_t& GetPts() { return m_iPts; }
    void AddFrame(Frame frame) { m_vFrames.push_back(frame); }
    void ClearFrames () { m_vFrames.clear(); }
    void SetDts(int64_t iDts) { m_iDts = iDts; }
    void SetPts(int64_t iPts) { m_iDts = iPts; }

};

#endif //UHDPLAYER_TYPES_H
