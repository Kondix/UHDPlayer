#include <vector>
#include <string>
#include <sstream>

#ifndef UHDPLAYER_IMEMOPTIONSHANDLER_H
#define UHDPLAYER_IMEMOPTIONSHANDLER_H

class ImemOptionsHandler {
private:
    std::vector<const char*> m_vOptions;
public:
    ImemOptionsHandler () {};
    ~ImemOptionsHandler() {};

    void AddOption(const char* sOption) { m_vOptions.push_back(sOption); }
    void AddOption(const std::string sOption) { m_vOptions.push_back(sOption.c_str()); }
    std::string ConvertNumber( const std::string sOption, const int iNumber) { return sOption + std::to_string(iNumber); }
    void ClearOptions() { m_vOptions.clear(); }
    std::vector<const char*>& GetOptions() { return m_vOptions; }
};


#endif //UHDPLAYER_IMEMOPTIONSHANDLER_H
