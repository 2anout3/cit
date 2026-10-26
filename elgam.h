#include "algs.h"
#include <functional>


using randProducer = std::function<ulongT()>;


class Participant {
public:
    Participant(ulongT p, ulongT g, randProducer& rand): rand(rand), p(p), g(g) {
        this->c = this->rand();
        this->d = powerDisc(g, this->c, this->p);
    }

    ulongT pubKey() {
        return this->d;
    }

    ulongT message() {
        return this->m;
    }

    void receiveMessage(ulongT r, ulongT e) {
        this->m = (e * powerDisc(r, this->p - 1 - this->c, this->p)) % this->p;
    }

    void exchangeMessage(Participant& other, ulongT m) {
        this->m = m;
        ulongT k = this->rand();
        ulongT r = powerDisc(this->g, k, this->p);
        ulongT e = (m * powerDisc(other.pubKey(), k, this->p)) % this->p;
        other.receiveMessage(r, e);
    }


private:
    randProducer rand;
    ulongT p;
    ulongT g;
    ulongT c;
    ulongT d;
    ulongT m;
};
