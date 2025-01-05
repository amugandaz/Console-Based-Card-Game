/*
 CSI2772A - Projet
 Classe Player - Gestion des joueurs, de leurs chaînes et de leurs cartes
*/

#ifndef PLAYER
#define PLAYER

#include "Hand.h"

class Player

{
private:
    string playerName;
    int playerCoins = 0;
    int maxChains = 2;

public:vector<Chain<Card*>*> chains;

      Chain<Card*>* chain1 = new Chain<Card*>;
      Chain<Card*>* chain2 = new Chain<Card*>;
      Chain<Card*>* chain3 = new Chain<Card*>; Hand* hand = new Hand(); Player()
      {
          chains.push_back(chain1);
          chains.push_back(chain2);
      }; Player(string&);
      Player(istream&, const CardFactory*); string getName() const; int getNumCoins() const; Player& operator+=(int); int getMaxNumChains() const;
      int getNumChains();
      void sellChain(Chain<Card*>);
      Chain<Card*>& operator[](int); void buyThirdChain();
      void printHand(ostream&, bool);
      void addChain(Card* card);
      friend ostream& operator<<(ostream&, Player);
      struct NotEnoughCoins : public exception  // Exception pour manque de pièces
      {
          const char* what() const throw()
          {
              return "Desole, vous avez pas assez de pieces";
          }
      };
};
// Constructeur avec nom
Player::Player(string& name)
{
    playerName = name;
    chains.push_back(chain1);
    chains.push_back(chain2);
}
// Constructeur avec flux et fabrique de cartes
Player::Player(istream& input, const CardFactory* cardFactory)
{
}
// Accède à une chaîne par index
Chain<Card*>& Player::operator[](int i)
{
    return *chains.at(i);
}
// Ajoute des pièces au joueur
Player& Player::operator+=(int i)
{
    playerCoins += i;

    return *this;
}
// Achète une troisième chaîne
void Player::buyThirdChain()
{
    if (getNumChains() < 3)
    {
        if (playerCoins < 3)
        {
            throw NotEnoughCoins();
        }
        else
        {
            playerCoins -= 3;
            chains.push_back(chain3);
            maxChains++;
        }
    }

    else
    {
        cout << " Vous avez deja 3 chaines, et vous navez pas dautorisation a en avoir plus." << endl;
    }
}
// Vend une chaîne et gagne des pièces
void Player::sellChain(Chain<Card*> chain)
{
    int coins = chain.sell();

    if (coins == 1)
    {
        chain.clear();
        playerCoins += 1;
        cout << " Vous avez accumule 1 piece " << endl;
    }
    else if (coins == 2)
    {
        chain.clear();
        playerCoins += 2;
        cout << " Vous avez accumule 2 pieces " << endl;
    }
    else if (coins == 3)
    {
        chain.clear();
        playerCoins += 3;
        cout << " Vous avez accumule 3 pieces " << endl;
    }
    else if (coins == 4)
    {
        chain.clear();
        playerCoins += 4;
        cout << " Vous avez accumule 4 pieces " << endl;
    }
    else
    {
        cout << coins << endl;
    }
}
// Affiche la main du joueur
void Player::printHand(ostream& out, bool choice)
{
    if (!choice)
        out << *hand->top();
    else
        out << *hand;
}
// Retourne le nom du joueur
string Player::getName() const { return playerName; }
// Retourne le nombre de pièces
int Player::getNumCoins() const { return playerCoins; }
// Retourne le nombre maximum de chaînes
int Player::getMaxNumChains() const { return maxChains; }
// Retourne le nombre de chaînes non vides
int Player::getNumChains()
{
    for (int j = 0; j < chains.size(); j++) {
        if (!(operator[](j).empty())) {
            j++;
        }


        return j;

    }

}
// Ajoute une carte dans une chaîne
void Player::addChain(Card* card)
{
    for (int i = 0; i < chains.size(); i++)
    {
        if ((operator[](i).empty()))
        {
            operator[](i).push_back(card);
            break;
        }

        else if (operator[](i).front()->getName() == card->getName())
        {
            operator[](i).push_back(card);
            break;
        }

        else
        {
        }
    }
}
// Surcharge de l'opérateur << pour afficher un joueur
ostream& operator<<(ostream& out, Player player)
{
    out << player.getName() << " " << player.getNumCoins() << " pieces " << endl;

    if (!(player.chains.empty()))
        for (int i = 0; i < player.getNumChains(); i++)
            out << player[i] << endl;

    else
        out << " Aucune Chaine ! ";

    return out;
}
#endif
