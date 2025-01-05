#include <iostream>
#include "Card.h"
#include "Chain.h"
#include "CardFactory.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "Hand.h"
#include "Player.h"
#include "Table.h"
#include "TradeArea.h"

const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int WHITE = 15;

int menu()
{
    int choix;

    cout << " -Menu- " << endl;
    cout << "1) Acheter une nouvelle chaine ( 3 pièces ) " << endl;
    cout << "2) Montrer la table de jeu " << endl;
    cout << "3) Vendre une chaine " << endl;
    cout << "4) Passer la chaine" << endl;
    cout << "5) Sauvegarder le jeu " << endl;
    cout << "6) Quitter le jeu " << endl;

    cin >> choix;

    if (choix == 1)
        return 1;
    if (choix == 2)
        return 2;
    if (choix == 3)
        return 3;
    if (choix == 4)
        return 4;
    if (choix == 5)
        return 5;
    if (choix == 6)
        return 6;
    return choix;
}

void saveGame(const Table& table)
{

    string save = "jeu.txt";
    ofstream out(save);
    table.print(out);
    out.close();
}

Table* loadGame(CardFactory* CardFactory)
{
    string save;
    cout << "Nom du fichier : ";
    cin >> save;
    // ouvrir fichier
    ifstream input(save);

    // lire fichier dans table
    return new Table(input, CardFactory);
}

