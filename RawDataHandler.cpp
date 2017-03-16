#include <vector>
#include <fstream>
#include <iostream>
#include "RawDataHandler.h"
#include "Types.h"

bool RawDataHandler::LoadFrameToFromStreamToBuffer(int iFrameSize, char *cBuffer)
{    if(m_pFileOpener->GetInputFileStream().eof())
    {
        return false;
    }
    m_pFileOpener->GetInputFileStream().read(cBuffer, iFrameSize);
    return true;

}