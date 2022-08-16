#ifndef LB30113_IMAGE
#define LB30113_IMAGE 0


#include "lb30113\data.h"
#include "lb30113\file.h"
#include "lb30113\img\imageV0.h"

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


uint8_t lb_rgb8uiTchannelSum(uint8_t c, int16_t v) {
    int32_t r=c; r+=v; r= r>255 ? 255:r; r= r<0 ? 0:r; return (uint8_t)r;
}
uint8_t lb_rgb8uiTchannelMult(uint8_t c, uint8_t v) {
    int32_t r=c; r*=v; r/=255; return (uint8_t)r;
}
uint8_t lb_rgb8uiTchannelAmplifie(uint8_t c, int16_t v) {
    int32_t r=c; r*=v; r= r>255 ? 255:r; r= r<0 ? 255-r :r; return (uint8_t)r;
}

lb_rgb8uiT lb_rgb8uiTminus(lb_rgb8uiT o) {
    o.r=255-o.r; o.g=255-o.g; o.b=255-o.b;
return o; }
lb_rgb8uiT lb_rgb8uiTsum(lb_rgb8uiT l, lb_rgb8uiT r) {
    l.r=lb_rgb8uiTchannelSum(l.r, r.r);
    l.g=lb_rgb8uiTchannelSum(l.g, r.g);
    l.b=lb_rgb8uiTchannelSum(l.b, r.b);
return l; }
lb_rgb8uiT lb_rgb8uiTmult(lb_rgb8uiT l, lb_rgb8uiT r) {
    l.r=lb_rgb8uiTchannelMult(l.r, r.r);
    l.g=lb_rgb8uiTchannelMult(l.g, r.g);
    l.b=lb_rgb8uiTchannelMult(l.b, r.b);
return l; }
lb_rgb8uiT lb_rgb8uiTAverage(lb_rgb8uiT l, lb_rgb8uiT r) { lb_rgb8uiT res; short rr,rg,rb;
    rr=(short)l.r+(short)r.r; rr/=2;
    rg=(short)l.g+(short)r.g; rg/=2;
    rb=(short)l.b+(short)r.b; rb/=2;
    res.r=rr; res.g=rg; res.b=rb;
return res; }
lb_rgb8uiT lb_ui32t_to_rgb8uiT(uint32_t value) { lb_rgb8uiT res;
    res.r = value%(2<<24)>>16;
    res.g = value%(2<<16)>>8;
    res.b = value%(2<<8);
return res; }

lb_argb8uiT lb_argb8uiTminus(lb_argb8uiT o) { lb_argb8uiT res;
    res.c.r=255-o.c.r; res.c.g=255-o.c.g; res.c.b=255-o.c.b; res.a=255-o.a;
return res; }
lb_argb8uiT lb_argb8uiTsum(lb_argb8uiT l, lb_argb8uiT r) {
    l.c.r=lb_rgb8uiTchannelSum(l.c.r, r.c.r);
    l.c.g=lb_rgb8uiTchannelSum(l.c.g, r.c.g);
    l.c.b=lb_rgb8uiTchannelSum(l.c.b, r.c.b);
    l.a=lb_rgb8uiTchannelSum(l.a, r.a);
return l; }
lb_argb8uiT lb_argb8uiTMult(lb_argb8uiT l, lb_argb8uiT r) {
    l.c.r=lb_rgb8uiTchannelMult(l.c.r, r.c.r);
    l.c.g=lb_rgb8uiTchannelMult(l.c.g, r.c.g);
    l.c.b=lb_rgb8uiTchannelMult(l.c.b, r.c.b);
    l.a=lb_rgb8uiTchannelMult(l.a, r.a);
return l; }
lb_argb8uiT lb_argb8uiTAverage(lb_argb8uiT l, lb_argb8uiT r) { lb_argb8uiT res; int32_t rr,rg,rb,ra;
    ra=(short)l.a+(short)r.a;
    rr=(int)l.c.r*(int)l.a+(int)r.c.r*(int)r.a; rr/=ra;
    rg=(int)l.c.g*(int)l.a+(int)r.c.g*(int)r.a; rg/=ra;
    rb=(int)l.c.b*(int)l.a+(int)r.c.b*(int)r.a; rb/=ra;
    ra/=2;
    res.c.r=rr; res.c.g=rg; res.c.b=rb; res.a=ra;
return res; }
lb_argb8uiT lb_ui32t_to_argb8uiT(uint32_t value) { lb_argb8uiT res;
    res.a   = value>>24;
    res.c.r = value%(2<<24)>>16;
    res.c.g = value%(2<<16)>>8;
    res.c.b = value%(2<<8);
return res; }

FILE* lb_imageWriteFile(const char* path, const char* name) {
    int len = strlen(name); char* rname = (char*) malloc((len+14)*sizeof(char));
    for(int i=0;i!=len;i++) { rname[i]=name[i]; }
    {
        const char* ext = ".lb30113image"; rname[14+len] = '\0';
        for(int i=0;i!=14;i++) { rname[i+len]=ext[i]; }
    }
    FILE* result = lb_fileOpener(path, rname, "wb");
    free(rname); return result;
}
FILE* lb_imageReadFile(const char* path, const char* name) {
    int len = strlen(name); char* rname = (char*) malloc((len+14)*sizeof(char));
    for(int i=0;i!=len;i++) { rname[i]=name[i]; }
    {
        const char* ext = ".lb30113image"; rname[14+len] = '\0';
        for(int i=0;i!=14;i++) { rname[i+len]=ext[i]; }
    }
    FILE* result = lb_fileOpener(path, rname, "rb");
    free(rname); return result;
}

lb_rawImageT* lb_imageReader(FILE* resource) {
    lb_rawImageT* res = (lb_rawImageT*)malloc(sizeof(lb_rawImageT));
    if (resource == NULL) { lb_writeF(&res->s, 0, 1); return res; }
    uint16_t mem; unsigned char ver;

    *((char*)&mem) = fgetc(resource);
    *(((char*)&mem)+1) = fgetc(resource);
    unsigned char endi = lb_endingnessHandler(mem);
    lb_writeF(&res->s, 1, endi!=0);
    if(endi==-1) { return res; }

    *((char*)&ver)=fgetc(resource); switch (ver) {

    case 0: return lb_imageReaderV0(resource, res, endi);
        break;
    default:
        char vermissmatch = ver>0;
        lb_writeF(&res->s, 2, vermissmatch);
        if(vermissmatch) { return res; }
        break;
    }
}
int lb_imageWriter(FILE* target, lb_rawImageT* data) {
    if (target == NULL) { return -1; }
    
    uint16_t val = LB30113ENDINGNESSVALUE;
    fputc(*((char*)&val), target);
    fputc(*(((char*)&val)+1), target);
    
    return lb_imageWriterV0(target);
}

lb_imageT* lb_imageExtractor(lb_rawImageT* rawimg) {
    return lb_imageExtractorV0(rawimg);
}
lb_rawImageT* lb_imageParser(lb_imageT* origin, lb_flags8T requests) {
    return lb_imageParserV0(origin, requests);
}

void lb_imageCloser(lb_imageT* target) {
    for(uint32_t i=0;i!=target->h;i++) { free(target->memory[i]); } free(target->memory);
    free(target);
}
void lb_rawImageCloser(lb_rawImageT* target) {
    free(target->image); free(target->memory); free(target);
}

#ifdef LB30113_CPP
} } }
#else
#ifdef LB30113_LIB
}
#endif
#endif

#endif // LB30113IMAGE_H_INCLUDED
#define LB30113_LIB