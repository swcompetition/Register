#include "Register.h"

#if defined(TEST_DEBUG)
/**
 * For testing purpose, use value from string.
 * Basically this constructor will use full_reg_address value based on tmp value. 
 * tmp string must contain one of arithmetic operation, such as "add" and should be 32-bit. 
 * Every bits over 32-bit will abandoned, and more than 1-value would be saved in array as '1'
 */
Register::Register(string& tmp) {
    if (tmp.length() < 32) {
        return;
    }
    for (int i = 0; i < MAX_BITS; i++) {
        full_reg_address[i] = (tmp.at(i) - '0');
    }
    init();
}
#endif

Register::Register() {
    init();
}

/**
 * Parse OPCODE, Read Register(1/2), Write Register
 * from "full_reg_address", which is full 32-bit-binary formed 
 * instruction.
 */
void Register::init() {
    // Constant value for starting point of each reg;
    // DO NOT MODIFY WITHOUT ANY PERMISSION
    const int start_opcode = 0;
    const int start_regone = 6;
    const int start_regtwo = 11;
    const int start_wr = 16;
    int idx_val = 0;

    // Parse OPCODE
    for (int i = start_opcode; i < start_opcode+OPCODE_BITS; i++) {
        opcode_bits[idx_val] = full_reg_address[start_opcode+idx_val];
        idx_val++;
    }
    idx_val = 0;

    // Parse Read Register 1
    for (int i = start_regone; i < start_regone + RR_ONE; i++) {
        readReg_one_bits[idx_val] = full_reg_address[start_regone+idx_val];
        idx_val++;
    }
    idx_val = 0;

    // Parse Read Register 2
    for (int i = start_regtwo; i < start_regtwo + RR_TWO; i++) {
        readReg_one_bits[idx_val] = full_reg_address[start_regtwo+idx_val];
        idx_val++;
    }
    idx_val = 0;

    // Parse Write Register
    for (int i = start_wr; i < start_wr + RR_TWO; i++) {
        readReg_one_bits[idx_val] = full_reg_address[start_wr+idx_val];
        idx_val++;
    }
}