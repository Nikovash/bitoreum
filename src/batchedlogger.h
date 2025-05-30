// Copyright (c) 2018-2020 The Dash Core developers
// Copyright (c) 2020-2022 The Bitoreum developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef _B_I_T_O_R_E_U_M__BATCHEDLOGGER_H
#define _B_I_T_O_R_E_U_M__BATCHEDLOGGER_H

#include <string>     // For std::string
#include <cstdint>    // For uint64_t
#include "tinyformat.h"

class CBatchedLogger
{
private:
    bool accept;
    std::string header;
    std::string msg;
public:
    CBatchedLogger(uint64_t _category, const std::string& _header);
    virtual ~CBatchedLogger();

    template<typename... Args>
    void Batch(const std::string& fmt, const Args&... args)
    {
        if (!accept) {
            return;
        }
        msg += "    " + strprintf(fmt, args...) + "\n";
    }

    void Flush();
};

#endif//_B_I_T_O_R_E_U_M__BATCHEDLOGGER_H
