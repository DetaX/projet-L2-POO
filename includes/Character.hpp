#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <string>
#include "Inventory.hpp"

class Character {
protected:
  std::string _name;
  int _skill;
  int _health;
  int _armor;
  int _attack; 
  int _luck; 
  Inventory *_inventory;
public:
  void setName(std::string name){_name=name;}
  void setSkill(int skill){_skill=skill;}
  void setHealth(int health){_health=health;}
  void setArmor(int armor){_armor=armor;}
  void setAttack(int attack){_attack=attack;}
  std::string getName(){return _name;}
  int getAttack(){return _attack;}
  int getSkill(){return _skill;}
  int getHealth(){return _health;}
  int getArmor(){return _armor;}
  int getLuck(){return _luck;}
  void attack(Character*);  
  void setLuck(int luck){_luck=luck;}
  Inventory* getInventory(){return _inventory;}
};



#endif
