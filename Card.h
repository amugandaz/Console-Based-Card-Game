/*
 CSI2772A - Projet
 Définition des classes de cartes
*/

#ifndef CARD
#define CARD

#include <iostream>     // Pour les flux d'entrée/sortie
#include <string>       // Pour utiliser std::string
#include <fstream>      // Pour les opérations sur fichiers
#include <algorithm>    // Pour les algorithmes (ex : random_shuffle)
#include <ctime>        // Pour srand (initialisation aléatoire)
#include <cstdlib>      // Pour rand et srand
#include <exception>    // Pour la gestion des exceptions

using namespace std;
// Classe de base `Card` pour représenter une carte générique
class Card
{
private:
    int number;     // Numéro unique pour identifier la carte (éventuel usage futur)

public:
    Card() {};      // Constructeur par défaut
    ~Card() {};     // Destructeur par défaut
    // Méthodes virtuelles pures à surcharger par les classes dérivées
    virtual int getCardsPerCoin(int coins) = 0;     // Cartes nécessaires par pièce
    virtual string getName() const = 0;             // Nom de la carte
    virtual void print(ostream& out) const = 0;     // Affiche la carte
    friend ostream& operator<<(ostream& out, Card const& card)      // Surcharge de l'opérateur << pour afficher une carte
    {
        card.print(out);
        return out;
    }
    // Exception en cas de types incompatibles
    struct illegalType : public exception
    {
        const char* what() const throw()
        {
            return "Pas le meme type dharicot  ";
        }
    };
};

/**
 * Les classes derivees de Card
 */
class Blue : public Card
{
public:
    int getCardsPerCoin(int coins) override
    {
        switch (coins)
        {
        case 1:
            return 4;
        case 2:
            return 6;
        case 3:
            return 8;
        case 4:
            return 10;
        default:
            cout << " Pas disponible " << endl;
            return 0;
        }
    }

    string getName() const override { return "Blue"; }
    void print(ostream& out) const override { out << "B"; }
};
class Chili : public Card
{
public:
    int getCardsPerCoin(int coins) override
    {
        switch (coins) {
        case 1:
            return 3;
        case 2:
            return 6;
        case 3:
            return 8;
        case 4:
            return 9;
        default:
            cout << " Pas disponible " << endl;
            return 0;
        }
    }
    string getName() const override { return "Chili"; }
    void print(ostream& out) const override { out << "C"; }
};
class Stink : public Card
{
public:
    int getCardsPerCoin(int coins) override
    {
        switch (coins)
        {
            // utilisation du tableau pour determiner le nb de cartes possibles
        case 1:
            return 3;
        case 2:
            return 5;
        case 3:
            return 7;
        case 4:
            return 8;
        default:
            cout << " Indisponible " << endl;
            return 0;
        }
    }
    string getName() const override { return "Stink"; }
    void print(ostream& out) const override { out << "S"; }
};
class Green : public Card
{
public:
    int getCardsPerCoin(int coins) override
    {
        switch (coins)
        {
        case 1:
            return 3;
        case 2:
            return 5;
        case 3:
            return 6;
        case 4:
            return 7;
        default:
            cout << " Pas disponible " << endl;
            return 0;
        }
    }
    string getName() const override { return "Green"; }
    void print(ostream& out) const override { out << "G"; }
};
class Soy : public Card
{
public:
    int getCardsPerCoin(int coins) override
    {
        switch (coins)
        {
        case 1:
            return 2;
        case 2:
            return 4;
        case 3:
            return 6;
        case 4:
            return 7;
        default:
            cout << " Pas disponible " << endl;
            return 0;
        }
    }
    string getName() const override { return "Soy"; }
    void print(ostream& out) const override { out << "s"; }
};
class Black : public Card
{
public:
    int getCardsPerCoin(int coins) override
    {
        switch (coins)
        {
        case 1:
            return 2;
        case 2:
            return 4;
        case 3:
            return 5;
        case 4:
            return 6;
        default:
            cout << " Pas disponible " << endl;
            return 0;
        }
    }
    string getName() const override { return "Black"; }
    void print(ostream& out) const override { out << "b"; }
};
class Red : public Card
{
public:
    int getCardsPerCoin(int coins) override
    {
        switch (coins)
        {
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 4;
        case 4:
            return 5;
        default:
            cout << " Pas disponible " << endl;
            return 0;
        }
    }
    // Nom de la carte
    string getName() const override { return "Red"; }

    // Afficher la lettre du type de carte
    void print(ostream& out) const override { out << "R"; }
};
class Garden : public Card
{
public:
    Garden() {}

    int getCardsPerCoin(int coins) override
    {
        switch (coins)
        {
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            cout << " Pas disponible " << endl;
            return 0;
        }
    }
    string getName() const override { return "Garden"; }
    void print(ostream& out) const override { out << "G"; }
    ~Garden() {};
};
#endif
