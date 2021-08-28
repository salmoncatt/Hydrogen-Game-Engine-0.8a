/* date = August 16th 2021 0:49 pm */

#ifndef HF_H
#define HF_H

//#ifdef _WIN32 || _WIN64
#include <windows.h>
//#endif
// TODO(salmoncatt): add linux headers n stuff pls


// TODO(salmoncatt): come up with a better header name pls
#include "datatypes/hfdatatypes.h"
#include "datatypes/hfvector.h"
#include "datatypes/hflinkedlist.h"
#include "datatypes/hfstring.h"

#include "util/hfutil.h"
#include "util/hfgl.h"

#include "math/hfmath.h"

#include "debug/hfdebug.h"

//#ifdef _WIN32 || _WIN64
#include "io/hfwindow.h"
//#endif

#include "time/hfprofiler.h"

#endif //HF_H
