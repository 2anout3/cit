#include "shamir.h"
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

    Participant sender(p, send);
    Participant reciver(p, recv);

    sender.exchangeMessage(reciver, "random message");
    std::cout << "send message = " << sender.getMessage() << std::endl;
    std::cout << "recv message = " << reciver.getMessage() << std::endl;

}
