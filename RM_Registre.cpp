#include "RM_Registre.h"


RM_Registre::RM_Registre(){
  this->setNull();
}
RM_Registre::RM_Registre(RM_RegDesc * regDesc PROGMEM){
  // A FAIRE
}

void RM_Registre::setNull(){
  this->ptrEEPROM=NULL;
  this->ptrRAM=NULL;
  this->descr=NULL;
}

bool RM_Registre::setPtrRAM(void* data){
  this->ptrRAM=data;
  return true;
}
bool RM_Registre::setPtrEEPROM(void* data){
  this->ptrEEPROM=data;
  return true;
}

index_t RM_Registre::getIndex() const{
  if( this->descr==NULL) return 0;
  return regDescGetIndex(this->descr);
}
subindex_t RM_Registre::getSubindex() const{
  if( this->descr==NULL) return 0;
  return regDescGetSubIndex(this->descr);
}
RM_type_t RM_Registre::getType() const{
  if( this->descr==NULL) return 0;
  return regDescGetType(this->descr);
}
RM_param_t RM_Registre::getParam() const{
  if( this->descr==NULL) return 0;
  return regDescGetParam(this->descr);
}
const void* PROGMEM RM_Registre::getAddrFlashData() const{
  if( this->descr==NULL) return NULL;
  return regDescGetFlashDataAddr(this->descr);
}

template<typename T>
T RM_Registre::getDefaultValue() const{
  T data;
  if( this->getDefaultValue(&data) == sizeof(data)) return data;
  else return 0;
}
template<typename T>
size_t RM_Registre::getDefaultValue(T* data) const{
  return regDescGetObjValue(this->descr, data, sizeof(*data));
}

template<typename T>
bool RM_Registre::isTypeOf(T data) const{
  return( this->getType() == RM_typeOf(data) );
}

bool RM_Registre::isObj() const{
  return regDescIsObj(this->descr);
}
uint8_t RM_Registre::isNull() const{
  return regDescIsNull(this->descr);
}
uint8_t RM_Registre::isNumeric() const{
  return regDescIsNumeric(this->descr);
}
uint8_t RM_Registre::isNumericNotFloat() const{
  return regDescIsNumericNotFloat(this->descr);
}
uint8_t RM_Registre::isFloat() const{
  return regDescIsFloat(this->descr);
}
uint8_t RM_Registre::isNumericSignedNotFloat() const{
  return regDescIsNumericSignedNotFloat(this->descr);
}
uint8_t RM_Registre::isNumericUnsignedNotFloat() const{
  return regDescIsNumericUnsignedNotFloat(this->descr);
}


RM_size_t RM_Registre::getSizeRam() const{return regDescGetSizeRam(this->descr);};
RM_size_t RM_Registre::getSizeFlash() const{return regDescGetSizeFlash(this->descr);};
RM_size_t RM_Registre::getSizeEEPROM() const{return regDescGetSizeEEPROM(this->descr);};


bool RM_Registre::next(){
  if( this->isEnd()) return false;
  this->descr += 1;
  return true;
}

RM_Registre_ERROR RM_Registre::effaceDataRAM(){
  if( this->aValeurRam() && this->ptrRAM != NULL ){
    memset(this->ptrRAM, 0, this->getSizeRam());
    return ERROR_OK;
  }
  return ERROR_ACTION_NON_SUPPORTE;
}


RM_Registre_ERROR RM_Registre::chargeValeurDefaut(){
  if( ( this->getParam() & ( RM_DATA_EEPROM | RM_DATA_RAM | RM_DATA_FCT ) ) != 0 ){
    if( this->aValeurDefaut() ) {  // a valeur flash
      this->chargeValeurFlash();
    } else  { // n'as pas de valeur flash
      if( this->getParam() & RM_DATA_RAM ) this->effaceDataRAM();
      if( this->getParam() & RM_DATA_EEPROM ) this->effaceDataEEPROM();
      if( this->getParam() & RM_DATA_FCT ) this->effaceDataFct();
    }
  }
  return ERROR_OK;
}

RM_Registre_ERROR RM_Registre::chargeValeurDemarrage(){
  if( ( this->getParam() & ( RM_DATA_RAM | RM_DATA_FCT ) ) != 0 ){
    if( this->aValeurEEPROM() ) {  // a valeur flash
      this->chargeValeurEEPROM();
    } else  { // n'as pas de valeur EEPROM
      if( this->getParam() & RM_DATA_RAM ) this->effaceDataRAM();
      if( this->getParam() & RM_DATA_FCT ) this->effaceDataFct();
    }
  }
  return ERROR_OK;
}
