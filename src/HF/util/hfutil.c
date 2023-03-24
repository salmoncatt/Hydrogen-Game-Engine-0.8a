#include "hfutil.h"
#ifdef _WIN32
#include <dbghelp.h> //for printing the stack
#endif

const u64 hf_string_npos = -1;

extern void* hf_memcpy(void* destination, const void* source, u64 size){
    char* dest = (char*)destination;
    const char* src = (const char*)source;
    
    u64 length = size;
    
#ifdef __AVX512__
    while (size >= 64) {
        __m256i val = _mm512_loadu_si512((__m512i*)(src));
        _mm512_storeu_si512((__m512i*)dest, val);
        dest += 64;
        src += 64;
        size -= 64;
    }
#endif
    
    while (size >= 32) {
        __m256i val = _mm256_loadu_si256((__m256i*)(src));
        _mm256_storeu_si256((__m256i*)dest, val);
        dest += 32;
        src += 32;
        size -= 32;
    }
    
    while (size >= 16) {
        __m128i val = _mm_loadu_si128((__m128i*)(src));
        _mm_storeu_si128((__m128i*)dest, val);
        dest += 16;
        src += 16;
        size -= 16;
    }
    
    if (length > 16) {
        src += size - 16;
        dest += size - 16;
        __m128i val = _mm_loadu_si128((__m128i*)(src));
        _mm_storeu_si128((__m128i*)(dest), val);
    }
    
    
    // TODO(salmoncatt): add masked load and store instead of this scalar crap pls
    while (size--) {
        *dest++ = *src++;
    }
    
    return destination;
}

extern b8 hf_strcmp(const char* a, const char* b){
    return hf_memcmp(a, b, hf_min(hf_strlen(a), hf_strlen(b)));
}

extern u64 hf_strlen(const char* data){
    // TODO(salmoncatt): make this faster pls (and hfStringFind too)
    const __m128i zeros = _mm_setzero_si128();
    __m128i* pointer = (__m128i*)(data);
    
    for (;; pointer++) {
        
        const __m128i current = _mm_loadu_si128(pointer);
        const __m128i comparison = _mm_cmpeq_epi8(current, zeros);
        u32 mask = _mm_movemask_epi8(comparison);
        
        if(mask){
            return ((char*)(pointer) - data) + hf_ctzu32(mask);
        }
        
        /* 
                if (_mm_cmpistrc(current, zeros, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH)) {
                    int index = _mm_cmpistri(current, zeros, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH);
                    
                    return ((char*)(pointer) - data) + index;
                }
         */
    }
}

// TODO(salmoncatt): convert strlen and strfind to _mm256i
extern u64 hf_strfind(const char d, const char* data, u64 startingIndex, u64 endingIndex){
    // TODO(salmoncatt): make this faster pls (and hfStringFind too)
    const __m128i delimiters = _mm_set_epi8(d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d);
    __m128i* pointer = (__m128i*)(data + startingIndex);
    
    // NOTE(salmoncatt): do this once so we dont have to do it every loop
    uptr endingPointer = (uptr)(data + endingIndex);
    
    if(startingIndex >= endingIndex)
        return hf_string_npos;
    
    //see
    for(;(uptr)(pointer) < endingPointer; pointer++){
        const __m128i current = _mm_loadu_si128(pointer);
        __m128i comparison = _mm_cmpeq_epi8(current, delimiters);
        u32 mask = _mm_movemask_epi8(comparison);
        
        if(mask){
            // NOTE(salmoncatt): pointer subraction instead of keeping track of index variable, then count trailing zeros
            u64 out = ((char*)(pointer) - data) + hf_ctzu32(mask);
            if(out < endingIndex)
                return out;
            else
                break;
        }
    }
    
    return hf_string_npos;
}

extern char* hf_strcpy(char* destination, const char* source, u64 offset){
    return (char*)hf_memcpy(destination, source + offset, hf_strlen(source) + 1 - offset);
}

