#include "FileOpener.h"
#include <vector>

#ifndef UHDPLAYER_RAWDATAHANDLER_H
#define UHDPLAYER_RAWDATAHANDLER_H


class RawDataHandler {
private:
    FileOpener* m_pFileOpener;
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
};


#endif //UHDPLAYER_RAWDATAHANDLER_H
