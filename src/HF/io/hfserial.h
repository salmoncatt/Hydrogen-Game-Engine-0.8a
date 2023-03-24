/* date = December 17th 2021 9:20 pm */

#ifndef HFSERIAL_H
#define HFSERIAL_H

#define hf_arduino_wait_time 2000

typedef struct hf_serial_port {
    b8 connected;
    const char* name;
#ifdef _WIN32
    HANDLE port;
    
    COMSTAT status;
    DWORD errors;
#endif
    
} hf_serial_port;

void hf_serial_list_open_ports();

hf_serial_port hf_serial_open_port(const char* port_name, u32 baud_rate);

b8 hf_serial_write(hf_serial_port* port, const char* buffer, u32 length);

u32 hf_serial_read(hf_serial_port* port, char* buffer, u32 length, const char ending_character);

u32 hf_serial_read_data_waiting(hf_serial_port* port);

//u32 hf_serial_read_until(hf_serial_port* port, char* buffer, u32 length);

b8 hf_serial_wait_for_data(hf_serial_port* port);

void hf_serial_close_port(hf_serial_port* port);

#endif //HFSERIAL_H
