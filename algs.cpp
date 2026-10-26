#include "algs.h"
#include <iostream>

std::ostream& operator<<(std::ostream& stream, const arrayT& arr) {
    stream << "gcd: " << arr[0] << "\t";
    stream << "x: " << arr[1] << "\t";
    stream << "y: " << arr[2];
    return stream;
}


int main() {
    std::cout << gcd(19, 11) << std::endl;
    std::cout << powerDisc(5, 100, 17) << std::endl;
    std::cout << inverse(17, 101) << " " << (17 * inverse(17, 101) % 101) << std::endl;

}
