//
// Created by aidankeefe on 5/19/26.
//
#include "../include/ctmplRender.h"


struct aid_string ctmpl_render(FILE* f, struct aid_arena* arena, struct ctmpl_params params) {
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

            free(tokens.data);
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

    free(codeSections.data);
    free(fileBuf);
    return retString;
    Error:
    free(codeSections.data);
    free(fileBuf);
    return (struct aid_string){0};

}
