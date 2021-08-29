/////////////////////////////////////////////
//                                         //
//    Copyright (C) 2021-2021 Julian Uy    //
//  https://sites.google.com/site/awertyb  //
//                                         //
//   See details of license at "LICENSE"   //
//                                         //
/////////////////////////////////////////////

#include "ncbind/ncbind.hpp"
#include "LayerBitmapIntf.h"
#include "LayerBitmapUtility.h"
#include "LayerBitmapDoGrayScale.h"
#include <string.h>
#include <stdio.h>

static void PreRegistCallback()
{
	iTJSDispatch2 *global = TVPGetScriptDispatch();
	if (global)
	{
		tTJSVariant layer_val;
		static ttstr Layer_name(TJS_W("Layer"));
		global->PropGet(0, Layer_name.c_str(), Layer_name.GetHint(), &layer_val, global);
		tTJSVariantClosure layer_valclosure = layer_val.AsObjectClosureNoAddRef();
		if (layer_valclosure.Object)
		{
			layer_valclosure.DeleteMember(TJS_IGNOREPROP, TJS_W("doGrayScale"), 0, NULL);
		}
	}
}

NCB_PRE_REGIST_CALLBACK(PreRegistCallback);

class LayerLayerExDoGrayScale
{
public:
	static tjs_error TJS_INTF_METHOD doGrayScale(
		tTJSVariant	*result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis)
	{
		if(objthis == NULL) TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));
		tTJSVariant bmpobject = tTJSVariant(objthis, objthis);
		tTJSVariantClosure bmpobject_clo = bmpobject.AsObjectClosureNoAddRef();

		// Now get information (this will independ the bitmap)
		tjs_int bmpwidth = 0;
		tjs_int bmpheight = 0;
		tjs_int bmppitch = 0;
		tjs_uint8* bmpdata = NULL;
		GetBitmapInformationFromObject(bmpobject_clo, true, &bmpwidth, &bmpheight, &bmppitch, &bmpdata);
		if(!bmpdata) TVPThrowExceptionMessage(TJS_W("Specify Layer or Bitmap class object"));
		tTVPBaseBitmap bmpinfo(bmpwidth, bmpheight, bmppitch, bmpdata);

		tTVPRect ClipRect;
		tjs_int ImageLeft = 0;
		tjs_int ImageTop = 0;
		GetLayerInformationFromLayerObject(bmpobject_clo, NULL, NULL, &ClipRect, NULL, &ImageLeft, &ImageTop, NULL);

		DoGrayScale(&bmpinfo, ClipRect);

		UpdateLayerWithLayerObject(bmpobject_clo, &ClipRect, &ImageLeft, &ImageTop);
		return TJS_S_OK;
	}
};

NCB_ATTACH_CLASS(LayerLayerExDoGrayScale, Layer)
{
	RawCallback("doGrayScale", &Class::doGrayScale, 0);
};
