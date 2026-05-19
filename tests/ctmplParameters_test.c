//
// Created by aidankeefe on 5/18/26.
//


#define AIDAN_SHORT_NAMES
#include <LibAidan/AidanTesting.h>
#include <ctmplToken.h>
#include "../src/ctmplToken.c"
#include "../src/ctmplParameters.c"

int testAddParameters(test_arg) {
 ctmpl_params params = {0};
 t_assert(ctmpl_addParam(&params, STR_LIT("key1"), STR_LIT("val1")));
 t_assert(params.params.size == 1);
 t_assert(ctmpl_addParam(&params, STR_LIT("key2"), STR_LIT("val2")));
 t_assert(params.params.size == 2);
 t_assert(ctmpl_addParam(&params, STR_LIT("key3"), STR_LIT("")));
 t_assert(params.params.size == 3);
 ctmpl_freeParams(&params);
 test_end
}

int testFindParamters(test_arg) {

 ctmpl_params params = {0};
 t_assert(ctmpl_addParam(&params, STR_LIT("key1"), STR_LIT("val1")));
 t_assert(params.params.size == 1);
 t_assert(ctmpl_addParam(&params, STR_LIT("key2"), STR_LIT("val2")));
 t_assert(params.params.size == 2);

 String val = ctmpl_findParam(params, STR_LIT("key1"));
 t_assert(str_cmp(&val, &STR_LIT("val1")));

 String val2 = ctmpl_findParam(params, STR_LIT("key2"));
 t_assert(str_cmp(&val2, &STR_LIT("val2")));

 ctmpl_freeParams(&params);
 test_end
}

int testFindMissingParameter(test_arg) {
 ctmpl_params params = {0};
 t_assert(ctmpl_addParam(&params, STR_LIT("key1"), STR_LIT("val1")));
 t_assert(ctmpl_addParam(&params, STR_LIT("key2"), STR_LIT("val2")));

 String missing = ctmpl_findParam(params, STR_LIT("key3"));
 t_assert(missing.s == nullptr);
 t_assert(missing.cap == 0);
 t_assert(missing.length == 0);

 ctmpl_freeParams(&params);
 test_end
}

int testFindParameterUsesFirstMatch(test_arg) {
 ctmpl_params params = {0};
 t_assert(ctmpl_addParam(&params, STR_LIT("dup"), STR_LIT("first")));
 t_assert(ctmpl_addParam(&params, STR_LIT("dup"), STR_LIT("second")));
 t_assert(params.params.size == 2);

 String val = ctmpl_findParam(params, STR_LIT("dup"));
 t_assert(str_cmp(&val, &STR_LIT("first")));

 ctmpl_freeParams(&params);
 test_end
}


int main() {
 Tests_set ts = ts_init();
 reg_test(ts, testAddParameters);
 reg_test(ts, testFindParamters);
 reg_test(ts, testFindMissingParameter);
 reg_test(ts, testFindParameterUsesFirstMatch);
 return run_tests(&ts);
}
