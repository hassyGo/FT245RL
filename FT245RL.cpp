#include "FT245RL.hpp"
#include <iostream>

#define FT_RESULT (this->ftStatus == FT_OK ? true : false)

UCHAR FT245RL::bits[8] =
  {
    0x01,//0b00000001
    0x02,//0b00000010
    0x04,//0b00000100
    0x08,//0b00001000
    0x10,//0b00010000
    0x20,//0b00100000
    0x40,//0b01000000
    0x80 //0b10000000
  };

FT245RL::FT245RL(int deviceNO, UCHAR mask):
  deviceNO(deviceNO)
{
  if (!this->open()){
    std::cout << "ERROR: cannot open the device (FT245RL)" << std::endl;
    exit(1);
  }
  else {
    std::cout << "succeed in opening FT245RL!!" << std::endl;
  }
  this->ftStatus = FT_SetBitMode(this->ftHandle, mask, 1);
  this->ftStatus = FT_SetBaudRate(this->ftHandle, FT_BAUD_9600);
  this->ftStatus = FT_Purge(this->ftHandle, FT_PURGE_RX|FT_PURGE_TX);
  this->mode = 0x00;
  this->ftStatus = FT_Write(this->ftHandle, &this->mode, sizeof(UCHAR), &this->writtenBytes);
}

FT245RL::~FT245RL(){
  this->bitOff();
  if (this->close()){
    std::cout << "succeeded in closing FT245RL!!" << std::endl;
  }
}

bool FT245RL::open(){
  return (FT_OK == FT_Open(this->deviceNO, &this->ftHandle) ? true : false);
}

bool FT245RL::close(){
  return (FT_OK == FT_Close(this->ftHandle) ? true : false);
}

bool FT245RL::getBitOf(PORT_NO no){
  this->ftStatus = FT_GetBitMode(this->ftHandle, &this->mode);
  assert(no != FT245RL::DB_);
  return (this->mode & FT245RL::bits[no] ? true : false);
}

bool FT245RL::bitOn(PORT_NO no){
  if (no != FT245RL::DB_) {
    this->mode = this->mode&FT245RL::bits[no] ? this->mode : this->mode^FT245RL::bits[no];
  }
  else {
    this->mode = 0xFF;
  }
  this->ftStatus = FT_Write(this->ftHandle, &this->mode, sizeof(UCHAR), &this->writtenBytes);
  return FT_RESULT;
}

bool FT245RL::bitOff(PORT_NO no){
  if (no != FT245RL::DB_){
    this->mode = this->mode&FT245RL::bits[no] ? this->mode^FT245RL::bits[no] : this->mode;
  }
  else {
    this->mode = 0x00;
  }
  this->ftStatus = FT_Write(this->ftHandle, &this->mode, sizeof(UCHAR), &this->writtenBytes);
  return FT_RESULT;
}
