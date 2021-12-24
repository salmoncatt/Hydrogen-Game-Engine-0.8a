#include "hf3dprint.h"

void hf_3d_printer_run_gcode(hf_serial_port* port, const char* gcode_file){
    FILE* file = fopen(gcode_file, "r");
    u64 length;
    char line[1024];
    char buffer[512];
    
    u64 index = 0;
    
    if(file){
        while(fgets(line, 1024, file) != NULL){
            
            //hf_log("%s\n", line);
            
            char* code = hf_string_substr(line, 0, hf_strfind(';', line, 0, hf_strlen(line)));
            
            
            hf_log("running command: [%s]\n", code);
            
            strcat(code, "\n");
            
            //line_code = hf_concat(line, "\n"); // NOTE(salmoncatt): make sure theres a new line to show the end of a command
            
            hf_serial_write(port, code, hf_strlen(line) + 1);
            
            
            //Sleep(100);
            
            hf_serial_wait_for_data(port);
            hf_serial_read(port, buffer, 512, '\n');
            
            
            /* 
                        while(1){
                            if(hf_serial_read(port, buffer, 512) > 0)
                                break;
                            
                            Sleep(1); //just wait for 3d printer to respond with success or fail
                        }
             */
            
            
            hf_log("code recieved: [%s]\n", buffer);
            
            
            hf_free(code);
            
            /* 
                        hf_serial_write(port, line, hf_strlen(line) + 1);
                        
                        Sleep(10);
                        
                        while(!hf_serial_read(port, buffer, 255)){
                            Sleep(10); //just wait for 3d printer to respond with success or fail
                        }
                        
                        if(!hf_strcmp("gcode success", buffer)){
                            hf_err("couldn't run gcode: %s", line);
                            return;
                        }else{
                            index += 1;
                            hf_log("gcode ran\n");
                        }
             */
        }
        fclose(file);
    }else{
        hf_err("couldn't read file: %s", gcode_file);
    }
    
}