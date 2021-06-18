#include <iostream>

#include "../headers/Hero.h"
#include "../headers/IObject.h"
#include "../headers/Log.h"

using namespace std;

namespace HE_Arc::RPG {
Hero::Hero(int strength, int agility, int intelligence, double hp, string name,
           IObject *pObject)
    : strength(strength), agility(agility), intelligence(intelligence), hp(hp),
      name(name), pObject(pObject), backpack(new Backpack()) {}

Hero::~Hero() {
  delete this->pObject;
  delete this->backpack;
}

Hero::Hero(const Hero &hero)
    : strength(hero.strength), agility(hero.agility),
      intelligence(hero.intelligence), hp(hero.hp), name(hero.name),
      pObject(hero.pObject), backpack(new Backpack()) {}

Hero &Hero::operator=(const Hero &hero) {
  this->agility = hero.agility;
  this->strength = hero.strength;
  this->hp = hero.hp;
  this->intelligence = hero.intelligence;
  this->name = hero.name;
  this->pObject = hero.pObject;

  return *this;
}

/**
 * Interact with an other Hero
 */
void Hero::interact(const Hero &otherHero) {
  cout << "Hero " << this->getName() << " interact with the Hero named "
       << otherHero.getName();
}

/**
 * A hero can exchange (sell) their backpack items with money
 */
void Hero::sell(IObject *pObject, Hero *hero) {
  bool exists = !this->getBackpack()->exists(pObject);
  if (exists) {
    throw runtime_error("You do not possess this item");
  }

  float price = pObject->getPrice();

  if (hero->money < price) {
    throw runtime_error("You don't have enough money to buy this item");
  }

  this->money += price;
  hero->money -= price;

  hero->getBackpack()->add(pObject);
  this->getBackpack()->remove(pObject);

  // Log the transaction in transactions.log
  Log::writeTransaction(this, hero, pObject, price);
}

ostream &operator<<(ostream &s, const Hero &hero) {
  s << "=================" << endl;
  s << hero.getType() << ": " << hero.getName() << endl;
  s << "=================" << endl;
  s << "Strength: " << hero.getStrength() << endl;
  s << "Agility: " << hero.getAgility() << endl;
  s << "Intelligence: " << hero.getIntelligence() << endl;
  s << "Money: " << hero.getMoney() << endl;
  s << "HP: " << hero.getHp() << endl;
  s << "Object in hands: " << *hero.getObject() << endl;

  s << "Backpack: " << endl;

  for (const auto &item : hero.getBackpack()->getItems()) {
    s << "    " << *item << endl;
  }

  return s;
}
} // namespace HE_Arc::RPG