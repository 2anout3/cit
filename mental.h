#include "algs.h"
#include <functional>
#include <vector>
#include <utility>


using randProducer = std::function<ulongT()>;



class Participant {
public:
    Participant(ulongT p, randProducer& rand): rand(rand), p(p) {}

    void deal(Participant& other, const std::vector<ulongT>& cards) {
        this->initPair();
        other.initPair();

        std::vector<ulongT> encoded = this->encodeCards(cards);
        this->shuffle(encoded);
        std::vector<ulongT> remain = other.choose(*this, encoded);
        ulongT otherCard = powerDisc(remain[this->rand() % remain.size()], this->d, this->p);
        other.setCard(otherCard); 
    }

    std::vector<ulongT> encodeCards(const std::vector<ulongT>& cards) {
        std::vector<ulongT> res;
        res.reserve(cards.size());
        for (auto card: cards) {
            res.push_back(powerDisc(((this->rand() % (this->p >> 2)) << 2) | card, this->c, this->p));
        }
        return res;
    }


    void shuffle(std::vector<ulongT>& cards) {
        ulongT limit = cards.size();
        for (std::size_t i = 0; i < cards.size() - 1; ++i) {
            ulongT toLast = rand() % limit;
            std::swap(cards[toLast], cards[--limit]);
        }
    }

    void setCard(ulongT card) {
        this->card = powerDisc(card, this->d, this->p) & 3ull;
    }
     
    std::vector<ulongT> choose(Participant& other, std::vector<ulongT>& cards) {
        std::vector<ulongT> res;
        res.reserve(cards.size() - 1);
        ulongT ind = this->rand() % cards.size();
        other.setCard(cards[ind]);
        for (ulongT i = 0; i < ind; ++i) {
            res.push_back(powerDisc(cards[i], this->c, this->p));
        }
        for (ulongT i = ind + 1; i < cards.size(); ++i) {
            res.push_back(powerDisc(cards[i], this->c, this->p));
        }
        this->shuffle(res);
        return res;
    }

    void initPair() {
        ulongT c = rand();
        while (gcd(static_cast<longT>(c), this->p - 1)[0] != 1) {
            c = rand();
        }
        ulongT d = static_cast<ulongT>(inverse(c, this->p - 1)); 
        this->c = c;
        this->d = d;
    }

    ulongT getCard() {
        return card;
    }


private:
    randProducer rand;
    ulongT p;
    ulongT card;
    ulongT c;
    ulongT d;
};
