//
// Created by aidankeefe on 5/18/26.
//
#include "../include/ctmplParameters.h"

#include <LibAidan/AidanLinkedList.h>
#include <LibAidan/AidanAidAllocator.h>

struct ctmpl_param {
    struct aid_string key;
    struct aid_string text_value;
};

struct ctmpl_params {
    struct aid_AidAllocator allocator;
    struct aid_LinkedList params;
};


bool ctmpl_addParam(ctmpl_params *params, struct aid_string key,struct aid_string value) {
    ctmpl_param* param = aid_AidAlloc(&params->allocator, sizeof(*param));
    if (!param )
        return false;
    *param = (ctmpl_param){key, value};
    aid_push(&params->params, param, VOIDPTR);
    return true;
}

struct aid_string ctmpl_findParam(ctmpl_params *params, struct aid_string key) {
    for (struct aid_LLNode* node = params->params.head; node != nullptr; node = node->next) {
        ctmpl_param *param = (ctmpl_param*)(node->VOIDPTR);
        if (aid_str_cmp(&param->key, &key)) {
            return param->text_value;
        }
    }
    return (struct aid_string){0};
}


bool ctmpl_freeParams(ctmpl_params *params) {
    aid_AidReleaseAll(&params->allocator);
    if (!aid_free_LL(&params->params))
        return false;
    if (params->allocator.mem.len != 0)
        return false;
    if (params->allocator.freeList.size != 0)
        return false;
    return true;
}
