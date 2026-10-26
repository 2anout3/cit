#include "algs.h"
#include <functional>
#include <iostream>
#include <random>
#include <string>

using randProducer = std::function<ulongT()>;

class Participant {
  public:
    Participant(ulongT g, ulongT p, randProducer& rand)
        : g(g), p(p), power(rand()) {}
    void receive(ulongT pubKey) {
        this->commonKey = powerDisc(pubKey, this->power, this->p);
    }
    ulongT getKey() {
        return powerDisc(g, this->power, this->p);
    }
    ulongT getInverseKey() {
        return inverse(this->getKey(), this->p - 1);
    }

    void exchangeMessage(Participant& other, const std::string& message) {
        ulongT myKey = this->getKey();
        ulongT myInvKey = this->getInverseKey();

    }

    void startRecvMessage(std::size_t messageSize) {
        this->message.resize(messageSize, '\0');
    }

    void receiveMessage(ulongT message) {
        this->message = message;
    }

    void printInfo() {
        std::cout << "\tg = " << this->g << "\n\tp = " << this->p
                  << "\n\tpower = " << this->power
                  << "\n\tcommonKey = " << this->commonKey << std::endl;
    }

  private:
    ulongT g;
    ulongT p;
    ulongT power;
    ulongT commonKey;
    std::string message;
};
