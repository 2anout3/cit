#include <array>

using ulongT = unsigned long long;
using longT = long long;
using arrayT = std::array<longT, 3>;


ulongT powerDisc(ulongT a, ulongT x, ulongT p) {
    ulongT result = 1;
    ulongT power = a;
    while (x != 0) {
        if (x & 1) {
            result = (result * power) % p;
        }
        power = (power * power) % p;
        x >>= 1;
    }
    return result;
}

arrayT gcd(longT a, longT b) {
    bool wasSwapped = false;
    if (a < b) {
        std::swap(a, b);
        wasSwapped = true;
    }
    arrayT u = {a, 1, 0};
    arrayT v = {b, 0, 1};
    while (v[0] != 0) {
        longT q = u[0] / v[0];
        arrayT temp = {u[0] % v[0], u[1] - q * v[1], u[2] - q * v[2]};
        u = v;
        v = temp;
    }
    if (wasSwapped) {
        std::swap(u[1], u[2]);
    }
    return u;
}

longT inverse(longT a, longT p) {
    a = a % p;
    longT res = gcd(p, a)[2];
    return res > 0 ? res : (p + res) % p;
}
