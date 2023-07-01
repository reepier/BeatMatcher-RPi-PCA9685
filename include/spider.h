#include <vector>

#include "animator.h"

class SpiderFixture;
class SpiderAnimation;

class SpiderFixture : public BaseFixture{
    std::vector<std::vector<uint8_t>> RGBW;
};