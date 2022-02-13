#include "RM_EEPROM.h"


EEPROMaddrReg RM_EEPROM_TableauRegistre::actualiseStockage(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr){
  addr=this->chercheAddr(regDescGetIndex(regDesc), regDescGetSubIndex(regDesc), addr);

  if(addr > TAILLE_EEPROM ) return addr;

  this->setParamAtAddr(addr, regDescGetParam(regDesc));
  this->setTypeAtAddr(addr, regDescGetType(regDesc));
  this->setSizeEEPROMAtAddr(addr, regDescGetSizeEEPROM(regDesc));

  return addr;
}
uint8_t RM_EEPROM_TableauRegistre::checkEEPROM(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr) const{
  addr=this->chercheAddr(regDescGetIndex(regDesc), regDescGetSubIndex(regDesc), addr);

  if( addr == 0xFFFF ) { // pas trouvé !
    return ERREUR_NON_TROUVE;
  }

  uint8_t erreur;

  RM_size_t sizeEEPROM = this->getSizeEEPROMDataAtAddr(addr);
  RM_size_t sizePGM = regDescGetSizeEEPROM(regDesc);

  if( sizeEEPROM != sizePGM ) erreur |= ERREUR_TAILLE;
  if( this->getParamAtAddr(addr) != regDescGetParam(regDesc) ) erreur |= ERREUR_PARAM;
  RM_type_t typeEEPROM = this->getTypeAtAddr(addr);
  RM_type_t typePGM = regDescGetType(regDesc);
  if( typeEEPROM != typePGM ) erreur |= ERREUR_TYPE_DIFFERENT;

  return erreur;
}

EEPROMaddrReg RM_EEPROM_TableauRegistre::chercheAddr(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr, bool pourInsertion) const{
  return this->chercheAddr(regDescGetIndex(regDesc), regDescGetSubIndex(regDesc), addr, pourInsertion);
}

EEPROMaddrReg RM_EEPROM_TableauRegistre::chercheAddr(index_t index, subindex_t subindex, EEPROMaddrReg addr, bool pourInsertion) const{
  // recherche d'un index équivalent

  // si à l'adresse de départ on est déjà au delà, alors on recherche depuis le début
  if( ( this->getIndexAtAddr(addr) > index || ( this->getIndexAtAddr(addr) == index && this->getSubindexAtAddr(addr) > subindex ) ) && addr != 0 ) addr=0;

  while( addr < this->getTailleAct() && this->getIndexAtAddr(addr) < index ){
    addr=this->next(addr);
  }

  if( addr >= this->getTailleAct() ) return 0xFFF4;

  if( this->getIndexAtAddr(addr) > index ){ // dépassé
    if( pourInsertion ) return addr;
    else return 0xFFFF;
  }

  while( addr < this->getTailleAct() && this->getIndexAtAddr(addr) == index && this->getSubindexAtAddr(addr) < subindex ){
    addr=this->next(addr);
  }

  if( addr >= this->getTailleAct() ) return 0xFFF4;

  if( ! pourInsertion && (this->getIndexAtAddr(addr) > index || this->getSubindexAtAddr(addr) > subindex) ){ // dépassé...
    return 0xFFFF;
  }

  // trouvé (ou addr pour insertion, càd addresse du suivant !)
  return addr;
}

bool RM_EEPROM_TableauRegistre::isEnd(EEPROMaddrReg addr) const{
  return ( addr >= this->getTaille() || ( this->getIndexAtAddr(addr) == 0xFFFF && this->getSubindexAtAddr(addr) == 0xFF ) );
}

EEPROMaddrReg RM_EEPROM_TableauRegistre::next(EEPROMaddrReg addr) const{
  return this->getSizeEEPROMDataAtAddr(addr) + RM_EEPROM_POS_DATA;
}


