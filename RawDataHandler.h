#include "FileOpener.h"
#include <vector>

#ifndef UHDPLAYER_RAWDATAHANDLER_H
#define UHDPLAYER_RAWDATAHANDLER_H


class RawDataHandler {
private:
    FileOpener* m_pFileOpener;
    bool eofFlag = false;
public:
    RawDataHandler(std::string sFileLocation)
    {
        m_pFileOpener = new FileOpener(sFileLocation);
    }

    ~RawDataHandler()
    {
        delete m_pFileOpener;
    }

    void GetFrame(int iFrameSize, char* cBuffer);
    bool GetEof(){ return eofFlag;}
};


#endif //UHDPLAYER_RAWDATAHANDLER_H
