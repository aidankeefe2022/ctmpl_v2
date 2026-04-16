
#include "../include/ctmplToken.h"

#include <ctype.h>

static u64 fileSize(FILE* file){
	if (!file)
		return 0;

	fseek(file, 0, SEEK_END);
	u64 fileSize = ftell(file);
	fseek(file, 0, SEEK_END);
	return fileSize;
}

static bool isStartOfCodeSection(struct aid_string* string, u64 currentIndex) {
	if (currentIndex >= string->length-1)
		return false;
	if (string->s[currentIndex] == '%'  && string->s[currentIndex+1] == '{')
		return true;
	return false;
}

static bool isEndOfCodeSection(struct aid_string* string, u64 currentIndex) {
	if (currentIndex >= string->length-1)
		return false;
	if (string->s[currentIndex] == '%'  && string->s[currentIndex-1] == '}')
		return true;
	return false;
}

static struct aid_DArray_string extractTemplCodeSegments(struct aid_arena* a, struct aid_string* string) {
	/*%{code}%*/
	u64 currentIndex = 0;
	struct aid_DArray_string templCodeSegments = {0};

	u64 startIndex = 0;
	u64 endIndex= 0;
	bool codeSectionFound = false;
	while (currentIndex < string->length) {
		if (isStartOfCodeSection(string, currentIndex)) {
			codeSectionFound = true;
			startIndex = currentIndex;
		}
		if (isEndOfCodeSection(string, currentIndex) && codeSectionFound) {
			endIndex = currentIndex;
			struct aid_string* newString= aid_str_new(a, 1, "", endIndex-startIndex+1);
			aid_str_substring(string, newString, startIndex , endIndex);
			aid_arr_push(templCodeSegments, newString);
			codeSectionFound = false;
		}
		currentIndex++;
	}

	return templCodeSegments;
}


//TODO fix
Array_CtmplToken tokenizeCodeSegment(struct aid_arena* a, struct aid_string string) {
	Array_CtmplToken tokens = {0};
	for (u64 i = 2; string.s[i] != '}'; i++) {
		/*skip white space*/
		while (isspace(string.s[i]))
			i++;
		u64 lastChar = i;
		/*get text between white space*/
		while (!isspace(string.s[i+1]) && string.s[i+1] != '}')
			i++;
		struct aid_string* newTokenString = aid_str_new(a, 0, "",  i-lastChar+1);
		aid_str_substring(&string, newTokenString, lastChar, i);
		aid_arr_push(tokens, ((CtmplToken){0, *newTokenString}));
	}
	return tokens;
}
