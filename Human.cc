#include <algorithm>
#include <iostream>
#include <string>

#include "Human.h"

Human::Human() : Player() {}

Human::~Human() {}

const Command
Human::play(const std::vector< std::vector <Card*> >& gameTable)
{
    print(gameTable);
    std::vector <Card*> legalPlays = constructLegalPlays(gameTable);
    bool legal = false;
    Command c;
    while(!legal)
    {
        std::cin >> c;
        if (c.type == Command::Type::PLAY)
        {
            if(findCard(legalPlays, c.card) != -1)
            {
                legal = true;
                playCard(c.card);
            }
            else
                std::cout << "This is not a legal play." << std::endl;
        }
        else if (c.type == Command::Type::DISCARD)
        {
            if(legalPlays.empty())
            {
                legal = true;
                discard(c.card);
            }
            else
                std::cout << "You have a legal play. You may not discard." << std::endl;
        }
        if (c.type == Command::Type::QUIT || c.type == Command::Type::RAGEQUIT)
            legal = true;
    }
    return c;
}

void
Human::print(const std::vector< std::vector<Card*> >& gameTable) const
{
  const std::string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
  std::cout << "Cards on the table:" << std::endl;
  for(int i = 0; i < 4; ++i)
  {
      std::cout << suits[i] << ":";
      printTableList(gameTable[i]);
  }
  std::cout << "Your hand:";
  printCardList(myHand);
  std::cout << "Legal plays:";
  std::vector<Card*> legalPlays = constructLegalPlays(gameTable);
  printCardList(legalPlays);
  std::cout << "> ";
}

void
Human::discard(const Card& card)
{
  int index = findCard(myHand, card);
  myDiscardedPile.push_back(myHand[index]);
  incrementScore(card.rank().rank()+1);
  myHand.erase(myHand.begin() + index);
}

void
Human::printTableList(const std::vector<Card*>& list) const
{
    for (const Card *c: list)
        std::cout <<" " << c->rank().rank()+1;
    
    std::cout << std::endl;
}

void
Human::printCardList(const std::vector<Card*>& list) const
{
    for(const Card *c: list)
        std::cout << " " << *c;

    std::cout << std::endl;
}
