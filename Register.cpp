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

Register::Register(string& rs, string&rt, string& rd) {
    rd_destination = 0;
    for (int i = 0; i < RR_ONE; i++) {
        readReg_one_bits[i] = rs.at(i) - '0';
    }

    for (int i = 0; i < RR_TWO; i++) {
        readReg_two_bits[i] = rt.at(i) - '0';
    }

    for (int i = 0; i < WR_BITS; i++) {
        writeReg_bits[i] = rd.at(i) - '0';
        rd_destination += pow(2, i) * writeReg_bits[i];
    }

    forward();
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
        readReg_two_bits[idx_val] = full_reg_address[start_regtwo+idx_val];
        idx_val++;
    }
    idx_val = 0;

    // Parse Write Register
    rd_destination = 0;
    for (int i = start_wr; i < start_wr + RR_TWO; i++) {
        writeReg_bits[idx_val] = full_reg_address[start_wr+idx_val];
        rd_destination += pow(2, idx_val) * writeReg_bits[idx_val];
        idx_val++;
    }
}

/**
 * Forward values to ALU
 * source to forward(addr): RS/RT --> readReg_one_bits, readReg_two_bits
 * Actual value will be forwarded in binary format.
 */
void Register::forward() {
    int rs_idx = register_memory.conv_bin_dec_idx(readReg_one_bits, RR_ONE);
    int rt_idx = register_memory.conv_bin_dec_idx(readReg_two_bits, RR_TWO);

    // Those boolean value is CREATED from R-Mem, dynamically
    bool* rs_forward = register_memory.get_actual_bin(rs_idx);
    bool* rt_forward = register_memory.get_actual_bin(rt_idx);
}

/**
 * Since this function called, it means "Write Data" signal is set to "true"
 * which means we have to write some alu-result data to write register.
 * 
 * Since we are implementing MIPS simulator on C++/High-Level, we need to declare some
 * array to store data.(We can't just store real MIPS register though)
 * 
 * So, this function will be just store alu-result, which would be "value" to register_mem's container.
 */
void Register::setRDValue(int& value) {
    register_memory.set_actual_dec(rd_destination, value);
}

// For testing purpose
#if defined(TEST_DEBUG)
void Register::printArray() {
    const int start_opcode = 0;
    const int start_regone = 6;
    const int start_regtwo = 11;
    const int start_wr = 16;
    int idx_val = 0;

    // Parse OPCODE
    cout << "OPCODE: ";
    for (int i = start_opcode; i < start_opcode+OPCODE_BITS; i++) {
        cout << opcode_bits[idx_val] << " ";
        idx_val++;
    }
    cout << endl;
    idx_val = 0;

    // Parse Read Register 1
    cout << "RR1: ";
    for (int i = start_regone; i < start_regone + RR_ONE; i++) {
        cout << readReg_one_bits[idx_val] << " ";
        idx_val++;
    }
    cout << endl;
    idx_val = 0;

    // Parse Read Register 2
    cout << "RR2: ";
    for (int i = start_regtwo; i < start_regtwo + RR_TWO; i++) {
        cout << readReg_two_bits[idx_val] << " ";
        idx_val++;
    }
    cout << endl;
    idx_val = 0;

    cout << "Write Register: ";
    // Parse Write Register
    for (int i = start_wr; i < start_wr + RR_TWO; i++) {
        cout << writeReg_bits[idx_val] << " ";
        idx_val++;
    }
    cout << endl;
}
#endif