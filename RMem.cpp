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
void RMem::get_actual_bin(int& idx, bool return_value[]) {
    for (int i = 0; i < MAX_REGISTER_CTR; i++) {
        return_value[i] = 0;
    }
    int target_value = rmem_store[idx]; // Decimal value of register

    string tmp_str = "";
    while (target_value != 0) {
        tmp_str += (target_value % 2) + '0';
        target_value /= 2;
    }
    int str_iter = tmp_str.length() - 1;
    for (int i = 0; i < MAX_REGISTER_CTR; i++) {
        if (i < MAX_REGISTER_CTR - tmp_str.length()) {
            return_value[i] = 0;
        } else {
            return_value[i] = tmp_str.at(str_iter--) - '0';
        }
    }
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

void RMem::set_actual_dec(int& idx, const int& value) {
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

int RMem::conv_bin_dec_idx(bool* bits, const int& bitidx) {
    int ret_val = 0;

    for (int i = 0; i < bitidx; i++) {
        ret_val += pow(2, (bitidx - 1) - i) * bits[i];
    }
    return ret_val;
}

int RMem::get_value(int& idx) {
    return this->rmem_store[idx];
}
int RMem::get_value(const int& idx) {
    return this->rmem_store[idx];
}