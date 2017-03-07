#include <vector>
#include <fstream>
#include <iostream>
#include "RawDataHandler.h"

void RawDataHandler::GetFrame(int iFrameSize, char* cBuffer)
{
    m_pFileOpener->GetInputFileStream().read(cBuffer, iFrameSize);
}