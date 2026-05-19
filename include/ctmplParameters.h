//
// Created by aidankeefe on 5/18/26.
//

#ifndef CTMPL_V2_CTMPLPARAMETERS_H
#define CTMPL_V2_CTMPLPARAMETERS_H

#include <LibAidan/AidanString.h>

typedef struct ctmpl_param ctmpl_param;

typedef struct ctmpl_params ctmpl_params;

bool ctmpl_addParam(ctmpl_params* params, struct aid_string key,struct aid_string value);
struct aid_string ctmpl_findParam(ctmpl_params params, struct aid_string key);
bool ctmpl_freeParams(ctmpl_params *params);

#endif //CTMPL_V2_CTMPLPARAMETERS_H
