#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/push.h"
#include "data-mov/pop.h"

#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/cmp.h"
#include "arith/sub.h"
#include "arith/add.h"

#include "control-trans/call.h"
#include "control-trans/je.h"
#include "control-trans/ret.h"
#include "control-trans/jmp.h"
#include "control-trans/jle.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"
#include "logic/test.h"

#include "string/rep.h"

#include "misc/misc.h"

#include "special/special.h"
