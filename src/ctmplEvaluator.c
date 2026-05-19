//
// Created by aidankeefe on 4/30/26.
//

#include "../include/ctmplEvaluator.h"
//Allocated a string in the string
struct aid_string ctmplEvaluateCodeSection(ctmpl_params params, Array_CtmplToken arr) {
    struct aid_string str = {.options = AID_STR_AUTO_RESIZE};
    for (i32 i = 0; i < arr.len; i++) {
        if (arr.data[i].features & CTMPL_VARIABLE) {
            struct aid_string paramVal = ctmpl_findParam(params, arr.data[i].text);
             aid_str_append_string(&str, &paramVal);
        }
    }
    return str;
}
