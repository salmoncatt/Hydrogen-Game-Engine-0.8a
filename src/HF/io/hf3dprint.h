/* date = December 19th 2021 0:26 pm */

#ifndef HF3DPRINT_H
#define HF3DPRINT_H

#include "hfserial.h"

void hf_3d_printer_run_gcode(hf_serial_port* port, const char* gcode_file);

#endif //HF3DPRINT_H
