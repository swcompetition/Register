#include <iostream>
using namespace std;

#define MAX_BITS 32
#define OPCODE_BITS 6
#define RR_ONE 5
#define RR_TWO 5
#define WR_BITS 5
#define TEST_DEBUG
class Register {
private:
    // For now, let's say there is bit array for storing bits.
    bool full_reg_address[MAX_BITS] = {0};
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
    bool opcode_bits[OPCODE_BITS] = {0};
    bool readReg_one_bits[RR_ONE] = {0};
    bool readReg_two_bits[RR_TWO] = {0};
    bool writeReg_bits[WR_BITS] = {0};
#if defined(TEST_DEBUG)
    Register(string& tmp);
#endif
    Register();
    void init();

#if defined(TEST_DEBUG)
    void printArray() {
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
            cout << readReg_one_bits[idx_val] << " ";
            idx_val++;
        }
        cout << endl;
        idx_val = 0;

        // Parse Write Register
        for (int i = start_wr; i < start_wr + RR_TWO; i++) {
            cout << readReg_one_bits[idx_val] << " ";
            idx_val++;
        }
        cout << endl;
    }
#endif
};