/* date = August 26th 2021 6:47 pm */

//HF's precompiled header file

#ifndef HFPCH_H
#define HFPCH_H


// NOTE(salmoncatt): this gets removed or left depending on how you compile in the makefile
#define HF_DEBUG

#include "datatypes/hfdatatypes.h"
#include "util/hfmemutil.h"

#include <GL/gl.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <time.h>

//for __debugbreak();
#include <signal.h>

#include "math/hfmath.h"
#include "util/hfutil.h"
#include "debug/hfdebug.h"
#include "datatypes/hfstring.h"
#include "datatypes/hfvector.h"
#include "io/hfinput.h"

#endif //HFPCH_H
