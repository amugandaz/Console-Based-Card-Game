/*
 CSI2772A - Projet
 Classe DiscardPile - Gestion de la pile de cartes défaussées
*/

#ifndef DISCARDPILE
#define DISCARDPILE

#include "CardFactory.h"        // Inclusion pour utiliser CardFactory

class DiscardPile : public vector<Card*>
{

public:
    /**
     * Constructeur par défaut
     */
    DiscardPile() {};
    /**
     * Destructeur par défaut
     */
    ~DiscardPile() {};
    /**
     * Constructeur pour initialiser une `DiscardPile` depuis un flux d'entrée
     *
     * @param input Flux d'entrée pour initialiser la pile
     * @param cardFactory Pointeur vers un `CardFactory` pour recréer les cartes
     */
    DiscardPile(istream&, CardFactory*);
    /**
     * Ajoute une carte au sommet de la pile
     *
     * @param card Carte à ajouter
     * @return Référence à la pile modifiée
     */
    DiscardPile& operator+=(Card*);
    /**
     * Retire et retourne la carte au sommet de la pile
     *
     * @return Pointeur vers la carte retirée
     */
    Card* pickUp();
    /**
     * Retourne la carte au sommet de la pile sans la retirer
     *
     * @return Pointeur vers la carte au sommet
     */
    Card* top();
    /**
     * Affiche le contenu de la pile dans un flux de sortie
     *
     * @param out Flux de sortie
     */
    void print(ostream&);
    /**
     * Surcharge de l'opérateur << pour afficher la pile
     *
     * @param out Flux de sortie
     * @param discardPile Pile à afficher
     * @return Flux de sortie avec les cartes de la pile
     */
    friend ostream& operator<<(ostream&, DiscardPile);
};
// Constructeur pour initialiser une `DiscardPile` à partir d'un flux et d'un `CardFactory`
DiscardPile::DiscardPile(istream& input, CardFactory* cardFactory)
{
}
// Opérateur += pour ajouter une carte à la pile
DiscardPile& DiscardPile::operator+=(Card* card)
{
    (this)->push_back(card);

    return *this;
}
// Retire et retourne la carte au sommet de la pile
Card* DiscardPile::pickUp()
{
    Card* firstCard = (Card*)this->at(0);
    this->erase(this->begin());
    return firstCard;
}
// Retourne la carte au sommet de la pile sans la retirer
Card* DiscardPile::top()
{
    Card* firstCard = (Card*)this->at(0);

    return firstCard;
}
// Affiche chaque carte dans la pile
void DiscardPile::print(ostream& out)
{
    for (vector<Card*>::const_iterator i = this->begin(); i != this->end(); i++)

        out << (**i) << " ";
}
// Surcharge de l'opérateur << pour afficher le contenu de la pile
ostream& operator<<(ostream& out, DiscardPile discardPile)
{
    discardPile.print(out);
    return out;
}
#endif