index_t RM_EEPROM_TableauRegistre::getIndexAtAddr(EEPROMaddrReg addr) const{
  return this->lit<index_t>(addr+RM_EEPROM_POS_INDEX);
}
subindex_t RM_EEPROM_TableauRegistre::getSubindexAtAddr(EEPROMaddrReg addr) const{
  return this->lit<subindex_t>(addr+RM_EEPROM_POS_SUBINDEX);
}
RM_param_t  RM_EEPROM_TableauRegistre::getParamAtAddr(EEPROMaddrReg addr) const{
  return this->lit<RM_param_t>(addr+RM_EEPROM_POS_PARAM);
}

RM_type_t  RM_EEPROM_TableauRegistre::getTypeAtAddr(EEPROMaddrReg addr) const{
  return this->lit<RM_type_t>(addr+RM_EEPROM_POS_TYPE);
}

RM_size_t  RM_EEPROM_TableauRegistre::getSizeEEPROMDataAtAddr(EEPROMaddrReg addr) const{
  return this->lit<RM_size_t>(addr+RM_EEPROM_POS_EEPROM_SIZE);
}


bool RM_EEPROM_TableauRegistre::setIndexAtAddr(EEPROMaddrReg addr, index_t index){
  return this->ecrit(index, addr+RM_EEPROM_POS_INDEX);
}
bool RM_EEPROM_TableauRegistre::setSubindexAtAddr(EEPROMaddrReg addr, subindex_t subindex){
  return this->ecrit(subindex, addr+RM_EEPROM_POS_SUBINDEX);
}
bool RM_EEPROM_TableauRegistre::setParamAtAddr(EEPROMaddrReg addr, RM_param_t param){
  return this->ecrit(param, addr+RM_EEPROM_POS_PARAM);
}
bool RM_EEPROM_TableauRegistre::setTypeAtAddr(EEPROMaddrReg addr, RM_type_t type){
  return this->ecrit(type, addr+RM_EEPROM_POS_TYPE);
}
bool RM_EEPROM_TableauRegistre::setSizeEEPROMAtAddr(EEPROMaddrReg addr, RM_size_t size){
  return this->ecrit(size, addr+RM_EEPROM_POS_EEPROM_SIZE);
}

bool RM_EEPROM_TableauRegistre::setAtAddr(EEPROMaddrReg addr, const RM_RegDesc* regDesc PROGMEM, void* ptrRAM, size_t taille){
  this->setIndexAtAddr(addr, regDescGetIndex(regDesc));
  this->setSubindexAtAddr(addr, regDescGetSubIndex(regDesc));
  this->setParamAtAddr(addr, regDescGetParam(regDesc));
  this->setTypeAtAddr(addr, regDescGetType(regDesc));
  this->setSizeEEPROMAtAddr(addr, regDescGetSizeEEPROM(regDesc));

  if( ptrRAM != NULL ){
    this->setDataFromRAMAtAddr(addr, regDesc, ptrRAM);
  }
  return true;
}
bool RM_EEPROM_TableauRegistre::setDataFromRAMAtAddr(EEPROMaddrReg addr, const RM_RegDesc* regDesc PROGMEM, void* ptrRAM){
  return this->ecrit(ptrRAM, min(regDescGetSizeRam(regDesc), regDescGetSizeEEPROM(regDesc)), addr + RM_EEPROM_POS_DATA);
}
bool RM_EEPROM_TableauRegistre::setDataFromRAMAtAddr(EEPROMaddrReg addr, void* ptrRAM, size_t taille){
  return this->ecrit(ptrRAM, min(taille, this->getSizeEEPROMDataAtAddr(addr)), addr + RM_EEPROM_POS_DATA);
}
bool RM_EEPROM_TableauRegistre::setDataFromPGMAtAddr(EEPROMaddrReg addr, const RM_RegDesc* regDesc PROGMEM){
  uint16_t position=addr + RM_EEPROM_POS_DATA;

  if ( (this->getMode() != modePartition_Ecriture && this->getMode() != modePartition_LectureEcriture) || (this->getMode() == modePartition_Ecriture && position != 0xFFFF)) return 0;

  char* posPGM=(char*)regDescGetFlashDataAddr(regDesc);
  RM_size_t resteAcopier=min(regDescGetSizeEEPROM(regDesc), regDescGetSizeFlash(regDesc));

  if( position+resteAcopier > this->getTaille() ) return false;

  char tampon[TABLE_PARTITION_TAMPON_COPIE];
  while( resteAcopier > 0 ){
    uint8_t tailleCopie=min(resteAcopier, TABLE_PARTITION_TAMPON_COPIE);

    memcpy_P(tampon, posPGM, tailleCopie);
    posPGM += tailleCopie;

    this->ecrit(tampon, tailleCopie, position);

    position += tailleCopie;
  }

  return true;
}

