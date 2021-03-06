/*!
  \file
  \brief USB 接続されているポートの探索

  \author Satofumi KAMIMURA

  $Id: UrgUsbCom.cpp 1407 2009-10-13 14:04:05Z satofumi $
*/

#include "UrgUsbCom.h"
#include "DetectOS.h"
#include "isUsingComDriver.h"

using namespace qrk;
using namespace std;


UrgUsbCom::UrgUsbCom(void)
{
}


vector<string> UrgUsbCom::baseNames(void)
{
  vector<string> ports;
#if defined(LINUX_OS)
  // Linux の場合
  ports.push_back("/dev/ttyACM");

#elif defined(MAC_OS)
  // MacOS の場合
  ports.push_back("/dev/tty.usbmodem");
#endif
  return ports;
}


bool UrgUsbCom::isUsbCom(const char* com_port)
{
  // "URG Series USB Device Driver (COMx)" や
  // "URG-X002 USB Device Driver (COMx)" が Value に含まれているか検索
  if (isUsingComDriver(com_port, "URG Series USB Device Driver") ||
      isUsingComDriver(com_port, "URG-X002 USB Device Driver")) {
    return true;

  } else {
    return false;
  }
}
