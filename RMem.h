#pragma once

#include <iostream>
#include <cmath>
#define MAX_REGISTER_CTR 32
using namespace std;

class RMem {
private:
    int rmem_store[MAX_REGISTER_CTR] = {0};
public:
    int get_actual_dec(int& idx);
    bool* get_actual_bin(int& idx);
    void set_actual_dec(int& idx, int& value);
    void set_actual_bin(int& idx, bool* value, int& bitidx);
    int conv_bin_dec_idx(bool* bits, int& bitidx);
    int conv_bin_dec_idx(bool* bits, const int& bitidx);
};