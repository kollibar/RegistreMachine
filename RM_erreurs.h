#ifndef __RM_ERREURS_H__
#define __RM_ERREURS_H__

#include "RM_config_default.h"

/* erreurs liées à la gestions des datas */
#define RM_ERREUR_NB_TABLE_MAX_ATTEINT  ( RM_ERREUR_BASE + 0x01 )

/* erreurs liées à une data en paRMiculier */
#define RM_ERREUR_INDEX_INEXISTANT     ( RM_ERREUR_BASE + 0x02 )
#define RM_ERREUR_SUBINDEX_INEXISTANT  ( RM_ERREUR_BASE + 0x03 )
#define RM_ERREUR_SANS_SUBINDEX        ( RM_ERREUR_BASE + 0x04 )
#define RM_ERREUR_EST_TABLEAU          ( RM_ERREUR_BASE + 0x05 )
#define RM_ERREUR_N_EST_PAS_TABLEAU    ( RM_ERREUR_BASE + 0x06 )
#define RM_ERREUR_TYPE_INCOMPATIBLE    ( RM_ERREUR_BASE + 0x07 )
#define RM_ERREUR_TAILLE_INCOMPATIBLE  ( RM_ERREUR_BASE + 0x08 )


#endif
