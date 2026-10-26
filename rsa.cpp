#include "rsa.h"
#include <iostream>
#include <random>

int main() {
    Participant a(131, 227, 3);
    Participant b(113, 281, 3);

    a.exchangeMessage(b, 1234);

    std::cout << "Sender message = " << a.message() << std::endl;
    std::cout << "Reciver message = " << b.message() << std::endl;

}
