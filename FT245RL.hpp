#include <windows.h>
#include "ftd2xx.h"

class FT245RL{
public:
  enum PORT_NO{
    DB_ = -1,
    DB0 = 0,
    DB1 = 1,
    DB2 = 2,
    DB3 = 3,
    DB4 = 4,
    DB5 = 5,
    DB6 = 6,
    DB7 = 7,
  };

  FT245RL(int deviceNO = 0, UCHAR mask = 0xFF);
  ~FT245RL();
private:
  int deviceNO;
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus;
  UCHAR mode;
  DWORD writtenBytes;
  bool open();
  bool close();
  bool getBitOf(PORT_NO no);
  bool bitOn(PORT_NO no = FT245RL::DB_);
  bool bitOff(PORT_NO no = FT245RL::DB_);
};
