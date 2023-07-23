#include <stdint.h>

uint64_t count_set_bits(uint64_t n) {
    n += 1;
    uint64_t power_of_2 = 2;
    uint64_t cnt = n / 2;

    while (power_of_2 <= n) {
        uint64_t total_pairs = n / power_of_2;
        cnt += (total_pairs / 2) * power_of_2;
        cnt += (total_pairs & 1) * (n % power_of_2);
        power_of_2 <<= 1;
    }

    return cnt;
}


uint64_t countOnes(uint64_t left, uint64_t right) {
    return count_set_bits(right) - count_set_bits(left - 1);
}
