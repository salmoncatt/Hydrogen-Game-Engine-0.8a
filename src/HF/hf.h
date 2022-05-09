/* date = August 16th 2021 0:49 pm */

#ifndef HF_H
#define HF_H

#define HF_RES "../res/"

#define HF_SUCCESS 1
#define HF_FAIL 0

// TODO(salmoncatt): add linux headers n stuff pls

#include "core/hfapp.h"

#include "ecs/hfecs.h"
#include "ecs/hfcomponents.h"

#include "datatypes/hfdatatypes.h"
#include "datatypes/hfvector.h"
#include "datatypes/hfarray.h"
#include "datatypes/hflinkedlist.h"
#include "datatypes/hfstring.h"
#include "datatypes/hffloatbuffer.h"

#include "util/hfutil.h"
#include "opengl/hfgl.h"

#include "math/hfmath.h"

#include "debug/hfdebug.h"

//#ifdef _WIN32 || _WIN64
#include "io/hfwindow.h"
#include "io/hfinput.h"
#include "io/hfserial.h" //for arduino n stuff
#include "io/hf3dprint.h"
//#endif

#include "time/hfprofiler.h"
#include "time/hftime.h"

#include "graphics/stb_image.h"
#include "graphics/hfimage.h"

#include "mesh/hfmesh.h"
#include "mesh/hftexture.h"

#include "rendering/hfrenderer.h"
#include "rendering/hfrenderer2d.h"
#include "rendering/hfshader.h"


#endif //HF_H
