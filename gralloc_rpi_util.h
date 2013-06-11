#ifndef GRALLOC_RPI_UTIL_H_
#define GRALLOC_RPI_UTIL_H_

#include <ui/PixelFormat.h>

#include "interface/vctypes/vc_image_types.h"

static VC_IMAGE_TYPE_T convert_android_to_vc_img_type(int format) {
	VC_IMAGE_TYPE_T type = VC_IMAGE_RGB565;
	switch (format) {
	case android::PIXEL_FORMAT_RGBA_8888:
		type = VC_IMAGE_RGBA32;
		break;
	case android::PIXEL_FORMAT_BGRA_8888:
		type = VC_IMAGE_BGRX8888;
		break;
	case android::PIXEL_FORMAT_RGBA_5551:
		type = VC_IMAGE_TF_RGBA5551;
		break;
	case android::PIXEL_FORMAT_RGBA_4444:
		type = VC_IMAGE_RGBA16;
		break;
	case android::PIXEL_FORMAT_RGBX_8888:
		type = VC_IMAGE_RGBX8888;
		break;
	case android::PIXEL_FORMAT_RGB_888:
		type = VC_IMAGE_RGB888;
		break;
	case android::PIXEL_FORMAT_RGB_565:
	default:
		type = VC_IMAGE_RGB565;
		break;
	}
	return type;
}

#endif /* GRALLOC_RPI_UTIL_H_ */
