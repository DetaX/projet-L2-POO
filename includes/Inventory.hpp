#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include <vector>
#include "Consumable.hpp"
#include "Equipable.hpp"

class Inventory {
private:
  std::vector<Equipable> _equipable;
  std::vector<Consumable> _consumable;
public:
  Consumable getConsumable(int pos){return _consumable[pos];};
  Equipable getEquipable(int pos){return _equipable[pos];};
  void add(Equipable e){_equipable.push_back(e);};
  void add(Consumable c){_consumable.push_back(c);};
  int getCon(){return _consumable.size();};
  int getEqu(){return _equipable.size();};
  void add (Inventory* i2);
  void delCon(int i){_consumable.erase(_consumable.begin()+i);};
  void delEqu(int i){_equipable.erase(_equipable.begin()+i);};
  void show();
};

#endif