int main()
{
    string name1, name2;
    string winner, answer;

    int game, houl, choice, round(0);

    Card* topCard;
    Table* table;

    CardFactory cardFactory = *CardFactory::getFactory();
    vector<Player*> players;
    cout << " Nouvelle partie (1) ou partie existante (2) ? " << endl;
    cin >> game;

    if (game == 1)
    {
        cout << " Nom du 1er joueur : " << endl;
        cin >> name1;
        cout << " Nom du 2eme joueur : " << endl;
        cin >> name2;

        Player* a = new Player(name1);
        Player* b = new Player(name2);

        table = new Table();

        // initialiser la nouvelle partie

        table->deck = CardFactory::getFactory()->getDeck();

        table->player1 = a;
        table->player2 = b;

        for (int i = 0; i < 4; ++i)
        {
            table->player1->hand->operator+=(table->deck.draw());
            table->player2->hand->operator+=(table->deck.draw());
        }

        players.push_back(table->player1);
        players.push_back(table->player2);
    }

    else

    {
        table = loadGame(cardFactory.getFactory());
    }

    cout << "Maitre du jeu : Melange des cartes..." << endl
        << endl;

    while (!table->win(winner))
    {

        while (!(table->deck.empty()))
        {

            round++;

            cout << "---- Tour " << round << "---" << endl;
            for (auto const& player : players)
            {

                cout << "Maitre du jeu : Voici la table :" << endl
                    << endl;
                cout << "###TABLE DU JEU ####" << endl;
                cout << *table;
                cout << "####" << endl;
                cout << endl;
                cout << "Maitre du jeu : Pige une carte....." << endl;
                Card* drawCard = table->deck.draw();
                cout << "[Vous avez pigé " + drawCard->getName() + "]" << endl;
                player->hand->operator+=(drawCard);

                player->printHand(cout, true);
                if (table->tradeArea.numCards() != 0)
                {
                    for (auto j : table->tradeArea)
                    {
                        cout << endl;
                        cout << "Maitre du jeu : Voulez vous ajouter " << *j << " a une chaine ? (Oui/Non)" << endl;
                        cout << player->getName() << " : ";
                        cin >> answer;

                        Card* cardInTrade = table->tradeArea.trade(j->getName());
                        if (cardInTrade != nullptr)
                        {
                            if (answer == "Oui" || answer == "oui" || answer == "o" || answer == "O")
                            {
                                player->addChain(cardInTrade);
                            }
                            else
                            {
                                table->discardPile += cardInTrade;
                            }
                        }
                    }
                }

                cout << endl;
                cout << "Carte du haut : ";
                player->printHand(cout, false);
                cout << endl;
                topCard = player->hand->play();

                player->addChain(topCard);

                cout << "Carte du haut : ";
                player->printHand(cout, false);
                cout << endl;

                cout << "Maitre du jeu : Voulez-vous ajouter la carte du haut a une chaine ? (Oui/Non)" << endl;
                cout << player->getName() << " : ";
                cin >> answer;

                if (answer == "Oui" || answer == "oui" || answer == "o" || answer == "O")
                {
                    topCard = player->hand->play();
                    player->addChain(topCard);
                }

                cout << "Maitre du jeu : Voulez-vous enlever une carte de votre main ? (Oui/Non)" << endl;
                cout << player->getName() << " : ";
                cin >> answer;

                if (answer == "Oui" || answer == "oui" || answer == "o" || answer == "O")
                {
                    player->printHand(cout, true);
                    cout << endl;
                    cout << "Maitre du jeu : Quelle carte voulez vous enlever ? (1,2...)" << endl;

                    for (;;)
                    {
                        cout << player->getName() << " : ";
                        cin >> choice;
                        Card* discardCard = player->hand->operator[](choice - 1);

                        if (discardCard != nullptr)
                        {
                            table->discardPile += discardCard;
                            cout << player->getName() << " main : ";
                            player->printHand(cout, true);
                            cout << endl;
                            break;
                        }
                    }
                }
                houl = menu();

                switch (houl)
                {
                case 1:
                    player->buyThirdChain();
                    break;
                case 2:
                    cout << "###TABLE DU JEU ###" << endl;
                    cout << *table << endl;
                    cout << "####" << endl;
                    break;
                case 3:
                    
                    cout << *table->player1 << endl; // Affiche les détails du joueur vv

                    // Affichage des chaînes disponibles à la vente pour le joueur vv
                    cout << "Chaînes disponibles à la vente pour " << table->player1->getName() << ":" << endl;
                    for (int i = 0; i < table->player1->getNumChains(); ++i) {
                        cout << i + 1 << ") " << *(table->player1->chains[i]) << endl;
                    }

                    // Demande au joueur vv quelle chaîne il souhaite vendre
                    
                    cout << " Quelle chaine voulez-vous vendre (1, 2... ) ?" << endl;
                    cout << *player << endl;
                    int i;
                    cin >> i;

                    player->sellChain(player->operator[](i - 1));
                    player->operator[](i - 1).clear();
                    
                case 5:
                    saveGame(*table);
                    cout << " Partie sauvergardee. Au revoir" << endl;
                    exit(0);
                    break;
                case 6:
                    cout << "Au revoir" << endl;
                    exit(0);
                default:
                    break;
                }
                for (int i = 0; i < 3; ++i)
                {
                    table->tradeArea += (table->deck.draw());
                }

                if (table->discardPile.size() != 0)
                {
                    while (table->discardPile.top() != nullptr && table->tradeArea.legal(table->discardPile.top()))
                    {
                        table->tradeArea += (table->discardPile.pickUp());
                    }
                }

                cout << endl;
                cout << " Aire de Trading : ";
                cout << table->tradeArea << endl;

                if (table->tradeArea.numCards() != 0)
                {
                    for (auto j : table->tradeArea)
                    {
                        cout << "Maitre du jeu : Voulez-vous ajouter " << *j << " a une chaine ? (Oui/Non) " << endl;
                        cout << player->getName() << " : ";
                        cin >> answer;

                        if (answer == "Oui" || answer == "oui" || answer == "o" || answer == "O")
                        {
                            Card* cardInTrade = table->tradeArea.trade(j->getName());

                            if (cardInTrade != nullptr)
                            {
                                player->addChain(cardInTrade);
                                cardInTrade = table->tradeArea.trade(j->getName());
                            }
                        }
                    }
                }

                player->hand->operator+=(table->deck.draw());
                player->hand->operator+=(table->deck.draw());
            }
        }
    }

    cout << " Vous avez gagne " << winner << "!" << endl;
    cout << "###FIN Du JEU ####" << endl;

    return 0;
}
