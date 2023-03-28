/* date = March 7th 2022 6:24 pm */

#ifndef HFDEBUGCAMERA_H
#define HFDEBUGCAMERA_H

#include "hfcamera.h"

typedef struct hf_debug_camera{
    
    hf_camera camera;
    hf_transform transform;
    f32 sensitivity, movement_speed, dir_x, dir_z;
    v3f direction;
    
}hf_debug_camera;

void hf_update_debug_camera(hf_debug_camera* camera);

#endif //HFDEBUGCAMERA_H
