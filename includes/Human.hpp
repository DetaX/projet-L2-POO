#ifndef HUMAN_HPP
#define HUMAN_HPP
#include "Character.hpp"

class Human : public Character {
private:
  int _stamina;
  int _equiped[2];
public:
  Human(std::string,int,int,int,int);
  void viewConsumable(int);
  void setStamina(int stamina){_stamina=stamina;}
  int getStamina(){return _stamina;}
  void info();
  void use();
  void showInventory(){ _inventory->show(); use();}
  void useCon (int i);
  void useEqu (int i);
  void setEqu(int* i){_equiped[0]=i[0];_equiped[1]=i[1];}
  int getEqu0(){return _equiped[0];}
  int getEqu1(){return _equiped[1];}
};

#endif
