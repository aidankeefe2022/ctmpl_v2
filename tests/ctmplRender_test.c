//
// Created by aidankeefe on 5/19/26.
//
#define AIDAN_SHORT_NAMES
#include <LibAidan/AidanTesting.h>
#include "../src/ctmplParameters.c"
#include "../src/ctmplRender.c"
#include "../src/ctmplToken.c"
#include "../src/ctmplEvaluator.c"


int testRender(test_arg) {
    Arena* a = arena_create(MiB(1));
    struct ctmpl_params params = {0};
    ctmpl_addParam(&params, STR_LIT("name"), STR_LIT("aidan keefe"));
    FILE* f = fopen("../testResources/RenderTest.ctmpl" , "r");
    t_assert_exit(f)
    auto retVal = ctmpl_render(f, a, params);
    String expectedValue = STR_LIT("<title>aidan keefe</title>");
    t_assert(str_cmp(&retVal,&expectedValue));

    free(retVal.s);
    ctmpl_freeParams(&params);
    arena_free(a);
    test_end
}


int main() {
    Tests_set ts = ts_init();
    reg_test(ts, testRender);
    return run_tests(&ts);
}
