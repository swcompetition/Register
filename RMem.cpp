#include "RMem.h"

/**
 * return register-stored value in DECIMAL
 */
int RMem::get_actual_dec(int& idx) {
    return rmem_store[idx];
}

/**
 * return register-stored value in BINARY
 */
bool* RMem::get_actual_bin(int& idx) {
    bool tmp[MAX_REGISTER_CTR] = {0}; // Reverse-Order store value
    bool* tmp_dep; // actual order store value - will be returned
    int target_value = rmem_store[idx]; // Decimal value of register
    int tmp_idx = 0; // for converting decimal to binary
    int dep_idx; // for storing temp idx
    while (target_value != 0) {
        tmp[tmp_idx++] = target_value % 2;
        target_value /= 2;
    }

    dep_idx = tmp_idx;
    /* TODO: Make sure this bool is deleted after use. */
    tmp_dep = new bool[tmp_idx];
    for (int i = 0; i < tmp_idx; i++) {
        tmp_dep[i] = tmp[dep_idx-1];
        dep_idx--;
    }

    return tmp_dep;
}

/**
 * Set some binary-type value to RMem
 * idx: Regmem store index
 * value: bits
 * bitidx: bits idx(maximum length)
 */
void RMem::set_actual_bin(int& idx, bool* value, int& bitidx) {
    // need to convert bits to decimal
    int ret_val = 0;
    for (int i = 0; i < bitidx; i++) {
        ret_val += pow(2, (bitidx - 1) - i) * value[i];
    }
    rmem_store[idx] = ret_val;
}

/**
 * Set some decimal-type value to RMem
 */
void RMem::set_actual_dec(int& idx, int& value) {
    rmem_store[idx] = value;
}


/**
 * For converting some bits to idx value
 * binaries --> decimal
 */
int RMem::conv_bin_dec_idx(bool* bits, int& bitidx) {
    int ret_val = 0;

    for (int i = 0; i < bitidx; i++) {
        ret_val += pow(2, (bitidx - 1) - i) * bits[i];
    }
    return ret_val;
}