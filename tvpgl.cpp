// Copied tvpgl functions, because we can't rely on the core to have them.

#include "tvpgl.h"

TVP_GL_FUNC_DECL(void, TVPDoGrayScale_c, (tjs_uint32 *dest, tjs_int len))
{
	tjs_uint32 s1, d1;
	{
		for(int ___index = 0; ___index < len; ___index++)
		{
			s1 = dest[___index];;
			d1 = (s1&0xffu)*19u;;
			d1 += ((s1 >> 8u)&0xffu)*183u;;
			d1 += ((s1 >> 16u)&0xffu)*54u;;
			d1 = (d1 >> 8u) * 0x10101u + (s1 & 0xff000000u);;
			dest[___index] = d1;;
		}
	}
}
