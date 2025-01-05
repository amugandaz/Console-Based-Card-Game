/*
 CSI2772A - Projet
 Classe Chain - Gestion des cha”nes de cartes
*/

#ifndef CHAINE
#define CHAINE

#include "CardFactory.h"

class Chain_Base
{
public:
    // constructeurs ************************************************

    // constructeur par defaut
    Chain_Base() {};

    // destructeur par defaut
    ~Chain_Base() {};

    // compte le nbr de cartes dans la chaine

    virtual int sell() = 0;
};

template <class T>
class Chain : public Chain_Base, public vector<Card*>
{
private:
public:
    // constructeurs et destructeurs ************************************************

    /**
     * constructeur par defaut
     */

    Chain() {};

    /**
     * constructeur a partir d'un input stream
     *
     * @param input input stream
     * @param const cardFactory
     */

    Chain(istream&, const CardFactory*);

    /**
     * destructeur par defaut
     */

    ~Chain() {};

    // methodes de la classe ************************************************

    /**
     * compte le nombre de carts dans la chaine et retourne le nombre de pieces
     * en se fiant a la fonction Card::getCardsPerCoin
     *
     * @return le nbr de pieces
     */

    int sell()
    {
        // le type de la chaine
        Card* card = (Card*)this->at(0);

        // usilise le tableau pour determiner le nbr de coins
        if (this->size() == card->getCardsPerCoin(1))
        {
            return 1;
        }
        else if (this->size() == card->getCardsPerCoin(2))
        {
            return 2;
        }
        else if (this->size() == card->getCardsPerCoin(3))
        {
            return 3;
        }
        else if (this->size() == card->getCardsPerCoin(4))
        {
            return 4;
        }
        else
        {
            cout << "Pas de pieces pour cette chaine. Essayez dajouter des haricots!" << endl;
            return 0;
        }
        return 0;
    }

    /**
     * Ajouter une carte a la chaine
     *
     * @param card la carte a ajouter
     * @return la nouvelle chaine modifiee
     */

    Chain<T>& operator+=(Card* card)
    {

        if (!(this->empty()))
        {

            if (this->front()->getName() != card->getName())
            {
                throw Card::illegalType();

                return *this;
            }

            else
            {
                this->push_back(card);
                return *this;
            }
        }

        else
        {
            this->push_back(card);
            return *this;
        }

    }


    friend ostream& operator<<(ostream& out, Chain const& chain)
    {

        if (!(chain.empty()))
        {
            out << chain.front()->getName() << "  ";
            for (auto i = chain.cbegin(); i != chain.cend(); i++)
            {
                out << (**i) << " ";
            }
        }
        else
        {
            out << "Pas de carte dans la chaîne";
        }

        return out;
    }
};
#endif
