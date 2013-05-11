#include <iostream>
#include <cstdlib>
#include "Character.hpp"

void Character::attack(Character* felix) {
  int degat = _skill+_attack-1+rand()%2-felix->_armor;
  if(degat<= 1)
    degat=1;
  if ((rand() % 100 + _luck)>70)
    degat*=1.5;
  felix->setHealth(felix->getHealth()-degat);
  std::cout<<_name<<" a infligé "<<degat<<" de dégats à "<<felix->_name<<std::endl;
}


