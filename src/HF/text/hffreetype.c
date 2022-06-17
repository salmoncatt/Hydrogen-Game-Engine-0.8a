#include "hffreetype.h"

FT_Library hf_ftlibrary = NULL;

void hf_free_type_init(){
    if(!FT_Init_FreeType(&hf_ftlibrary)){
        printf("[HF FT] initialized freetype\n\n");
    }else{
        hf_err("[HF FT] couldn't initialize freetype\n\n");
    }
}

void hf_free_type_close(){
    if(!FT_Done_FreeType(hf_ftlibrary)){
        printf("[HF FT] closed freetype\n");
    }else{
        hf_err("[HF FT] couldn't close freetype\n");
    }
}

FT_Face hf_load_face(const char* path){
    FT_Face face = NULL;
    FT_Error error = FT_New_Face(hf_ftlibrary, path, 0, &face);
    
    if(error == FT_Err_Unknown_File_Format){
        hf_err("[HF FT] unknown font file format at: [%s]\n", path);
    }else if(error){
        hf_err("[HF FT] couldn't load font : [%s]\n", path);
    }
    
    return face;
}