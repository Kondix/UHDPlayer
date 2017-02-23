#include <fstream>
#include <iostream>

#ifndef UHDPLAYER_FILEOPENER_H
#define UHDPLAYER_FILEOPENER_H


class FileOpener {
private:
    std::fstream m_fsInputFile;
public:
    FileOpener(std::string sFileLocation)
    {
        m_fsInputFile.open(sFileLocation, std::fstream::in);
    };

    std::fstream& GetInputFileStream() { return m_fsInputFile; }
};


#endif //UHDPLAYER_FILEOPENER_H
