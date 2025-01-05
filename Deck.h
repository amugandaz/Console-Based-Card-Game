/*
 CSI2772A - Projet
 Classe Deck - Gestion d'un paquet de cartes
*/

#ifndef DECK
#define DECK

#include "Card.h"           // Inclusion pour utiliser la classe Card
#include "CardFactory.h"    // Inclusion pour utiliser la classe CardFactory
#include <iostream>         // Inclusion pour les flux d'entrée/sortie
#include <vector>           // Inclusion pour la gestion des tableaux dynamiques

class CardFactory;
// Classe Deck dérivée de std::vector<Card*>
// Représente un paquet de cartes, chaque élément étant un pointeur vers un objet de type Card
class Deck : public vector<Card*>
{
public:
    /**
     * Constructeur par défaut
     */
    Deck() {};
    /**
     * Destructeur par défaut
     */
    ~Deck() {};
    /**
     * Constructeur pour initialiser un Deck à partir d'un flux d'entrée
     *
     * @param input Flux d'entrée à partir duquel initialiser le Deck
     * @param cardFactory Pointeur vers une CardFactory pour recréer les cartes
     */
    Deck(istream&, CardFactory*);
    /**
     * Tire la première carte du Deck
     *
     * @return Pointeur vers la première carte du Deck
     */
    Card* draw();
    /**
     * Surcharge de l'opérateur << pour afficher le contenu du Deck
     *
     * @param out Flux de sortie
     * @param deck Deck à afficher
     * @return Flux de sortie avec les cartes du Deck
     */
    friend ostream& operator<<(ostream&, Deck deck);
};
// Implémentation du constructeur pour initialiser un Deck à partir d'un flux d'entrée
Deck::Deck(istream& input, CardFactory* cardFactory)
{
}
// Implémentation de la fonction draw pour tirer une carte du Deck
Card* Deck::draw()
{
    Card* firstCard = (Card*)this->at(0);

    this->erase(this->begin());

    return firstCard;
}
// Implémentation de la surcharge de l'opérateur << pour afficher le contenu du Deck
ostream& operator<<(ostream& out, Deck deck)
{
    for (vector<Card*>::const_iterator i = deck.begin(); i != deck.end(); i++)
        out << (**i) << " ";
    return (out);
}
#endif
