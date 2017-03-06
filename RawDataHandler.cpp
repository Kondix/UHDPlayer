#include <vector>
#include <fstream>
#include <iostream>
#include "RawDataHandler.h"

std::vector<char> RawDataHandler::GetFrame(int iFrameSize)
{
    std::vector<char> vcRetVector;
    char ch;
    int cnt = 0;
    while (m_pFileOpener->GetInputFileStream() >> std::noskipws >> ch && iFrameSize != cnt)
    {
        vcRetVector.push_back(ch);
        cnt++;
    }
    return vcRetVector;
}

void RawDataHandler::GetFrame(int iFrameSize, char* cBuffer)
{
    char ch;
    int cnt = 0;
    while (m_pFileOpener->GetInputFileStream() >> std::noskipws >> ch && iFrameSize != cnt)
    {
        cBuffer[cnt] = ch;
        cnt++;
    }
}