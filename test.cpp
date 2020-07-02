#include "Register.h"

int main(void) {
    string tmp = "00000011111010101010000000100000";
    Register reg_test(tmp);
    reg_test.printArray();
    return 0;
}