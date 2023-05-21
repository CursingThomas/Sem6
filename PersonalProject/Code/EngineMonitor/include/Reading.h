#include <string>
#include "time.h"
struct Reading
{
    uint8_t speed;
    uint8_t oilTemperature;
    uint16_t rpm;
    tm timeStamp;
};