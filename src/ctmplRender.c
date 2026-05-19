//
// Created by aidankeefe on 5/19/26.
//
#include "../include/ctmplRender.h"

static bool isEndOfCodeSection(struct aid_string* string, u64 currentIndex) {
    if (currentIndex >= string->length)
        return false;
    if (string->s[currentIndex] == '%'  && string->s[currentIndex-1] == '}')
        return true;
    return false;
}

static bool isStartOfCodeSection(struct aid_string* string, u64 currentIndex) {
    if (currentIndex >= string->length-1)
        return false;
    if (string->s[currentIndex] == '%'  && string->s[currentIndex+1] == '{')
        return true;
    return false;
}

struct aid_string ctmpl_render(FILE* f, struct ctmpl_params params) {
    auto arena = aid_create_arena(MiB(1));
    struct aid_string retString = {.options = AID_STR_AUTO_RESIZE};
    fseek(f, 0, SEEK_END);
    u64 len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* fileBuf = (char*)malloc(len);
    fread(fileBuf, len, 1, f);
    struct aid_string fileString = {len,len, 0, fileBuf};
    auto codeSections = extractTemplCodeSegments(arena, &fileString);

    u64 index = 0;
    u64 codeSegmentIndex = 0;

    while (index < len) {
        if (isStartOfCodeSection(&fileString, index)) {
            auto codeSection =  codeSections.data[codeSegmentIndex++];
            auto tokens = tokenizeCodeSegment(arena,*codeSection);
            auto val = ctmplEvaluateCodeSection(params, tokens);
            aid_str_append_string(&retString, &val);
            free(val.s);
            while (!isEndOfCodeSection(&fileString, index)) {
                if (index > len)
                    goto Error;
                index++;
            }
        }else {
            aid_str_append_char(&retString, fileString.s[index]);
        }
        index++;
    }

    Error:
    aid_arena_free(arena);
    return (struct aid_string){0};

}
