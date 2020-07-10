#include <iostream>
#include <cmath>

#include "RMem.h"

using namespace std;

#define MAX_BITS 32
#define MAX_WRITE_REG 32
#define OPCODE_BITS 6
#define RR_ONE 5
#define RR_TWO 5
#define WR_BITS 5
#define TEST_DEBUG
class Register {
private:
    // For now, let's say there is bit array for storing bits.
    bool full_reg_address[MAX_BITS] = {0};

    // It is written in CPP, therefore we need to check RD value correctly based on binary value
    int rd_destination;
    RMem register_memory;
public:
    /**
     * Needs:
     * Control Signal Forwarding bits --> 6 Bits(OPCODE) --> 0 - 5
     * Read Register 1 --> 5 Bits --> 6 - 10
     * Read Register 2 --> 5 Bits --> 11 - 15
     * Write Register --> 5 Bits --> 16 - 20
     * Write Data --> Single Bits
     * Read Data 1(Actually forwarded from RR1)
     * Read Data 2(Actually Forwarded from RR2)
     */
    bool opcode_bits[OPCODE_BITS] = {0}; // OPCODE --> to Control
    bool readReg_one_bits[RR_ONE] = {0}; // RS --> to ALU First operand
    bool readReg_two_bits[RR_TWO] = {0}; // RT --> to ALU Second operand
    bool writeReg_bits[WR_BITS] = {0}; // RD

    bool rs_forward_bits[MAX_WRITE_REG] = {0};
    bool rt_forward_bits[MAX_WRITE_REG] = {0};

    bool* get_rs_forward();
    bool* get_rt_forward();

    void initRegister(const string& rs, const string& rt, const string& rd);
    Register();
    void forward();
    void setRDValue(int& value);
};