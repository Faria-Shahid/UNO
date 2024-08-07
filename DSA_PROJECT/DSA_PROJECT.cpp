#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <random>
#include <chrono>
#include <iomanip>
#include "C:/Users/fariy/CLionProjects/untitled/DoublyCircularLinkedList.h"
#include "C:/Users/fariy/CLionProjects/untitled/DoublyLinkedList.h"
#include "C:/Users/fariy/CLionProjects/untitled/Stack.h"
//add path of the header files

using namespace std;

string colour[4] = {"Red", "Green", "Blue", "Yellow"};
string type[5] = {"Number", "Reverse", "Draw_two", "Draw_four", "Skip"};

class Card {
    int number;
    string type;
    string colour;
public:
    Card() : number(-1), type(" "), colour(" ") {
    }

    void setNumber(int num) {
        number = num;
    }

    void setType(string Type) {
        type = Type;
    }

    string getType() {
        return type;
    }

    void setColour(string Colour) {
        colour = Colour;
    }

    string getColour() {
        return colour;
    }

    int getNumber() {
        return number;
    }

    bool operator==(Card &other) {
        return (getType() == other.getType() &&
                getColour() == other.getColour() &&
                getNumber() == other.getNumber());
    }

    void printCards() const {
        cout << left << setw(20) << ("Type: " + type);
        cout << left << setw(20) << ("Colour: " + colour);
        cout << left << setw(20) << ("Number: " + to_string(number)) << endl;
    }
};

class Deck {
    Stack<Card> cards;

public:
    void generateDeck() {
        generateNumberCards();
        generateActionCards();
        generateWild();
    }

    void generateNumberCards() {
        Card card;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 9; ++j) {
                card.setColour(colour[i]);
                card.setNumber(j);
                card.setType(type[0]);
                cards.push(card);
            }
        }
    }

    void generateActionCards() {
        Card card;


        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 4; j++) {
                card.setType(type[i]);
                card.setColour(colour[j]);
                card.setNumber(-1);
                cards.push(card);
            }
        }
    }

    void generateWild() {
        Card card;
        for (int i = 0; i < 4; i++) {
            card.setType("Wild");
            card.setColour("Black");
            card.setNumber(-1);
            cards.push(card);
        }
    }

    void shuffle() {
        vector<Card> cardsVector;

        SLLNODE<Card> *current = cards.getHead();

        while (current != nullptr) {
            cardsVector.push_back(current->getData());
            SLLNODE<Card> *temp = current;
            current = current->getNext();
            delete temp;
        }

        cards.setHead(nullptr);

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(cardsVector.begin(), cardsVector.end(), std::default_random_engine(seed));

        for (size_t i = 0; i < cardsVector.size(); ++i) {
            cards.push(cardsVector[i]);
        }
    }


    Card removeCardFromDeck(Stack<Card> &DiscardPile) {

        if (cards.getHead() != nullptr) {
            return cards.pop();
        } else {
            refillDeck(DiscardPile);
            removeCardFromDeck(DiscardPile);
        }
    }


    void addCardInDeck(Card card) {
        cards.push(card);
    }

    SLLNODE<Card> *peekTopCard() {
        return cards.getHead();
    }

    int cardsInDeck() {
        return cards.getTotalNodes();
    }

    void shiftData(Stack<Card> &source) {
        while (source.getHead() && source.getHead()->getNext() != nullptr) {
            SLLNODE<Card> *removedNode = source.getHead()->getNext();
            source.getHead()->setNext(removedNode->getNext());

            if (cards.getHead() == nullptr) {
                cards.setHead(removedNode);
                removedNode->setNext(nullptr);
            } else {
                SLLNODE<Card> *current = cards.getHead();
                while (current->getNext()) {
                    current = current->getNext();
                }
                current->setNext(removedNode);
                removedNode->setNext(nullptr);
            }
        }
    }


    void refillDeck(Stack<Card> &DiscardPile) {
        shiftData(DiscardPile);
        shuffle();
    }

};

class Player {
    string playerType;
    DoublyLinkedList<Card> PlayerCards;

public:
    Player() : playerType(" ") {}

    string getPlayerType() const {
        return playerType;
    }

    void setPlayerType(string playerType) {
        Player::playerType = playerType;
    }

    void insertCardToPlayerHand(Card card) {
        PlayerCards.insert(card);
    }

