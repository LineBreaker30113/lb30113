#define LB30113_LIB
#include "lb30113\img\imageV0.h"

#ifdef LB30113_CPP
using namespace lb; using namespace img;
#endif // LB30113_CPP
extern "C" {

/* data order:
    handled previusly: endingness handler, verison number
    handled here: {
        flags, atribute lenght, data length, width, height, atributes, data
    }
*/

lb_rawImageT* lb_imageReaderV0(FILE* resource, lb_rawImageT res, unsigned char endimismatch)
{
    res->p.v=fgetc(resource);

    *((char*)&res->ml)=fgetc(resource);
    *(((char*)&res->ml)+1)=fgetc(resource);

    *((char*)&res->il)=fgetc(resource);
    *(((char*)&res->il)+1)=fgetc(resource);
    *(((char*)&res->il)+2)=fgetc(resource);
    *(((char*)&res->il)+3)=fgetc(resource);
    *(((char*)&res->il)+4)=fgetc(resource);
    *(((char*)&res->il)+5)=fgetc(resource);
    *(((char*)&res->il)+6)=fgetc(resource);
    *(((char*)&res->il)+7)=fgetc(resource);

    *((char*)&res->w)=fgetc(resource);
    *(((char*)&res->w)+1)=fgetc(resource);
    *(((char*)&res->w)+2)=fgetc(resource);
    *(((char*)&res->w)+3)=fgetc(resource);

    *((char*)&res->h)=fgetc(resource);
    *(((char*)&res->h)+1)=fgetc(resource);
    *(((char*)&res->h)+2)=fgetc(resource);
    *(((char*)&res->h)+3)=fgetc(resource);

    if(endimismatch) {
        lb_byteFlipper(((char*)&res->w), 4); lb_byteFlipper(((char*)&res->h), 4);
        lb_byteFlipper(((char*)&res->il), 8); lb_byteFlipper(((char*)&res->ml), 2);
    }

    res->memory = (void*)malloc(res->ml);
    for(uint16_t i=0;i!=res->ml;i++) { res->memory[i] = fgetc(resource); }

    res->image = (void*)malloc(res->il);
    for(int64_t i=0;i!=res->il;i++) { res->image[i] = fgetc(resource); }
    
    return res;
}
int32_t lb_imageWriterV0(FILE* target, lb_rawImageT* data)
{
    fputc((unsigned char)0x00, target);// verison

    fputc(data->p.v, target);// flags

    fputc((unsigned char)0x00, target);// atributes is not supported yet
    fputc((unsigned char)0x00, target);// that way atribute length is zero

    fputc(*((char*)&(data->il)), target);
    fputc(*(((char*)&(data->il))+1), target);
    fputc(*(((char*)&(data->il))+2), target);
    fputc(*(((char*)&(data->il))+3), target);
    fputc(*(((char*)&(data->il))+4), target);
    fputc(*(((char*)&(data->il))+5), target);
    fputc(*(((char*)&(data->il))+6), target);
    fputc(*(((char*)&(data->il))+7), target);

    fputc(*((char*)&(data->w)), target);
    fputc(*(((char*)&(data->w))+1), target);
    fputc(*(((char*)&(data->w))+2), target);
    fputc(*(((char*)&(data->w))+3), target);

    fputc(*((char*)&(data->h)), target);
    fputc(*(((char*)&(data->h))+1), target);
    fputc(*(((char*)&(data->h))+2), target);
    fputc(*(((char*)&(data->h))+3), target);

    for(uint64_t i=0;i!=data->il;i++) { fputc(*((char*)&(data->image[i])), target); }

    return 0;
}

lb_imageT* lb_imageExtractorV0(lb_rawImageT* rawimg) {
    lb_imageT* result = malloc(sizeof(lb_imageT));
    result->w = rawimg->w; result->h = rawimg->h;
    result->memory = (lb_argb8uiT**) malloc(result->h*sizeof(void*));
    uint8_t hasAlpha = lb_readF(rawimg->p, 0);
    for(uint32_t yi=0;yi!=result->h;yi++) {
        result->memory[yi] = (lb_argb8uiT*)malloc(res->w * sizeof(lb_argb8uiT));
        if(hasAlpha) {
            for(uint32_t xi=0;xi!=result->w;xi++) {
		        result->memory[yi][xi].c.r =rawimg->image[yi*rawimg->w +xi*4 +0];
		        result->memory[yi][xi].c.g =rawimg->image[yi*rawimg->w +xi*4 +1];
		        result->memory[yi][xi].c.b =rawimg->image[yi*rawimg->w +xi*4 +2];
                result->memory[yi][xi].a   =rawimg->image[yi*rawimg->w +xi*4 +3];
            }
        } else { for(uint32_t xi=0;xi!=result->w;xi++) {
		        result->memory[yi][xi].c.r =rawimg->image[yi*rawimg->w +xi*3 +0];
		        result->memory[yi][xi].c.g =rawimg->image[yi*rawimg->w +xi*3 +1];
		        result->memory[yi][xi].c.b =rawimg->image[yi*rawimg->w +xi*3 +2];
                result->memory[yi][xi].a   = 255ui8;
            }
        }
    }
    return result;
}
lb_rawImageT* lb_imageParserV0(lb_imageT* origin, lb_flags8T requests) {
    lb_rawImageT* result = malloc(sizeof(lb_rawImageT));
    result->w = origin->w; result->h = origin->h;
    result->memory = (lb_argb8uiT**) malloc(result->h*sizeof(void*));
    uint8_t hasAlpha = 0;
    if(lb_readF(requests, 0)) {
        for(uint32_t yi=0;yi!=result->h;yi++) { for(uint32_t xi=0;xi!=result->w;xi++) {
            if(origin->memory[yi][xi].a!=255) { hasAlpha = 1; lb_writeF(&result->p, 0, 1); break}
        } if(hasAlpha) { break; } }
    }
    for(uint32_t yi=0;yi!=result->h;yi++) {
        result->memory[yi] = (lb_argb8uiT*)malloc(res->w * sizeof(lb_argb8uiT));
        if(hasAlpha) {
            for(uint32_t xi=0;xi!=origin->w;xi++) {
		        result->image[yi*result->w +xi*4 +0] =origin->memory[yi][xi].c.r;
		        result->image[yi*result->w +xi*4 +1] =origin->memory[yi][xi].c.g;
		        result->image[yi*result->w +xi*4 +2] =origin->memory[yi][xi].c.b;
                result->image[yi*result->w +xi*4 +3] =  origin->memory[yi][xi].a;
            }
        } else { for(uint32_t xi=0;xi!=origin->w;xi++) {
		        result->image[yi*result->w +xi*3 +0] =origin->memory[yi][xi].c.r;
		        result->image[yi*result->w +xi*3 +1] =origin->memory[yi][xi].c.g;
		        result->image[yi*result->w +xi*3 +2] =origin->memory[yi][xi].c.b;
            }
        }
    }
}

	    /*res->memory[i] = malloc(res->w * sizeof(3+lb_readF(res->p, 0)));
	    if(!lb_readF(res->p, 0)) { lb_rgb8uiT* current = (lb_rgb8uiT*)res->memory[i];
	    for(uint32_t xi=0;xi!=res->w;xi++) {
		    current[xi].r =fgetc(resource);
		    current[xi].g =fgetc(resource);
		    current[xi].b =fgetc(resource);
		} } else { lb_argb8uiT* current = (lb_argb8uiT*)res->memory[i];
        for(uint32_t xi=0;xi!=res->w;xi++) {
		    current[xi].c.r =fgetc(resource);
		    current[xi].c.g =fgetc(resource);
		    current[xi].c.b =fgetc(resource);
		    current[xi].a =fgetc(resource);
		} }*/

#ifndef LB30113_CPP
}
#endif // LB30113_CPP