EEPROMaddrReg RM_EEPROM_TableauRegistre::setDefautValue(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr){
  addr=this->chercheAddr(regDesc, addr,false);

  if( addr > TAILLE_EEPROM ) return 0xFFF1;

  this->setDataFromPGMAtAddr(addr, regDesc);

  return addr;
}

EEPROMaddrReg  RM_EEPROM_TableauRegistre::addReg(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr, void* ptrRAM, size_t taille){
  if(! regDescAValeurEEPROM(regDesc)) return 0xFFF1;

  size_t tailleAct=this->getTailleAct();
  if( tailleAct + regDescGetSizeEEPROM(regDesc) + RM_EEPROM_TAILLE_ENTETE > this->getTaille() ) return 0xFFF3;
  this->setTailleAct(tailleAct + regDescGetSizeEEPROM(regDesc) + RM_EEPROM_TAILLE_ENTETE);

  addr = this->chercheAddr(regDescGetIndex(regDesc), regDescGetSubIndex(regDesc), 0, true);

  this->insertAt(addr, regDescGetSizeEEPROM(regDesc) + RM_EEPROM_TAILLE_ENTETE, false);

  this->setAtAddr(addr, regDesc, ptrRAM, taille);

  if( ptrRAM == NULL ) {
    if( regDescAValeurDefaut(regDesc)) this->setDataFromPGMAtAddr(addr, regDesc);
    else this->memset(addr+RM_EEPROM_TAILLE_ENTETE, 0, regDescGetSizeEEPROM(regDesc));
  }
  return addr;
}
void  RM_EEPROM_TableauRegistre::deleteReg(index_t index, subindex_t subindex, EEPROMaddrReg addr){
  addr = this->chercheAddr(index, subindex, addr);
  if( addr > TAILLE_EEPROM ) return;

  size_t taille=this->getSizeEEPROMDataAtAddr(addr)+RM_EEPROM_TAILLE_ENTETE;

  this->setTailleAct(this->getTailleAct()-taille);

  this->deleteAt(addr, taille);
}
void  RM_EEPROM_TableauRegistre::deleteReg(const RM_RegDesc* regDesc, EEPROMaddrReg addr){
  return this->deleteReg(regDescGetIndex(regDesc), regDescGetSubIndex(regDesc), addr);
}

EEPROMaddrReg RM_EEPROM_TableauRegistre::get(index_t index, subindex_t subindex, void* data, size_t size, uint8_t debut, EEPROMaddrReg addr) const{
  addr = this->chercheAddr(index, subindex, addr);
  if( addr > TAILLE_EEPROM ) return 0xFFF0;

  if( this->lit(data, min(size, this->getSizeEEPROMDataAtAddr(addr) - debut), addr + debut) - (addr+debut) <= TAILLE_EEPROM ) return addr;
  else return 0xFFFF;

}
size_t RM_EEPROM_TableauRegistre::set(index_t index, subindex_t subindex, const void* data, size_t size, uint8_t debut, EEPROMaddrReg addr, bool attenteActualisationCRC){
  addr = this->chercheAddr(index, subindex, addr);
  if( addr > TAILLE_EEPROM ) return 0xFFF0;

  size = this->ecrit(data, min( size, this->getSizeEEPROMDataAtAddr(addr) - debut ), addr + debut) - (addr + debut);

  if( size > TAILLE_EEPROM ) return 0xFFFF;

  if( ! attenteActualisationCRC && this->getSizeEEPROMDataAtAddr(addr) <= debut + size ){ // on a ecrit la totalité de l'objet
    this->actualiseCRC(); // => actualisation dela CRC du blocMem
  }

  return addr;
}
