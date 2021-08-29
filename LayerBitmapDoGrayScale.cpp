
#include "tjsCommHead.h"
#include "LayerBitmapIntf.h"
#include "LayerBitmapDoGrayScale.h"

#define RET_VOID
#define BOUND_CHECK(x) \
{ \
	tjs_int i; \
	if(rect.left < 0) rect.left = 0; \
	if(rect.top < 0) rect.top = 0; \
	if(rect.right > (i=destbmp->GetWidth())) rect.right = i; \
	if(rect.bottom > (i=destbmp->GetHeight())) rect.bottom = i; \
	if(rect.right - rect.left <= 0 || rect.bottom - rect.top <= 0) \
		return x; \
}

void DoGrayScale(tTVPBaseBitmap *destbmp, tTVPRect rect)
{
#if 0
	if(!Is32BPP()) return;  // 8bpp is always grayscaled bitmap
#endif

	BOUND_CHECK(RET_VOID);

	tjs_int h = rect.bottom - rect.top;
	tjs_int w = rect.right - rect.left;

	tjs_int pitch = destbmp->GetPitchBytes();
	tjs_uint8 * line = (tjs_uint8*)destbmp->GetScanLineForWrite(rect.top);


	line += rect.left * sizeof(tjs_uint32);
	while(h--)
	{
		TVPDoGrayScale((tjs_uint32*)line, w);
		line += pitch;
	}
}
