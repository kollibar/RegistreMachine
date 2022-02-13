#include "RM_TableauRegistre.h"

RM_Registre RM_TableauRegistre::getRegistre(index_t index, subindex_t subindex){
  RM_Registre registre=RM_Registre(this->descrRegistre0);

  // initialisation de `registre` avec le registre de départ, ainsi que ptrRam et ptrEEPROM avec les ptr de départ (issus de this)
  char* ptrRAM = (char*)this->ptrRAM;
  char* ptrEEPROM = (char*)this->ptrEEPROM;

  // parcours des registre jusqu'à un registre de fin ou un index de registre >= `index`
  while( ! registre.isEnd() && registre.getIndex() < index ){
    ptrRAM += registre.getSizeRam();
    ptrEEPROM += registre.getSizeEEPROM();

    registre.next();
  }
  // si on a trouvé un registre de fin ou un index de registre > `index`
  if( registre.isEnd() || registre.getIndex() > index ){
    // renvoi d'un registre null
    registre.setNull();
    return registre;
  }

  // parcours des registre jusqu'à un registre de fin ou un subindex de registre >= `subindex` ou un index de registre > `index`
  while( ! registre.isEnd() && registre.getSubindex() < subindex && registre.getIndex() == index ){
    ptrRAM += registre.getSizeRam();
    ptrEEPROM += registre.getSizeEEPROM();

    registre.next();
  }

  // si on a trouvé un registre de fin ou un index de registre > `index`
  if( registre.isEnd() || registre.getIndex() > index || registre.getSubindex() > subindex ){
    // renvoi d'un registre null
    registre.setNull();
    return registre;
  }

  // si on arrive ici, alors index de registre == `index` ET subindex de registre == `subindex`
  if( this->ptrRAM != NULL && registre.aValeurRam()){
    registre.setPtrRAM(ptrRAM);
  } else {
    registre.setPtrRAM(NULL);
  }

  if( this->ptrEEPROM != NULL && registre.aValeurEEPROM()){
    registre.setPtrEEPROM(ptrEEPROM);
  } else {
    registre.setPtrEEPROM(NULL);
  }

  return registre;
}

size_t RM_TableauRegistre::getSizeRAM(){
  size_t tailleRAM=0;

  // initialisation de `registre` avec le registre de départ
  RM_Registre registre=RM_Registre(this->descrRegistre0);

  while( ! registre.isEnd() ){
    tailleRAM += registre.getSizeRam();
    registre.next();
  }

  return tailleRAM;
}

size_t RM_TableauRegistre::getSizeEEPROM(){
  size_t tailleEEPROM=0;

  // initialisation de `registre` avec le registre de départ
  RM_Registre registre=RM_Registre(this->descrRegistre0);

  while( ! registre.isEnd() ){
    tailleEEPROM += registre.getSizeEEPROM();
    registre.next();
  }

  return tailleEEPROM;
}

size_t RM_TableauRegistre::mallocRAM(){
  size_t tailleRAM = this->getSizeRAM();

  // si déjà allouée, on s'en va !
  if( this->ptrRAM != NULL ) vPortFree(this->ptrRAM);

  void* ptrRAM = pvPortMalloc(tailleRAM);
  if( ptrRAM == NULL ) return 0xFFFF;

  this->setRAM(ptrRAM, tailleRAM);
  return tailleRAM;
}

void RM_TableauRegistre::freeRAM(){
  return vPortFree(this->ptrRAM);
}

void RM_TableauRegistre::setRAM(void* ptr, size_t tailleRAM){
  if( tailleRAM==0xFFFF) tailleRAM=this->getSizeRAM();

  this->ptrRAM = ptr;
  memset(this->ptrRAM, 0, tailleRAM);


}

void RM_TableauRegistre::chargeValeurDemarrage(){

  // initialisation de `registre` avec le registre de départ
  RM_Registre registre=RM_Registre(this->descrRegistre0);

  // initialisation de la ram avec les valeurs des registres !
  while( ! registre.isEnd() ){
    registre.chargeValeurDemarrage();
    registre.next();
  }
}

void RM_TableauRegistre::chargeValeurDefaut(){
  // initialisation de `registre` avec le registre de départ
  RM_Registre registre=RM_Registre(this->descrRegistre0);

  
}
