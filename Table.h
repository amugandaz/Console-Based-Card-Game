/*
 CSI2772A - Projet
 Classe Table - Gestion de l'Žtat global de la table de jeu
*/
#ifndef TABLE
#define TABLE

#include "Player.h"
#include "DiscardPile.h"
#include <sstream>

class Table
{
private:
public:
    Player* player1;

    Player* player2;

    Deck deck;

    DiscardPile discardPile;

    TradeArea tradeArea;
    Table();
    ~Table() {};

    Table(istream&, CardFactory*);
    bool win(string&);
    void printHand(bool);

    void print(ostream&) const;
    friend ostream& operator<<(ostream&, Table);
};
// Constructeur par dŽfaut
Table::Table()
{
}
// Constructeur ˆ partir d'un flux et d'une fabrique de cartes
Table::Table(istream& input, CardFactory* cardFactory)
{

    string line, token, temp;
    while (getline(input, line))
    {
        istringstream streamLine(line);

        while (streamLine >> token)
        {
            // processer le token
            if (token == "Player1")
            {
                player1 = new Player(input, cardFactory);
                break;
            }
            if (token == "Player2")
            {
                player2 = new Player(input, cardFactory);
                break;
            }
            if (token == "TradeArea")
            {
                streamLine >> temp;
                tradeArea = TradeArea(streamLine, cardFactory);
                break;
            }
            if (token == "DiscardPile")
            {
                streamLine >> temp;
                discardPile = DiscardPile(streamLine, cardFactory);
                break;
            }
            if (token == "Deck")
            {
                streamLine >> temp;
                deck = Deck(streamLine, cardFactory);
                break;
            }
            if (token == "end")
                break;
            cout << "Token invalide" << endl;
        }
        if (token == "end")
            break;
    }
}
// VŽrifie si un joueur a gagnŽ
bool Table::win(string& name)
{

    if (deck.empty())
    {
        if (player1->getNumCoins() == player2->getNumCoins())
            name = "Égalité";

        else if (player1->getNumCoins() > player2->getNumCoins())
            name = player1->getName();

        else
            name = player2->getName();
        return true;
    }

    return false;
}
// Affiche l'Žtat de la table
void Table::print(ostream& out) const
{
    out << "Joueur 1 " << endl
        << player1;
    out << "Main : ";
    player1->printHand(out, true);
    out << endl;
    out << "Joueur 2 " << endl;
    out << "Main : ";
    player2->printHand(out, true);
    out << endl;
    out << "TradeArea : " << tradeArea << endl;
    out << "DiscardPile : " << discardPile << endl;
    out << "Deck : " << deck << endl;
    out << "end";
}
// Surcharge de l'opŽrateur << pour afficher la table
ostream& operator<<(ostream& out, Table const table)
{
    out << "Joueur 1 " << *table.player1 << endl;
    out << "Joueur 2 " << *table.player2 << endl;
    out << "Aire de trading " << table.tradeArea << endl;
    out << "Pile de discarte " << table.discardPile << endl;

    return out;
}

#endif
