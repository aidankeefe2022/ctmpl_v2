
#include "../include/ctmplToken.h"
	
static u64 fileSize(FILE* file){
	if (!file)
		return 0;

	fseek(file, 0, SEEK_END);
	u64 fileSize = ftell(file);
	fseek(file, 0, SEEK_END);
	return fileSize;
}

static CtmplToken* processToken(struct aid_String* string){

}

CtmplToken* ctmpl_tokenizeFile(FILE* file){
	u64 fileSizeBytes = fileSize(file);
	struct aid_arena* a = aid_create_arena(fileSizeBytes + MiB(1));
	if (!a)
		goto Error;

	struct aid_string* fileString = aid_str_new(a, 1, "", fileSizeBytes);
	if (!fileString)
		goto Error;
	
	
	
	

Error:
	aid_arena_free(a);
	return nullptr;
}
