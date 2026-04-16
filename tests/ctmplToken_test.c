//
// Created by aidankeefe on 4/13/26.
//
#define AIDAN_SHORT_NAMES
#include <LibAidan/AidanTesting.h>
#include <ctmplToken.h>
#include "../src/ctmplToken.c"

int testExtractCtmplCodeSections(test_arg) {
    Arena* a = arena_create(MiB(1));
    t_assert(a)
    String s = STR_LIT("not code %{code}% not code %{more code asdfasfasfasfasf}%");
    DArray_string codeSections = extractTemplCodeSegments(a,&s);
    t_assert(codeSections.len == 2);
    t_assert(codeSections.data[0]->length == 8)
    t_assert(codeSections.data[0]->cap == 8)
    t_assert(codeSections.data[1]->length == 30)
    t_assert(codeSections.data[1]->cap == 30)
    arena_free(a);
    free(codeSections.data);
    test_end
}

int testTokenizeCodeSegmentsEasy(test_arg) {
    Arena* a = arena_create(MiB(1));
    t_assert_exit(a)
    String codeSegment = STR_LIT("%{code code2}%");
    Array_CtmplToken tokens = tokenizeCodeSegment(a, codeSegment);
    t_assert(tokens.len == 2);
    t_assert(tokens.data[0].text.length == 4);
    free(tokens.data);
    arena_free(a);
    test_end
}

int testTokenizeCodeSegmentsHard(test_arg) {
    Arena* a = arena_create(MiB(1));
    t_assert_exit(a)
    String codeSegment = STR_LIT("%{  code \r\t\t code2  \t }%");
    Array_CtmplToken tokens = tokenizeCodeSegment(a, codeSegment);
    t_assert(tokens.len == 2);
    t_assert(tokens.data[0].text.length == 4);
    free(tokens.data);
    arena_free(a);
    test_end
}


int main() {
    Tests_set ts = ts_init();
    reg_test(ts, testExtractCtmplCodeSections);
    reg_test(ts, testTokenizeCodeSegmentsEasy);
    reg_test(ts, testTokenizeCodeSegmentsHard);
    return run_tests(&ts);
}