#ifndef __RM_CONFIG_H__
#define __RM_CONFIG_H__

/***********************************
*  paramètre à activer/désactiver  *
***********************************/

// active les flottant sur sur 8 octets /!\ au suppoRM de ceux ci par la caRMe
// #define RM_ENABLE_REAL64



/**************************************************************************************
*                                paramètre à modifier                                 *
* (si commenté prendront leurs valeurs par défaut définie dans RM_config_default.h !) *
**************************************************************************************/

// Erreur de base pour définir 16 erreurs de `RM_ERREUR_BASE` à `RM_ERREUR_BASE + 0x0F`
#define RM_ERREUR_BASE  0x00


#endif
