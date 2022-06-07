/* date = June 6th 2022 10:16 pm */

#ifndef HFGUI_IMAGE_H
#define HFGUI_IMAGE_H

typedef struct hf_gui_image{
    
    const char* name;
    v2f pos;
    v2f size;
    f32 rotation;
    v2f anchorpoint;
    b8 size_type;
    b8 visible;
    
    
}hf_gui_image;

#endif //HFGUI_IMAGE_H
