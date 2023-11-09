#pragma once

#include "stdint.h"

/* Определения адресов регистров */
//Область RAM
enum ADE7880_REG : uint16_t
{
    AIGAIN = 0x4380,
    AVGAIN,
    BIGAIN,
    BVGAIN,
    CIGAIN,
    CVGAIN,
    NIGAIN,
    RESERVED1,
    DICOEFF
};