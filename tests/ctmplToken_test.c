//
// Created by aidankeefe on 4/13/26.
//
#include <LibAidan/AidanTesting.h>
#include "../src/ctmplToken.c"


int main() {
    Tests_set ts = ts_init();
    run_tests(&ts);
    return 0;
}