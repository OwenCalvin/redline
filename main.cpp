#include <algorithm>
#include <iostream>
#include <list>

#include "./headers/Potion.h"
#include "./headers/Shield.h"
#include "./headers/Sword.h"

#include "./headers/Hero.h"
#include "./headers/Necromancer.h"
#include "./headers/Warrior.h"
#include "./headers/Wizard.h"

#include "./headers/PotionVendor.h"
#include "./headers/WeaponVendor.h"

#include "./headers/Menu.h"

using namespace std;
using namespace HE_Arc::RPG;

int main(int argc, char const *argv[]) {
  // Initialize all the required heros and items
  list<Hero *> party;

  Sword *defaultSword = new Sword(10);
  Potion *defaultPotion = new Potion(5);
  Shield *defaultShield = new Shield(15);

  Warrior *ven = new Warrior(20, 20, 20, 20, "Owen", defaultSword);
  Wizard *clems = new Wizard(20, 20, 20, 20, "Clement", 10, defaultPotion);
  Warrior *jerem = new Warrior(20, 20, 20, 20, "Jeremy", defaultSword);
  Wizard *julien = new Wizard(20, 20, 20, 20, "Julien", 15, defaultPotion);
  Necromancer *quentin =
      new Necromancer(20, 20, 20, 20, "Quentin", 15, defaultPotion);

  WeaponVendor *martin =
      new WeaponVendor(20, 20, 20, 20, "Martin", 1.9, defaultPotion);
  WeaponVendor *ali =
      new WeaponVendor(20, 20, 20, 20, "Ali", 0.8, defaultPotion);
  PotionVendor *harry =
      new PotionVendor(20, 20, 20, 20, "Harry", 1.4, defaultSword);
  PotionVendor *aria =
      new PotionVendor(20, 20, 20, 20, "Aria", 2.2, defaultSword);

  party.push_back(ven);
  party.push_back(clems);
  party.push_back(jerem);
  party.push_back(julien);
  party.push_back(quentin);
  party.push_back(martin);
  party.push_back(ali);
  party.push_back(harry);
  party.push_back(aria);

  ven->getBackpack()->add(defaultShield);
  ven->getBackpack()->add(defaultPotion);

  clems->getBackpack()->add(defaultShield);
  clems->getBackpack()->add(defaultPotion);
  clems->getBackpack()->add(new Potion(10, 3));
  clems->getBackpack()->add(defaultSword);

  // Shows the menu and initialize the navigation
  Menu::setHero(ven);

  vector<Vendor *> vendors{martin, ali, harry, aria};
  Menu::setVendors(vendors);

  vector<Hero *> players{clems, jerem, julien, quentin};
  Menu::setPlayers(players);

  Menu::printTitle();
  Menu::sperate();

  Menu::print("Bonjour, vous êtes le héro " + ven->getName() +
              ". Voici votre carte d'identité ainsi que votre équipement:");
  Menu::printHero(ven);

  Menu::updateMenu();

  return 0;
}
