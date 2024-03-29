#include "hfserial.h"
// NOTE(salmoncatt): bro i literally just stole from this: https://playground.arduino.cc/Interfacing/CPPWindows/



#include <fcntl.h> 


void hf_serial_print_open_ports(){
    char buffer[5000];
    char com[20];
    
    hf_log("[HF SERIAL] finding all open ports...\n");
    
#ifdef _WIN32
    // NOTE(salmoncatt): loop through all ports and get avaible ports
    for(u32 i = 0; i < 255; i++){
        sprintf_s(com, 20, "COM%u", i);
        
        DWORD result = QueryDosDevice(com, buffer, 5000);
        
        //hf_log("%s\n", com);
        
        if(result != 0){
            hf_log("[HF SERIAL] found port: [COM%u]\n", i);
        }
    }
    
#elif defined(__linux__)
    
    
    const char* usb_dirs[] = {"/dev/tty%u", "/dev/ttyS%u", "/dev/ttyACM%u"};
    
    for(u32 dir_num = 0; dir_num < 3; dir_num++){
        for(u32 i = 0; i < 255; i++){
            
            sprintf(com, usb_dirs[dir_num], i);
            
            
            
            int result = open(com, O_RDWR | O_NOCTTY | O_SYNC);
            
            //hf_log("%s\n", com);
            
            if(result >= 0){
                hf_log("[HF SERIAL] found port: [%s]\n", com);
            }
        }
    }
    
    
    
#endif
    
    hf_log("[HF SERIAL] found all open ports\n\n");
}

char* hf_serial_list_open_ports(){
    char buffer[5000];
    char* out = hf_malloc(1024);
    char com[20];
    
    strcpy(out, "[HF SERIAL] finding all open ports...\n");
    //strcat(out, "test\n");
    
#ifdef _WIN32
    // NOTE(salmoncatt): loop through all ports and get avaible ports
    for(u32 i = 0; i < 255; i++){
        sprintf_s(com, 20, "COM%u", i);
        
        DWORD result = QueryDosDevice(com, buffer, 5000);
        
        //hf_log("%s\n", com);
        
        if(result != 0){
            sprintf_s(com, 20, " COM%u \n", i);
            strcat(out, com);
        }
    }
    
#endif 
    
    
    return out;
}

hf_serial_port hf_serial_open_port(const char* port_name, u32 baud_rate){
#ifdef _WIN32
    hf_serial_port out = {};
    out.connected = 0;
    
    out.port = CreateFile(port_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if(out.port == INVALID_HANDLE_VALUE){
        
        if(GetLastError() == ERROR_FILE_NOT_FOUND){
            hf_log("[HF SERIAL] error, port: %s couldn't open a connection, handle was not attached, uknown reason for this (check your connection and port?)\n", port_name);
        }else{
            hf_log("[HF SERIAL] error, couldn't open port: %s, uknown reason\n", port_name);
        }
        
    }else{
        
        DCB serial_params = {};
        
        if(!GetCommState(out.port, &serial_params)){
            hf_log("[HF SERIAL] error, couldn't get serial parameters for port: %s", port_name);
        }else{
            
            
            // NOTE(salmoncatt): get the baud rate
            serial_params.BaudRate = baud_rate;
            serial_params.ByteSize = 8;
            serial_params.StopBits = ONESTOPBIT;
            serial_params.Parity = NOPARITY;
            
            serial_params.fDtrControl = DTR_CONTROL_ENABLE;
            //serial_params.fRtsControl = RTS_CONTROL_ENABLE;
            //serial_params.fBinary = 1;
            
            if(!SetCommState(out.port, &serial_params)){
                hf_log("[HF SERIAL] error, couldn't set serial parameters for port: %s", port_name);
            }else{
                
                out.connected = 1;
                out.name = port_name;
                hf_log("[HF SERIAL] successfully opened port: %s with baud rate: %u\n", port_name, baud_rate);
                Sleep(hf_arduino_wait_time);
            }
        }
    }
    
    return out;
#elif defined(__linux__)
    
    /* 
        int port_num = open(port_name, O_RDWR | O_NOCTTY | O_SYNC);
        
        
        struct termios tty;
        if (tcgetattr (port_num, &tty) != 0)
        {
            printf("failed to open serial port [%s]\n", port_name);
            //error_message ("error %d from tcgetattr", errno);
            //return -1;
        }
        
        cfsetospeed (&tty, baud_rate);
        cfsetispeed (&tty, baud_rate);
        
        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
        
        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
        
        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;
        
        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
            printf("failed to open serial port [%s]\n", port_name);
            //error_message ("error %d from tcsetattr", errno);
            //return -1;
        }
     */
    //return 0;
    
#endif
}

b8 hf_serial_write(hf_serial_port* port, const char* buffer, u32 length){
#ifdef _WIN32
    /* 
        if(!port->connected){
            hf_log("[HF SERIAL] error, trying to read from port: %s but it's closed\n", port->name);
            return 0;
        }
     */
    DWORD bytes_sent;
    
    if(!WriteFile(port->port, (void*)buffer, length, &bytes_sent, 0)){
        ClearCommError(port->port, &port->errors, &port->status);
        return 0;
    }else
        return 1;
#endif
}

u32 hf_serial_read(hf_serial_port* port, char* buffer, u32 length, const char ending_character){
#ifdef _WIN32
    /* 
        if(!port->connected){
            hf_log("[HF SERIAL] error, trying to read from port: %s but it's closed\n", port->name);
            return 0;
        }
     */
    
    DWORD bytes_read;
    u32 to_read = 0;
    
    ClearCommError(port->port, &port->errors, &port->status);
    
    if(port->status.cbInQue > 0){
        
        if(port->status.cbInQue > length){
            to_read = length;
        }else
            to_read = port->status.cbInQue;
        
        if(ReadFile(port->port, buffer, to_read, &bytes_read, NULL)){
            return bytes_read;
        }
    }
    
    return 0;
#endif
}

u32 hf_serial_read_data_waiting(hf_serial_port* port){
    if(!port->connected)
        return 0;
    
#ifdef _WIN32
    ClearCommError(port->port, &port->errors, &port->status);
    
    return (u32)(port->status.cbInQue);
#endif
}

b8 hf_serial_wait_for_data(hf_serial_port* port){
#ifdef _WIN32
    while(hf_serial_read_data_waiting(port) == 0){
        Sleep(10);
    }
#endif
    
    return 1;
}

/* 
u32 hf_serial_read_until(hf_serial_port* port, char* buffer, u32 length){
    if(!port->connected){
        hf_log("[HF SERIAL] error, trying to read from port: %s but it's closed\n", port->name);
        return 0;
    }
    
    DWORD bytes_read;
    u32 to_read;
    
    ClearCommError(port->port, &port->errors, &port->status);
    
    if(port->status.cbInQue > 0){
        
        if(port->status.cbInQue > length){
            to_read = length;
        }else
            to_read = port->status.cbInQue;
        
        if(ReadFile(port->port, buffer, to_read, &bytes_read, NULL)){
            return bytes_read;
        }
    }
    
    return 0;
}
 */

void hf_serial_close_port(hf_serial_port* port){
#ifdef _WIN32
    CloseHandle(port->port);
    port->connected = 0;
#endif
    hf_log("[HF SERIAL] closed port: %s\n", port->name);
}