#include "elgam.h"
#include <iostream>
#include <random>

int main() {
    ulongT p = 30803;

    std::random_device dev;
    std::mt19937 sendG(dev());
    std::mt19937 recvG(dev());
    std::uniform_int_distribution<ulongT> distr(2, p - 2);

    std::function<ulongT()> recv = [&distr, &recvG]() -> ulongT {
        return distr(recvG);
    };

    std::function<ulongT()> send = [&distr, &sendG]() -> ulongT {
        return distr(sendG);
    };

    Participant r(p, 2, recv);
    Participant s(p, 2, send);

    s.exchangeMessage(r, 1234);

    std::cout << "Sender message = " << s.message() << std::endl;
    std::cout << "Reciver message = " << r.message() << std::endl;

}
