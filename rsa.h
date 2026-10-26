#include "algs.h"
#include <functional>


class Participant {
public:
    Participant(longT p, longT q, longT d): p(p), q(q), d(d) {
        this->c = inverse(this->d, (this->p - 1) * (this->q - 1));
        this->n = this->p * this->q;
    }

    longT pubKey() {
        return this->d;
    }

    longT getN() {
        return this->n;
    }

    ulongT message() {
        return this->m;
    }

    void receiveMessage(longT codedMessage) {
        this->m = powerDisc(codedMessage, this->c, n);
    }

    void exchangeMessage(Participant& other, ulongT m) {
        this->m = m;
        other.receiveMessage(powerDisc(m, other.pubKey(), other.getN()));
    }


private:
    longT p;
    longT q;
    longT d;
    longT c;
    longT n;
    longT m;
};
