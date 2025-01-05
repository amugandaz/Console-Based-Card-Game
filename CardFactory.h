/*
 CSI2772A - Projet
 Classe CardFactory - Gestion de la création et du mélange de cartes
*/

#ifndef CARDFACTORY
#define CARDFACTORY
#include "Deck.h"       // Inclusion pour la classe Deck

// Classe `CardFactory` pour gérer la création et le mélange de cartes dans un Deck
class CardFactory
{
private:
    Deck* deck;     // Pointeur vers un Deck de cartes
    CardFactory();  // Constructeur privé par défaut (singleton)
    CardFactory(istream&);      // Constructeur privé avec flux d'entrée pour initialisation à partir d'un flux

protected:
    static int count;       // Compteur statique pour limiter le nombre d'instances

public:
    // Méthodes statiques pour obtenir une instance de `CardFactory`
    static CardFactory* getFactory(istream&);
    static CardFactory* getFactory();
    Deck getDeck();     // Retourne le Deck créé par cette `CardFactory`
};
// Initialisation du compteur statique
int CardFactory::count = 0;
// Constructeur par défaut de `CardFactory`
CardFactory::CardFactory()
{
    if (count > 1)
    {
        cout << "Trop d'usines" << endl;
    }
    else
    {
        srand(unsigned(time(0)));       // Initialise le générateur de nombres aléatoires pour le mélange

        deck = new Deck();      // Crée un nouveau Deck vide
        
        // Ajoute des cartes de différents types avec des quantités spécifiques
        for (int i(0); i < 20; i++)
            deck->push_back(new Blue());

        for (int i(0); i < 18; i++)
            deck->push_back(new Chili());

        for (int i(0); i < 16; i++)
            deck->push_back(new Stink());

        for (int i(0); i < 14; i++)
            deck->push_back(new Green());

        for (int i(0); i < 12; i++)
            deck->push_back(new Soy());

        for (int i(0); i < 10; i++)
            deck->push_back(new Black());

        for (int i(0); i < 8; i++)
            deck->push_back(new Red());

        for (int i(0); i < 6; i++)
            deck->push_back(new Garden());
        random_shuffle(deck->begin(), deck->end());     // Mélange aléatoire des cartes dans le Deck
        count++;
    }
}
// Constructeur de `CardFactory` avec flux d'entrée (placeholder pour une implémentation future)
CardFactory::CardFactory(istream& input)// Logique pour initialiser CardFactory à partir d'un flux
{
}

CardFactory* CardFactory::getFactory()
{
    CardFactory* factory = new CardFactory();
    return factory;
}

CardFactory* CardFactory::getFactory(istream& input)
{
    CardFactory* factory = new CardFactory(input);
    return factory;
}

Deck CardFactory::getDeck()
{
    return *deck;
}

#endif
