#include <iostream>
#include "Inventory.hpp"

void Inventory::show(){
  int i,j;
  std::cout<<std::endl;
  std::cout<<"Consommables :"<<std::endl;
   for (i=0;i<getCon();i++)
    std::cout<<i<<" : "<<_consumable[i].getName()<<std::endl;
   std::cout<<std::endl;std::cout<<"Equipement :"<<std::endl;
   for (j=0;j<getEqu();j++) {
    std::cout<<i<<" : "<<_equipable[j].getName()<<std::endl;
    i++;
    }
}

void Inventory::add(Inventory* i2){  
  int i;
  for (i=0;i<i2->getEqu();i++)
    add(i2->getEquipable(i));
  for (i=0;i<i2->getCon();i++)
    add(i2->getConsumable(i));
    
}