extern b8 hf_memcmp(const void* aPointer, const void* bPointer, size_t bytes){
    /* 
        if(a == NULL || b == NULL)
            return 0;
     */
    __m128i* mAPointer = (__m128i*)aPointer;
    __m128i* mBPointer = (__m128i*)bPointer;
    
    while(bytes >= 16){
        __m128i a = _mm_loadu_si128(mAPointer);
        __m128i b = _mm_loadu_si128(mBPointer);
        
        __m128i comparison = _mm_cmpeq_epi8(a, b);
        u16 mask = _mm_movemask_epi8(comparison);
        
        
        // NOTE(salmoncatt): wont work if bytes > 16
        if(mask != (u16)((INT16_MIN + INT16_MAX)))
            break;
        
        bytes -= 16;
        mAPointer += 1;
        mBPointer += 1;
    }
    
    if(bytes > 0){
        __m128i a = _mm_loadu_si128((__m128i*)mAPointer);
        __m128i b = _mm_loadu_si128((__m128i*)mBPointer);
        
        __m128i comparison = _mm_cmpeq_epi8(a, b);
        u16 mask = _mm_movemask_epi8(comparison);
        
        //remove unnecessary bits from comparison
        mask <<= (16 - bytes);
        
        //u16 test = (u16)((INT16_MIN + INT16_MAX) << (16 - bytes));
        //hf_print_bits(&test, sizeof(u16));
        //hf_print_bits(&mask, sizeof(u16));
        
        // NOTE(salmoncatt): min = 10000... max = 011111... min + max = 11111...
        return mask == (u16)((INT16_MIN + INT16_MAX) << 16 - bytes);
    }else
        return 1;
}

/* 
char* hf_convert_to_bits(u64 size, const void* data){
    /* 
char* bytes = (char*)data;
char* out = (char*)hf_malloc((size * 8) + 1);
char byte;
int i, j;

for(i = size - 1; i >= 0; i--){
for(j = 7; j >= 0; j--){
byte = (bytes[i] >> j) & 1;
//out[i * j] = byte;
//printf("%u", byte);
}
}
puts("");


out[size * 8] = '\0';

return out;
*/
//return 0;
//}
//*/

