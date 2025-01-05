/*
 CSI2772A - Projet
 Classe TradeArea - Gestion de la zone d'échange de cartes
*/
#ifndef TRADEAREA
#define TRADEAREA

#include <list>             // Pour utiliser la liste doublement chaînée
#include <typeinfo>         // Pour le support RTTI (Type Identification)
#include "Chain.h"          // Inclusion de Chain pour la compatibilité
#include "CardFactory.h"    // Inclusion de CardFactory pour la création des cartes

class TradeArea : public list<Card*>
{
private:
public:
    /**
     * Constructeur par défaut
     */
    TradeArea() {};
    /**
     * Destructeur par défaut
     */
    ~TradeArea() {};
    /**
     * Constructeur pour initialiser TradeArea à partir d'un flux d'entrée
     *
     * @param input Flux d'entrée
     * @param cardFactory Pointeur constant vers une CardFactory pour recréer les cartes
     */
    TradeArea(istream&, const CardFactory*);
    /**
     * Ajoute une carte à la TradeArea
     *
     * @param card Pointeur vers la carte à ajouter
     * @return Référence à la TradeArea modifiée
     */
    TradeArea& operator+=(Card*);
    /**
     * Vérifie si une carte est légale pour être ajoutée
     *
     * @param card Pointeur vers la carte à vérifier
     * @return true si la carte est légale, sinon false
     */
    bool legal(Card*);
    /**
     * Échange et retire une carte de la TradeArea par son nom
     *
     * @param name Nom de la carte à échanger
     * @return Pointeur vers la carte échangée ou nullptr si non trouvée
     */
    Card* trade(string);
    /**
     * Retourne le nombre de cartes dans la TradeArea
     *
     * @return Nombre total de cartes dans TradeArea
     */
    int numCards();
    /**
     * Surcharge de l'opérateur << pour afficher la TradeArea
     *
     * @param out Flux de sortie
     * @param tradeArea TradeArea à afficher
     * @return Flux de sortie modifié
     */
    friend ostream& operator<<(ostream&, const TradeArea);
};
// Implémentation du constructeur TradeArea à partir d'un flux d'entrée
TradeArea::TradeArea(istream& input, const CardFactory* cardFactory)
{
}
// Ajoute une carte à la TradeArea
TradeArea& TradeArea::operator+=(Card* card)
{
    if (this->legal(card))
    {
        this->push_back(card);
        return *this;
    }

    else
        return *this;
}
// Vérifie si une carte est légale pour être ajoutée
bool TradeArea::legal(Card* card)
{
    if (this->empty())
        return true;

    for (auto i : *this)
    {
        if (i->getName() == card->getName())
            return true;
    }

    return false;
}
// Échange et retire une carte de TradeArea par son nom
Card* TradeArea::trade(string name)
{
    Card* eraseCard = (Card*)this->front();

    for (auto i : *this)
    {

        if (i->getName() == name)
            this->erase(this->begin());
        return eraseCard;
    }

    return NULL;
}
// Retourne le nombre de cartes dans TradeArea
int TradeArea::numCards()
{

    return this->size();
}

ostream& operator<<(ostream& out, const TradeArea tradeArea)
{

    for (auto i = tradeArea.cbegin(); i != tradeArea.cend(); i++)

        out << (**i) << " ";
    return out;
}

#endif
