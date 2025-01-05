/*
 CSI2772A - Projet
 Classe Hand - Gestion des cartes dans la main d'un joueur
*/

#ifndef HAND
#define HAND
#include "TradeArea.h"

// Classe représentant la main d'un joueur, héritant de std::vector
class Hand : public vector<Card*>
{
public:
    Hand() {};
    ~Hand() {};
    Hand(istream&, const CardFactory*);
    Hand& operator+=(Card*);
    Card* play();
    Card* top() const;
    Card* operator[](int);
    friend ostream& operator<<(ostream&, const Hand);
};
// Constructeur à partir d'un flux et d'une fabrique de cartes
Hand::Hand(istream& input, const CardFactory* cardFactory)
{
}
// Ajoute une carte à la main
Hand& Hand::operator+=(Card* card)
{
    (this)->push_back(card);

    return *this;
}
// Joue la première carte de la main et la retire
Card* Hand::play()
{
    Card* firstCard = (Card*)this->at(0);

    this->erase(this->begin());

    return firstCard;
}
// Retourne la première carte de la main sans la retirer
Card* Hand::top() const
{
    Card* firstCard = (Card*)this->at(0);

    return firstCard;
}
// Accède à une carte par index et la retire de la main
Card* Hand::operator[](int i)
{
    Card* cardPtr = nullptr;
    if (i >= this->size() || i < 0)
        cout << "Index est trop loin!" << endl;
    else
    {
        cardPtr = this->at(i);
        this->erase(this->begin() + i);
    }

    return cardPtr;
}
// Surcharge de l'opérateur << pour afficher la main
ostream& operator<<(ostream& out, const Hand hand)
{
    for (auto i = hand.cbegin(); i != hand.cend(); i++)

        out << (**i) << " ";
    return out;
}
#endif
