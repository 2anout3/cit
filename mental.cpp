#include "mental.h"
#include <iostream>
#include <random>


int main() {
    ulongT p = 30803;

    std::random_device dev;
    std::mt19937 aliceG(dev());
    std::mt19937 bobG(dev());
    std::uniform_int_distribution<ulongT> distr(2, p - 2);

    std::function<ulongT()> aliceR = [&distr, &aliceG]() -> ulongT {
        return distr(aliceG);
    };

    std::function<ulongT()> bobR = [&distr, &bobG]() -> ulongT {
        return distr(bobG);
    };

    Participant alice(p, aliceR);
    Participant bob(p, bobR);

    alice.deal(bob, std::vector<ulongT>{1, 2, 3});

    std::cout << "Alice card = " << alice.getCard() << std::endl;
    std::cout << "Bob card = " << bob.getCard() << std::endl;

}
