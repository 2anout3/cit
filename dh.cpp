#include <random>
#include "dh.h"

int main() {
    ulongT p = 30803;
    ulongT g = 2;
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<ulongT> distr(1, p - 1);
    std::function<ulongT()> r = [&distr, &gen]() -> ulongT {
        return distr(gen);
    };
    Participant p1(g, p, r);
    Participant p2(g, p, r);

    ulongT a = p1.getKey();
    p2.receive(a);
    ulongT b = p2.getKey();
    p1.receive(b);

    std::cout << "p1\n";
    p1.printInfo();
    std::cout << "p2\n";
    p2.printInfo();

}