    void removeCardFromPlayerHand(Card card) {
        DLLNode<Card> *current = PlayerCards.getHead();
        Card temp;

        while (current != NULL) {
            temp = current->getData();
            if (temp == card) {
                Card d = PlayerCards.removeFromList(current);
                break;
            }
            current = current->getNext();
        }
    }

    DLLNode<Card> *getPlayerCards() {
        return PlayerCards.getHead();
    }

    void displayPlayerCards() {
        DLLNode<Card> *temp = PlayerCards.getHead();
        Card card;
        int i = 1;

        while (temp != NULL) {
            card = temp->getData();
            cout << i << "-";
            card.printCards();
            temp = temp->getNext();
            i++;
        }
    }

    int cardsLeftInUserHand() {
        return PlayerCards.totalNodes();
    }

    Card searchByPosition(int pos) {
        DLLNode<Card> *current = PlayerCards.getHead();

        if (current != NULL) {
            if (pos <= cardsLeftInUserHand()) {
                int i = 1;
                while (i != pos) {
                    current = current->getNext();
                    i++;
                }
                return current->getData();
            } else {
                cout << "Invalid value entered." << endl;
            }
        }
        return Card();
    }

};


class UNO {
    DoublyCircularLinkedList<Player> players;
    Deck deck;
    Stack<Card> DiscardPile;


public:
    void skip(DLLNode<Player> *player) {
        Player player1 = player->getNext()->getData();
        Player player2 = player->getData();

        player->getNext()->setData(player2);
        player->setData(player1);
    }

    void reverse(DLLNode<Player> *player) {
        skip(player);
    }

    void drawTwo(DLLNode<Player> *currentPlayer) {
        if (deck.cardsInDeck() != -1) {
            DLLNode<Player> *nextPlayer = currentPlayer->getNext();

            for (int i = 0; i < 2; i++) {
                Card card = deck.removeCardFromDeck(DiscardPile);
                Player player = nextPlayer->getData();
                player.insertCardToPlayerHand(card);
                nextPlayer->setData(player);
            }
        } else {
            deck.refillDeck(DiscardPile);
            drawTwo(currentPlayer);
        }
    }


    void drawFour(DLLNode<Player> *player) {
        for (int i = 0; i < 2; ++i) {
            drawTwo(player);
        }
    }

    int *findNumberOfCardsOfEachColor(int size, Player player) {
        int *numberOfCards = new int[4]();
        for (int i = 0; i < size; i++) {
            DLLNode<Card> *current = player.getPlayerCards();
            while (current != NULL) {
                string color = current->getData().getColour();
                if (color == colour[i]) {
                    numberOfCards[i]++;
                }
                current = current->getNext();
            }
        }

        return numberOfCards;
    }

    int maxColorCard(int size, Player player) {
        int *numCards = findNumberOfCardsOfEachColor(size, player);
        int max = numCards[0];
        int maxIndex = 0;

        for (int i = 1; i < size; ++i) {
            if (numCards[i] > max) {
                maxIndex = i;
                max = numCards[i];
            }
        }

        delete[] numCards;

        return maxIndex;
    }

    void wild(Player player) {
        int choice;
        string color;

        if (player.getPlayerType() == "USER") {
            while (1) {
                cout << "Enter the serial number corresponding to the color you wish." << endl;
                cout << "1-Red 2-Blue 3-Green 4-Yellow" << endl;
                cin >> choice;

                if (cin.fail() || choice < 1 || choice > 9) {
                    cout << "Invalid value entered." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                } else {
                    switch (choice) {
                        case 1:
                            color = "Red";
                            break;
                        case 2:
                            color = "Blue";
                            break;
                        case 3:
                            color = "Green";
                            break;
                        case 4:
                            color = "Yellow";
                            break;
                        default:
                            cout << "Invalid number entered! Try again.";
                            continue;
                    }
                }
                break;
            }
        } else {
            int maxColor = maxColorCard(4, player);

            color = colour[maxColor];

            cout << "Color choosen by computer:" << color << endl;
        }


        Card temp = DiscardPile.getHead()->getData();
        temp.setColour(color);
        DiscardPile.getHead()->setData(temp);
    }


    void throwCard(Card card, DLLNode<Player> *currentPlayer, Player &player) {
        DiscardPile.push(card);
        Player player1 = currentPlayer->getData();
        player1.removeCardFromPlayerHand(card);
        currentPlayer->setData(player1);
        player = player1;
    }

    void generatePlayers() {
        Player userPlayer;
        userPlayer.setPlayerType("USER");
        players.insert(userPlayer);

        Player computerPlayer;
        computerPlayer.setPlayerType("COMPUTER");
        players.insert(computerPlayer);
    }

