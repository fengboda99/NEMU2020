#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "jnb-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jnb-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jnb-template.h"
#undef DATA_BYTE

make_helper_v(jnb_i);



