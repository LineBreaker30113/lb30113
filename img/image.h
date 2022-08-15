#ifndef LB30113_IMAGE
#define LB30113_IMAGE 0

#ifdef LB30113_CPP
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <bitset>
#include <cinttypes>
namespace lb {
namespace img {
    using namespace std;
extern "C" {
   #else
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#ifdef LB30113_LIB
extern "C" {
#endif
#endif

#include "lb30113\data.h"
#include "lb30113\file.h"


uint8_t lb_rgb8uiTchannelSum(uint8_t c, int16_t v);
uint8_t lb_rgb8uiTchannelMult(uint8_t c, uint8_t v);
uint8_t lb_rgb8uiTchannelAmplifie(uint8_t c, int16_t v);

typedef struct { uint8_t r, g, b; } lb_rgb8uiT;
lb_rgb8uiT lb_rgb8uiTminus(lb_rgb8uiT o);
lb_rgb8uiT lb_rgb8uiTsum(lb_rgb8uiT l, lb_rgb8uiT r);
lb_rgb8uiT lb_rgb8uiTmult(lb_rgb8uiT l, lb_rgb8uiT r);
lb_rgb8uiT lb_rgb8uiTaverage(lb_rgb8uiT l, lb_rgb8uiT r);
lb_rgb8uiT lb_ui32t_to_rgb8uiT(uint32_t value);

typedef struct { uint8_t a; lb_rgb8uiT c; } lb_argb8uiT;
lb_argb8uiT lb_argb8uiTminus(lb_argb8uiT o);
lb_argb8uiT lb_argb8uiTsum(lb_argb8uiT l, lb_argb8uiT r);
lb_argb8uiT lb_argb8uiTmult(lb_argb8uiT l, lb_argb8uiT r);
lb_argb8uiT lb_argb8uiTaverage(lb_argb8uiT l, lb_argb8uiT r);
lb_argb8uiT lb_ui32t_to_argb8uiT(uint32_t value);

typedef struct { uint32_t w,h; lb_argb8uiT** memory; } lb_imageT;
typedef struct {
    lb_flags8T primary, secondary; uint32_t w,h;
    void* image; void* memory; uint64_t il; uint16_t ml;
} lb_rawImageT;

FILE* lb_imageWriteFile(const char* path, const char* name);
FILE* lb_imageReadFile(const char* path, const char* name);

lb_rawImageT* lb_imageReader(FILE* resource);// must be "wb"
int lb_imageWriter(FILE* target, lb_rawImageT* data);// must be "rb"

lb_imageT* lb_imageExtractor(lb_rawImageT* rawimg);
lb_rawImageT* lb_imageParser(lb_imageT* origin, lb_flags8T requests);

#ifdef LB30113_CPP
} } }
#else
#ifdef LB30113_LIB
}
#endif
#endif

#endif // LB30113IMAGE_H_INCLUDED
