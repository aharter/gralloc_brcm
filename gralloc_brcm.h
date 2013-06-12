#ifndef _GRALLOC_BRCM_H
#define _GRALLOC_BRCM_H

#include <system/window.h>
#include <ui/android_native_buffer.h>
#include <EGL/egl.h>

const int GRALLOC_PRIV_TYPE_MM_RESOURCE = 0;
const int GRALLOC_PRIV_TYPE_GL_RESOURCE = 1;

const int GRALLOC_MAGICS_HAL_PIXEL_FORMAT_OPAQUE = 0;

typedef struct gralloc_private_handle_t {

    int res_type;
    int w;
    int h;
    int stride;
    uint32_t vc_handle;
    int gl_format;
    int pixel_format;
    android_native_buffer_t * buffer;

} gralloc_private_handle_t;

#ifdef __cplusplus
extern "C" {
#endif

gralloc_private_handle_t* gralloc_private_handle_from_client_buffer(EGLClientBuffer buffer);

uint32_t gralloc_private_handle_get_res_type(gralloc_private_handle_t* private_handle);

uint32_t gralloc_private_handle_get_vc_handle(gralloc_private_handle_t *private_handle);

uint32_t gralloc_private_handle_get_egl_image(gralloc_private_handle_t *private_handle);

#ifdef __cplusplus
};
#endif

#endif //_GRALLOC_BRCM_H
