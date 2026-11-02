#include "algs.h"
#include <utility>
#include <functional>

using randProducer = std::function<ulongT()>;

std::pair<ulongT, ulongT> getPair(ulongT p, ulongT q, randProducer& prod) {
    ulongT cand = prod();
    ulongT phi = (p - 1) * (q - 1);
    arrayT out = gcd(phi, cand); 
    while (out[0] != 1) {
        cand = prod();
        out = gcd(phi, cand);
    }
    return {cand, (out[2] + phi) % phi};
}

template<typename hashT = std::identity>
std::pair<ulongT, ulongT> sign(ulongT message, ulongT n, ulongT secret, hashT hash= {}) {
    return std::make_pair(message, powerDisc(hash(message), secret, n)); 
}

template<typename hashT = std::identity>
bool isValid(std::pair<ulongT, ulongT> signMessage, ulongT n, ulongT pub, hashT hash = {}) {
    return hash(signMessage.first) = powerDisc(signMessage.second, pub, n);
}
