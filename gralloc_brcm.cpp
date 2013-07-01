/*
 * "gralloc" (not in Android terms) to add missing functions to raspberry pi userland driver.
 *
 * Author: aharter
 */

#include "gralloc_brcm.h"
#include "gralloc_rpi_util.h"
#include "bcm_host.h"

uint32_t allocate_and_set_vc_handle(gralloc_private_handle_t *private_handle) {
    uint32_t vc_handle = 0;
    DISPMANX_RESOURCE_HANDLE_T resource_handle = vc_dispmanx_resource_create(
            convert_android_to_vc_img_type(private_handle->pixel_format), private_handle->w, private_handle->h,
            &vc_handle);

    //vc_dispmanx_resource_create set vc_handle to 0
    //call to vc_dispmanx_resource_get_image_handle is needed
    vc_handle = vc_dispmanx_resource_get_image_handle(resource_handle);

    return vc_handle;
}

int gralloc_get_gl_format(int android_buffer_format){
    switch (android_buffer_format)
		{
		  case PIXEL_FORMAT_RGBA_8888:
		  case PIXEL_FORMAT_BGRA_8888:
		  case PIXEL_FORMAT_RGBA_5551:
		  case PIXEL_FORMAT_TRANSLUCENT:
		  case PIXEL_FORMAT_TRANSPARENT:
		  case PIXEL_FORMAT_RGBA_4444:	return GRALLOC_MAGICS_HAL_PIXEL_FORMAT_TRANSLUCENT;

		  case PIXEL_FORMAT_OPAQUE:
		  case PIXEL_FORMAT_RGBX_8888:
		  case PIXEL_FORMAT_RGB_565:
		  case PIXEL_FORMAT_RGB_888:    
		  default :                     return GRALLOC_MAGICS_HAL_PIXEL_FORMAT_OPAQUE;
	    }
}

gralloc_private_handle_t* gralloc_private_handle_from_client_buffer(EGLClientBuffer buffer) {
    bcm_host_init();

    gralloc_private_handle_t* gralloc_handle = (gralloc_private_handle_t*) malloc(sizeof(gralloc_private_handle_t));
    android_native_buffer_t *android_buffer = (android_native_buffer_t *) buffer;
    gralloc_handle->res_type = GRALLOC_PRIV_TYPE_MM_RESOURCE;
    gralloc_handle->w = android_buffer->width;
    gralloc_handle->h = android_buffer->height;
    gralloc_handle->stride = android_buffer->stride;
    gralloc_handle->buffer = android_buffer;
    //gralloc_handle->gl_format = GRALLOC_MAGICS_HAL_PIXEL_FORMAT_OPAQUE;
    gralloc_handle->gl_format = gralloc_get_gl_format(android_buffer->format);
    gralloc_handle->pixel_format = android_buffer->format;

    gralloc_handle->vc_handle = allocate_and_set_vc_handle(gralloc_handle);

    return gralloc_handle;
}

uint32_t gralloc_private_handle_get_res_type(gralloc_private_handle_t* private_handle) {
    return private_handle->res_type;
}

uint32_t gralloc_private_handle_get_vc_handle(gralloc_private_handle_t *private_handle) {
    return private_handle->vc_handle;
}

uint32_t gralloc_private_handle_get_egl_image(gralloc_private_handle_t *private_handle) {
    return (uint32_t)private_handle->buffer;
}
