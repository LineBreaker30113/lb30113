#define LB30113_LIB
#include "lb30113\data.h"

#ifdef LB30113_CPP
using namespace lb;
#endif // LB30113_CPP
extern "C" {

uint8_t lb_readF(lb_flags8T r, uint8_t i) { return (r.v%(2<<i))>>i; }
void lb_writeF(lb_flags8T* r, uint8_t i, uint8_t v) {
    uint8_t s = (r->v%(2<<i))>>i;
    if(s==(v!=0)) { return; }
    r->v+=((s)*2-1)*(2<<i);
}

uint8_t lb_endingnessHandler(uint16_t v) {// returns 0 when matches
    if(v==LB30113ENDINGNESSVALUE) { return 0; } if(v==LB30113ENDINGNESSVALUE) { return 1; }
    return -1;
}
void lb_byteFlipper(char* mem, int32_t lenght) {
   char* rem = (char*)malloc(lenght);
   for(int32_t i=0;i!=lenght;i++) { rem[i]=mem[lenght-i-1]; }
   for(int32_t i=0;i!=lenght;i++) { mem[i]=rem[i]; }
}

#ifndef LB30113_CPP
}
#endif // LB30113_CPP