    void dealCards() {
        Player player;
        DLLNode<Player> *currentPlayer = players.getHead();

        do {
            player = currentPlayer->getData();

            for (int i = 0; i < 7; ++i) {
                player.insertCardToPlayerHand(deck.removeCardFromDeck(DiscardPile));
            }

            currentPlayer->setData(player);

            currentPlayer = currentPlayer->getNext();
        } while (currentPlayer != players.getHead());

    }

    bool isValid(Card card) {
        Card temp = DiscardPile.getHead()->getData();

        if (card.getNumber() == -1) {
            if (card.getType() == temp.getType() || card.getColour() == temp.getColour()) {
                return true;
            }
        } else {
            if (card.getNumber() == temp.getNumber() || card.getColour() == temp.getColour()) {
                return true;
            }
        }

        return false;
    }

    void actionCard(Card card, DLLNode<Player> *player) {
        if (card.getType() == "Skip") {
            cout << player->getNext()->getData().getPlayerType() << " Skipped." << endl;
            skip(player);
        } else if (card.getType() == "Reverse") {
            cout << "Player turns reversed." << endl;
            reverse(player);
        } else if (card.getType() == "Draw_two") {
            cout << "Two cards added to " << player->getNext()->getData().getPlayerType() << " hand." << endl;
            drawTwo(player);
        } else if (card.getType() == "Draw_four") {
            cout << "Four cards added to " << player->getNext()->getData().getPlayerType() << " hand." << endl;
            drawFour(player);
        }
    }

    bool searchForCardUsingType(string type, DLLNode<Player> *player) {
        DLLNode<Card> *current = player->getData().getPlayerCards();

        if (!current) {
            return false;
        }

        while (current != nullptr) {
            if (current->getData().getType() == type) {
                if (type == "Wild") {
                    return true;
                } else {
                    if (isValid(current->getData())) {
                        return true;
                    }
                }
            }
            current = current->getNext();

        }

        return false;
    }

    Card getCardUsingType(string type, DLLNode<Player> *player) {
        DLLNode<Card> *current = player->getData().getPlayerCards();

        while (current != NULL) {
            if (current->getData().getType() == type) {
                if (type == "Wild") {
                    return current->getData();
                } else {
                    if (isValid(current->getData())) {
                        return current->getData();
                    }
                }
            }
            current = current->getNext();
        }

        return Card();
    }

    Card getCardForComputer(DLLNode<Player> *computer, string *type, int size, Player &player) {
        Card card;
        int check = 0;

        for (int i = 0; i < size; i++) {
            if (searchForCardUsingType(type[i], computer)) {
                card = getCardUsingType(type[i], computer);
                break;
            } else {
                if (check == size - 1) {
                    card = deck.removeCardFromDeck(DiscardPile);
                    Player temp = computer->getData();
                    temp.insertCardToPlayerHand(card);
                    computer->setData(temp);
                    player = temp;
                    cout << computer->getData().getPlayerType() << " drew card from deck." << endl;
                    cout << endl;
                    if (!isValid(card)) {
                        return Card();
                    }
                }

                check++;
            }
        }
        return card;
    }

    Card computerTurn(DLLNode<Player> *computer, DLLNode<Player> *user, Player &player) {
        int playerCards = user->getData().cardsLeftInUserHand();
        Card card;

        if (playerCards <= 4) {
            string priority[6] = {"Draw_four","Skip","Wild","Draw_two","Reverse", "Number"};

            card = getCardForComputer(computer, priority, 6, player);
        } else if (playerCards > 6) {
            string priority[6] = {"Number", "Skip", "Reverse", "Draw_two", "Wild", "Draw_four"};

            card = getCardForComputer(computer, priority, 6, player);
        } else {
            string priority[6] = { "Skip","Number","Reverse", "Draw_two", "Wild", "Draw_four"};

            card = getCardForComputer(computer, priority, 6, player);

        }

        return card;
    }

