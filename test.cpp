#include "Register.h"

int main(void) {
    string tmp = "00000001010101001111100000100000";
    Register reg_test(tmp);
    reg_test.printArray();
    return 0;
}