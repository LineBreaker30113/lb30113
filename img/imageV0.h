#ifndef LB30113_IMAGEV0
#define LB30113_IMAGEV0 0

#include "lb30113\img\image.h"

#ifdef LB30113_CPP
namespace lb {
namespace img {
    using namespace std;
extern "C" {
    #else
#ifdef LB30113_LIB
extern "C" {
#endif
#endif

lb_rawImageT* lb_imageReaderV0(FILE* resource, lb_rawImageT res);
int lb_imageWriterV0(FILE* target, lb_rawImageT* data);

lb_imageT* lb_imageExtractorV0(lb_rawImageT* rawimg);
lb_rawImageT* lb_imageParserV0(lb_imageT* origin, lb_flags8T requests);

#ifdef LB30113_CPP
} } }
#else
#ifdef LB30113_LIB
}
#endif
#endif

#endif // LB30113_IMAGEV0
