#include "hftime.h"
#include <time.h>
//#include "hfpch.h"


u64 hf_get_time(){
    return time(NULL);
}