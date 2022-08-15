#ifndef LB30113FILE
#define LB30113FILE 0

#ifdef LB30113_CPP
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <sys/stat.h>
#include <cunistd>
namespace lb {
    using namespace std;
extern "C" {
   #else
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h> 
#ifdef LB30113_LIB
extern "C" {
#endif
#endif


int lb_fputs(FILE* target, const void* value, uint32_t size);

char** lb_pathAndFileSeperator(const char* pathNname);
char** lb_pathSeperator(const char* pathNname);


int lb_changeDirectory(const char* path);
FILE* lb_fileOpener(const char* path, const char* name, const char* prot);
int lb_makeDirectory(const char* path, const char* name, int prot = 0777);


#ifdef LB30113_CPP
} }
#else
#ifdef LB30113_LIB
}
#endif
#endif
#endif // LB30113FILE
