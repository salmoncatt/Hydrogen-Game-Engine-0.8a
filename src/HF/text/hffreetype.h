/* date = June 14th 2022 7:08 pm */

#ifndef HFFREETYPE_H
#define HFFREETYPE_H

extern FT_Library hf_ftlibrary;

void hf_free_type_init();
void hf_free_type_close();

FT_Face hf_load_face(const char* path);

#endif //HFFREETYPE_H
