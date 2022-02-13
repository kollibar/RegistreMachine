#ifndef __RM_SCCONNECTEUR_H__
#define __RM_SCCONNECTEUR_H__

#include "RM_config_default.h"
#include "RM_type.h"

#include "RM_Registre.h"
#include "RM_RegDesc.h"


#include <SerialCommandeur.h>


const char RM_SC_GETCMDE[] PROGMEM = "GET";
const char RM_SC_SETCMDE[] PROGMEM = "SET";
const char RM_SC_LISTCMDE[] PROGMEM = "LIST";

const char RM_NOM_MODULE[] PROGMEM="RM";
const char* const RM_LISTE_COMMANDE[] PROGMEM={RM_SC_GETCMDE, RM_SC_SETCMDE, RM_SC_LISTCMDE};

void getFromSC(SerialCommander*);
void setFromSC(SerialCommander*);
void listFromSC(SerialCommander*);


registre_t getRegistreFromStr(const char*);


#endif
