#pragma once

#include "spot.h"
#include "laser.h"
#include "spider.h"
#include "LED.h"
#include "addr_LED.h"


// contains every individual (low level) fixture (1 element = 1 physical fixture with its own adress)
extern fix_vec ll_fxtrs;
// contain "animation level" (high level) fixtures (1 element = 1 structure of fixtures controlled together)
extern fix_vec fixtures;