    Card userTurn(Deck &deck, DLLNode<Player> *currentPlayer, Player &player) {
        Player temp = currentPlayer->getData();
        temp.displayPlayerCards();
        int choice;
        Card card;

        while (1) {
            cout << "Enter the serial number of the card you wish to throw." << endl;
            cout << "Press 0 to pick a card from the deck if you don't have a matching card in hand." << endl;
            cin >> choice;

            if (cin.fail() || choice < 0 || choice > temp.cardsLeftInUserHand()) {
                cout << "Invalid value entered." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else {
                switch (choice) {
                    case 0:
                        card = deck.removeCardFromDeck(DiscardPile);
                        temp.insertCardToPlayerHand(card);
                        currentPlayer->setData(temp);
                        player = temp;
                        if (!isValid(card)) {
                            return Card();
                        } else {
                            card = userTurn(deck, currentPlayer, player);
                        }
                        break;
                    default:
                        card = temp.searchByPosition(choice);
                        break;
                }

                break;
            }
        }

        return card;
    }

    void continuePrompt(){
        char choice;

        cout << endl << "Press any char key to continue or Press 'e' to exit game." << endl;
        cin >> choice;

        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            if (choice=='e'||choice=='E'){
                cout << endl;
                cout << "Exiting game!Goodbye:("<<endl;
                exit(0);
            }
        }
    }

    void intialiseGame() {
        generatePlayers();
        deck.generateDeck();
        deck.shuffle();
        dealCards();
    }

    Player startGame() {
        Card temp;
        Card c;
        Card card;
        bool firstRun = true;

        intialiseGame();

        DiscardPile.push(deck.removeCardFromDeck(DiscardPile));

        DLLNode<Player> *currentPlayer = players.getHead();

        while (1) {
            system("cls");
            cout<<"\t\t\t\t\t---WELCOME TO UNO CARD GAME!---"<<endl;
            cout<<"\t\t\t\t\t\tREADY,SET,UNO!"<<endl;
            cout<<endl;
            cout << "Discard Pile:" << endl;
            DiscardPile.getHead()->getData().printCards();
            cout << endl;

            if (firstRun) {
                if (DiscardPile.getHead()->getData().getNumber() == -1) {
                    c = DiscardPile.getHead()->getData();

                    if (c.getType() != "Reverse") {
                        if (c.getType() == "Wild") {
                            wild(currentPlayer->getData());
                        } else {
                            actionCard(c, currentPlayer->getNext());
                        }
                    }


                }
                firstRun = false;
            }

            Player player = currentPlayer->getData();

            if (player.getPlayerType() == "USER") {
                cout << player.getPlayerType() << " turn:" << endl;
                cout << "Total cards in hand:" << player.cardsLeftInUserHand() << endl;
                while (1) {
                    card = userTurn(deck, currentPlayer, player);

                    if (card == temp) {
                        cout << player.getPlayerType() << " drew card from deck." << endl;
                        break;
                    } else {
                        if (card.getType() == "Wild") {
                            throwCard(card, currentPlayer, player);
                            wild(player);
                            break;
                        } else {
                            if (isValid(card)) {
                                throwCard(card, currentPlayer, player);

                                if (card.getNumber() == -1) {
                                    actionCard(card, currentPlayer);
                                }

                                break;
                            } else {
                                cout << "Invalid card thrown! Try again.";
                                continue;
                            }
                        }


                    }
                }

                if (card == temp) {
                    cout << "User didn't have a valid card." << endl;
                } else {
                    cout << endl;
                    cout << "Card successfully added!" << endl;

                }

            } else {
                cout << player.getPlayerType() << " turn:" << endl;
                cout << "Total cards in hand:" << player.cardsLeftInUserHand() << endl;
                continuePrompt();
                card = computerTurn(currentPlayer, currentPlayer->getNext(), player);

                if (card == temp) {
                    cout << "Computer didn't have a valid card." << endl;
                } else {
                    throwCard(card, currentPlayer, player);
                    player = currentPlayer->getData();

                    if (card.getType() == "Wild") {
                        wild(player);
                    } else if (card.getNumber() == -1) {
                        actionCard(card, currentPlayer);
                    }

                    cout << endl;
                    cout << "After throwing card:" << endl;
                    cout << "Discard Pile:" << endl;
                    DiscardPile.getHead()->getData().printCards();
                    cout << endl;
                }
            }

            if (player.cardsLeftInUserHand() == -1) {
                return player;
            } else {
                if (player.getPlayerType() == "USER") {
                    player.displayPlayerCards();
                    cout << endl;
                }
                cout << "Total cards in hand:" << player.cardsLeftInUserHand() << endl;
                continuePrompt();
                system("cls");
            }

            currentPlayer = currentPlayer->getNext();
        }
    }

};


int main() {
    UNO uno;
    Player winner;
    winner = uno.startGame();
    cout << winner.getPlayerType() << " won:)";
}
