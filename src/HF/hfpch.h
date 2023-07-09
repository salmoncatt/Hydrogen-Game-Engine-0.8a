/* date = August 26th 2021 6:47 pm */

//HF's precompiled header file

#ifndef HFPCH_H
#define HFPCH_H

// NOTE(salmoncatt): this gets removed or left depending on how you compile in the makefile
#define HF_DEBUG

#include "datatypes/hfdatatypes.h"
#include "util/hfmemutil.h"


#include <GL/gl.h>

#ifdef _WIN32
#include <windows.h>
//for cpuid
#include <intrin.h>
#elif defined(__linux__)
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/glx.h>
#include<GL/glu.h>

//#include <time.h>
#include <sys/time.h>

//for scancodes
#include <X11/XKBlib.h>

//for XDeviceMotionEvent
#include <X11/extensions/XInput.h>

#include <unistd.h>
#endif

//#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <time.h>
#include <math.h>
#include <string.h>

//for __debugbreak();
#include <signal.h>

#include "hfres.h"

#include "math/hfmath.h"
#include "time/hftime.h"
#include "util/hfutil.h"
#include "debug/hfdebug.h"
#include "datatypes/hfstring.h"
#include "datatypes/hfvector.h"
#include "datatypes/hfarray.h"
#include "io/hfinput.h"

#include "opengl/hfgl.h"

#include "datatypes/hffloatbuffer.h"

#include "rendering/hfrenderer.h"
#include "rendering/hfrenderer2d.h"

#include "graphics/stb_image.h"


#include "ft2build.h"
#include "freetype/freetype.h"

#endif //HFPCH_H