void hf_print_bits(const void* data, u64 size){
    char* bytes = (char*)data;
    char byte;
    int i, j;
    
    for(i = size - 1; i >= 0; i--){
        for(j = 7; j >= 0; j--){
            byte = (bytes[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

u32 hf_ctzu32(u32 in){
    u32 c = 32; // c will be the number of zero bits on the right
    in &= -in;
    if (in) c--;
    if (in & 0x0000FFFF) c -= 16;
    if (in & 0x00FF00FF) c -= 8;
    if (in & 0x0F0F0F0F) c -= 4;
    if (in & 0x33333333) c -= 2;
    if (in & 0x55555555) c -= 1;
    
    return c;
    //return __builtin_ctz(in);
}

char* hf_concat(const char* a, const char* b){
    u64 size_a = hf_strlen(a);
    
    char* out = (char*)hf_malloc(size_a + hf_strlen(b));
    
    
    hf_strcpy(out, a, 0);
    hf_strcpy(out, b, size_a);
    
    return out;
}


char* hf_format_string(const char* msg, ...){
    va_list args;
    va_start(args, msg);
    hf_vformat_string(msg, args);
    va_end(args);
}

char* hf_vformat_string(const char* msg, va_list args){
    u64 buffer_size = 0;
    char* formatted_msg = (char*)hf_malloc(256);;
    i32 length = vsnprintf(formatted_msg, 256, msg, args);
    
    if(length > 256){
        i32 old_length = length;
        hf_free(formatted_msg);
        formatted_msg = (char*)hf_malloc(length + 64);
        length = vsnprintf(formatted_msg, length + 64, msg, args);
        
        if(length > old_length + 64){
            hf_err("hf_format_string couldn't allocate enough memory for string: %s", msg);
        }
    }
    
    return formatted_msg;
}

void hf_print_stack() {
#ifdef _WIN32
    unsigned int   i;
    void         * stack[ 100 ];
    unsigned short frames;
    SYMBOL_INFO  * symbol;
    HANDLE         process;
    
    process = GetCurrentProcess();
    
    SymInitialize( process, NULL, TRUE );
    
    frames               = CaptureStackBackTrace( 0, 100, stack, NULL );
    symbol               = ( SYMBOL_INFO * )calloc( sizeof( SYMBOL_INFO ) + 256 * sizeof( char ), 1 );
    symbol->MaxNameLen   = 255;
    symbol->SizeOfStruct = sizeof( SYMBOL_INFO );
    
    DWORD displacement;
    IMAGEHLP_LINE64 line;
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    
    printf("printing stack... \n");
    
    for( i = 0; i < frames; i++ )
    {
        DWORD64 address = (DWORD64)(stack[i]);
        SymFromAddr( process, address, 0, symbol );
        
        if(SymGetLineFromAddr64(process, address, &displacement, &line)){
            printf("%i: %s - 0x%pS, file: %s, line: %lu\n", frames - i - 1, symbol->Name, symbol->Address, line.FileName, line.LineNumber);
        }else{
            printf("%i:%s - 0x%pS\n", frames - i - 1, symbol->Name, symbol->Address);
        }
        
        
        /* 
                if(SymGetLineFromAddr64(process, address, &displacement, &line)){
                    hf_log( "$hfcc{aqua}%i$hfcc{white}: $hfcc{green}%s $hfcc{white} - $hfcc{blue}0x%pS$hfcc{white}, $hfcc{aqua}file$hfcc{white}: $hfcc{green}%s$hfcc{white}, $hfcc{aqua}line$hfcc{white}: $hfcc{blue}%lu\n", frames - i - 1, symbol->Name, symbol->Address, line.FileName, line.LineNumber);
                }else{
                    hf_log( "$hfcc{aqua}%i$hfcc{white}:$hfcc{green}%s $hfcc{white} - $hfcc{blue}0x%pS\n", frames - i - 1, symbol->Name, symbol->Address);
                }
         */
        
    }
    
    printf("\n");
    
    __real_free(symbol);
#endif
}

/* 
u32 hf_highestOneBit(u32 in){
    return hf_ctzu32(in);
    in |= (in >>  1);
    in |= (in >>  2);
    in |= (in >>  4);
    in |= (in >>  8);
    in |= (in >> 16);
    return in - (in >> 1);
}

u32 hfHighestZeroBit(u32 in){
    return hf_ctzu32(!in);
}
 */


char* hf_load_file_as_string(const char* file_path){
    FILE* file = fopen(file_path, "r");
    char* out;
    u64 length;
    
    if(file){
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        out = hf_malloc(length + 1);
        
        if(out){
            fread(out, 1, length, file);
            out[length] = '\0';
        }else{
            hf_err("couldn't allocated buffer for file: %s", file_path);
            fclose(file);
            return NULL;
        }
        
        fclose(file);
    }else{
        hf_err("couldn't read file: %s", file_path);
        return NULL;
    }
    
    return out;
}

char* hf_remove_file_path(const char* file_path){
    char* fwd = strrchr(file_path, '/');
    char* bck = strrchr(file_path, '\\');
    
    u32 fwd_slash_index = 0;
    u32 bck_slash_index = 0;
    
    if(fwd){
        fwd_slash_index = (u32)(fwd - file_path);
    }
    
    if(bck){
        bck_slash_index = (u32)(bck - file_path);
    }
    
    u32 index = hf_max(fwd_slash_index, bck_slash_index);
    
    
    return hf_string_substr(file_path, index + 1, hf_strlen(file_path));
}

char* hf_get_cpu_name(){
#ifdef _WIN32
    int CPUInfo[4] = { -1 };
    char* CPUBrandString = hf_malloc(sizeof(char) * 65);
    __cpuid(CPUInfo, 0x80000000);
    unsigned int nExIds = CPUInfo[0];
    
    memset(CPUBrandString, 0, sizeof(CPUBrandString));
    
    // Get the information associated with each extended ID.
    for (unsigned int i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(CPUInfo, i);
        // Interpret CPU brand string.
        if (i == 0x80000002)
            hf_memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            hf_memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            hf_memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }
    
    CPUBrandString[64] = '\0';
    
    return CPUBrandString;
#endif
}