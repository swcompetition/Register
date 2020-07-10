#include "Register.h"

Register::Register() {
}

/**
 * Init Register
 * forwarded from i-mem
 */
void Register::initRegister(RMem& reg_mem, const string& rs, const string& rt, const string& rd) {
    register_memory = reg_mem;
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
 * Forward values to ALU
 * source to forward(addr): RS/RT --> readReg_one_bits, readReg_two_bits
 * Actual value will be forwarded in binary format.
 */
void Register::forward() {
    int rs_idx = register_memory.conv_bin_dec_idx(readReg_one_bits, RR_ONE);
    int rt_idx = register_memory.conv_bin_dec_idx(readReg_two_bits, RR_TWO);

    // Those boolean value is CREATED from R-Mem, statically
    register_memory.get_actual_bin(rs_idx, rs_forward_bits);
    register_memory.get_actual_bin(rt_idx, rt_forward_bits);
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

void Register::setRDValue(bool* bits) {
    int max = 32;
    register_memory.set_actual_bin(rd_destination, bits, max);
}

bool* Register::get_rs_forward() {
    return this->rs_forward_bits;
}

bool* Register::get_rt_forward() {
    return this->rt_forward_bits;
}

int Register::getRDValue() {
    return this->register_memory.get_value(rd_destination);
}