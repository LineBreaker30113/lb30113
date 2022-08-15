#ifndef LB30113DATA
#define LB30113DATA 0

#ifdef LB30113_CPP
#include <bitset>
#include <cinttypes>
#include <cstdlib>
namespace lb {
    using namespace std;
extern "C" {
   #else
#include <inttypes.h>
#include <stdlib.h>
#ifdef LB30113_LIB
extern "C" {
#endif
#endif


typedef struct {
    uint8_t v;/*lower index to higher index:
    on image {
if primary: file not opened, endingness misses, higher version
if secondary: has alpha, has colorKey
    }
    */
#ifdef LB30113_CPP
    std::bitset<8>& s = *((std::bitset<8>*)&v);// std::bitset progresses bits same as lbflags8T
#endif
} lb_flags8T;

uint8_t lb_readF(lb_flags8T r, uint8_t i);
void lb_writeF(lb_flags8T* r, uint8_t i, uint8_t v);

#define LB30113ENDINGNESSVALUE 0x0077ui16

uint8_t lb_endingnessHandler(uint16_t v);
void lb_byteFlipper(char* mem, int32_t lenght);

#ifdef LB30113_CPP
} }
#else
#ifdef LB30113_LIB
}
#endif
#endif
#endif // LB30113DATA
