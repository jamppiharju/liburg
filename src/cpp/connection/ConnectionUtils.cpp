/*!
  \file
  \brief Connection を用いた補助関数

  \author Satofumi KAMIMURA

  $Id: ConnectionUtils.cpp 1838 2010-06-01 03:17:17Z satofumi $
*/

#include "ConnectionUtils.h"
#include "Connection.h"

using namespace qrk;


bool qrk::isLF(const char ch)
{
    return ((ch == '\r') || (ch == '\n')) ? true : false;
}


void qrk::skip(Connection* con, int total_timeout, int each_timeout)
{
    if (each_timeout <= 0) {
        each_timeout = total_timeout;
    }

    // !!! total_timeout を使う実装に修正する
    char recv_ch;
    while (1) {
        int n = con->receive(&recv_ch, 1, each_timeout);
        if (n <= 0) {
            break;
        }
    }
}


int qrk::readline(Connection* con, char* buf, const size_t count, int timeout)
{
    // １文字ずつ読み出して評価する
    bool is_timeout = false;
    size_t filled = 0;

    while (filled < count) {
        char recv_ch;
        int n = con->receive(&recv_ch, 1, timeout);
        if (n <= 0) {
            is_timeout = true;
            break;
        } else if (isLF(recv_ch)) {
            break;
        }
        buf[filled++] = recv_ch;
    }
    if (filled == count) {
        --filled;
        con->ungetc(buf[filled]);
    }
    buf[filled] = '\0';

    if ((filled == 0) && is_timeout) {
        return -1;
    } else {
        return static_cast<int>(filled);
    }
}
