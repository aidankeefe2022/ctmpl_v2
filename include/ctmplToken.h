//
// Created by aidankeefe on 4/10/26.
//

#ifndef CTMPL_V2_CTMPLTOKEN_H
#define CTMPL_V2_CTMPLTOKEN_H
#include <LibAidan/AidanCommon.h>
#include <LibAidan/AidanString.h>
#include <LibAidan/AidanAidAllocator.h>
#include <LibAidan/AidanArena.h>
#include <LibAidan/AidanDynaArray.h>
#include <stdio.h>
#include <sys/stat.h>

//feature flags
#define CTMPL_VARIABLE 1

typedef struct CtmplToken{
	u64 features;
	struct aid_string text;
}CtmplToken;

ArrayCreate(CtmplToken, CtmplToken);

struct aid_DArray_string extractTemplCodeSegments(struct aid_arena* a, struct aid_string* string);
Array_CtmplToken tokenizeCodeSegment(struct aid_arena* a, struct aid_string string);

#endif //CTMPL_V2_CTMPLTOKEN_H
