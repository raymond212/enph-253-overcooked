#pragma once
#include <cstdint>

namespace Opcodes {

    enum class opcodes : uint8_t {
        ACK = 0x00,  // No Operation
        START = 0x01,
        STOP = 0x02,
        B_BUNS = 0x03,
        PATTIES = 0x04,
        T_BUNS = 0x05
        // Add other opcodes with hexadecimal values as needed
    };

}

struct Message {
    Opcodes::opcodes opcode;
    uint8_t data[10];  // Example additional data
};
