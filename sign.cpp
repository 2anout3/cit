#include <iostream>
#include "sign.h"

std::pair<ulongT, ulongT> factor(ulongT num) {
    for (ulongT p = 2; p < num; ++p) {
        if (num % p == 0) {
            return {p, num / p};
        }
    }
    return {0, 0};
}


int main() {
    ulongT n = 52891;
    std::pair<ulongT, ulongT> pq = factor(n);
    ulongT d = 3;
    ulongT c = inverse(d, (pq.first - 1) * (pq.second - 1));

    ulongT m = 500;
    std::pair<ulongT, ulongT> signM = sign(m, n, c);
    std::cout << "message = " << signM.first << "\tsign = " << signM.second << std::endl;
    std::cout << "isValid = " << isValid(signM, n, d) << std::endl;



}
