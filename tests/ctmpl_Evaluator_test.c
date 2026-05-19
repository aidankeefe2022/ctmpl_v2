//
// Created by aidankeefe on 5/19/26.
//
#define AIDAN_SHORT_NAMES
#include "../include/ctmplEvaluator.h"
#include "../include/ctmplParameters.h"
#include "../include/ctmplToken.h"
#include <LibAidan/AidanTesting.h>
#include "../src/ctmplParameters.c"
#include "../src/ctmplToken.c"
#include "../src/ctmplEvaluator.c"

int testEvaluateCode(test_arg) {
    Arena* a = arena_create(MiB(1));
    t_assert_exit(a);
    String codeSegment = STR_LIT("%{code code2}%");
    Array_CtmplToken tokens = tokenizeCodeSegment(a, codeSegment);
    ctmpl_params params = {0};
    ctmpl_addParam(&params, STR_LIT("code"), STR_LIT("hello to the world "));
    ctmpl_addParam(&params, STR_LIT("code2"), STR_LIT("I hope there is a lot of good will"));
    String resultString = ctmplEvaluateCodeSection(params, tokens);
    String finalString = STR_LIT("hello to the world I hope there is a lot of good will");
    t_assert(str_cmp(&resultString, &finalString))
    t_assert(resultString.length == finalString.length)
    arena_free(a);
    free(tokens.data);
    free(resultString.s);
    ctmpl_freeParams(&params);
    test_end
}

int main() {
    Tests_set ts = ts_init();
    reg_test(ts, testEvaluateCode);
    return run_tests(&ts);
}
