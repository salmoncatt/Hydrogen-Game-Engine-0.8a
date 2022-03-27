/* date = August 26th 2021 6:47 pm */

//HF's precompiled header file

#ifndef HFPCH_H
#define HFPCH_H

// NOTE(salmoncatt): the standard hf_icon in res/icon.png
//#define HF_ICON 101 //look in res.rc if you want to make your own

// NOTE(salmoncatt): this gets removed or left depending on how you compile in the makefile
#define HF_DEBUG

#include "datatypes/hfdatatypes.h"
#include "util/hfmemutil.h"

#include <GL/gl.h>
//#include <GL/glext.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <time.h>
#include <math.h>
//for cpuid
#include <intrin.h>

//for __debugbreak();
#include <signal.h>

#include "math/hfmath.h"
#include "time/hftime.h"
#include "util/hfutil.h"
#include "debug/hfdebug.h"
#include "datatypes/hfstring.h"
#include "datatypes/hfvector.h"
#include "io/hfinput.h"

#include "opengl/hfgl.h"

#include "datatypes/hffloatbuffer.h"


#include "graphics/stb_image.h"


#endif //HFPCH_H
