#include "algs.h"
#include <functional>
#include <iostream>
#include <random>
#include <string>

using randProducer = std::function<ulongT()>;

class Participant {
  public:
    Participant(ulongT p, randProducer& rand)
        : p(p), rand(rand) {}

    void exchangeMessage(Participant& other, const std::string& message) {
        this->isReceiver = false;
        this->message = message;
        other.startRecvMessage(message.size());
        for (ulongT m: message) {
            this->updateKeys();
            other.updateKeys();

            ulongT temp = this->encode(m);
            temp = other.encode(temp);
            temp = this->decode(temp);
            other.decode(temp);
        }
    }

    void updateKeys() {
        do {
            this->key = rand();
            this->invKey = inverse(key, this->p - 1);
        } while ((this->key * this->invKey) % (this->p - 1) != 1);
    }

    void startRecvMessage(std::size_t messageSize) {
        this->message.resize(messageSize, '\0');
        this->isReceiver = true;
        this->recvInd = 0;
    }

    ulongT encode(ulongT m) {
        return powerDisc(m, this->key, this->p);
    }

    ulong decode(ulongT m) {
        ulongT res = powerDisc(m, this->invKey, this->p);
        if (this->isReceiver) { 
            message[this->recvInd] = static_cast<char>(res);
            ++this->recvInd;
        }
        return res;
    }

    const std::string& getMessage() { return this->message; }



  private:
    ulongT p;
    randProducer genProducer;
    randProducer rand;
    ulongT key;
    ulongT invKey;
    bool isReceiver;
    std::size_t recvInd;
    std::string message;
};
