#include <iostream>
#include <cstdlib>
#include "Human.hpp"

Human::Human(std::string name, int skill, int stamina, int luck, int armor) {
  _name=name;
  _attack=0;
  _armor=armor;
  _skill=skill+rand()%12+1;
  _luck=luck+rand()%6+1;
  _stamina=stamina+rand()%12+1;
  _health=_stamina*10;
  Inventory* i = new Inventory();
  _inventory=i;
}

void Human::viewConsumable(int pos) {
  std::cout<<_inventory->getConsumable(pos).getName()<<std::endl;
}

void Human::use() {
  std::string choix1;
  std::cout<<"Quel objet voulez vous utiliser? (si vous n'utilisez rien vous vous faites frapper attention)"<<std::endl;
  std::cin>>choix1;
  int choix = atoi(choix1.c_str());
  if(choix==0 && choix1 != "0") {
    std::cout<<"Vous n'avez rien utilisé";
    std::cout<<std::endl;
  }
  else {
    if (choix >= 0 && choix < _inventory->getCon())
      useCon(choix);
    else if (choix >= _inventory->getCon() && choix < _inventory->getCon()+_inventory->getEqu())
      useEqu(choix); 
    else {std::cout<<"Vous n'avez rien utilisé"; std::cout<<std::endl;}
  }
}

void Human::info(){
  std::cout<<"***************************"<<std::endl;
  std::cout<<"*** Fiche du personnage ***"<<std::endl;
  std::cout<<"***************************"<<std::endl;
  std::cout<<"Nom : "<<_name<<std::endl;
  std::cout<<"Habileté : "<<_skill<<std::endl;
  std::cout<<"Chance : "<<_luck<<std::endl;
  std::cout<<"Endurance : "<<_stamina<<std::endl;
  std::cout<<"Vie : "<<_health<<"/"<<_stamina*10<<std::endl;
  std::cout<<"Armure : "<<_armor;
  if (_equiped[1]!=-1)
    std::cout<<" ("<<_inventory->getEquipable(_equiped[1]).getName()<<")";
  std::cout<<std::endl;
  std::cout<<"Arme : "<<_attack;
  if (_equiped[0]!=-1)
    std::cout<<" ("<<_inventory->getEquipable(_equiped[0]).getName()<<")";
  std::cout<<std::endl;
}

void Human::useCon(int i){
  if (i>=0 && i<_inventory->getCon())
    {
      std::cout<<"Vous avez utilisé : "<<_inventory->getConsumable(i).getName()<<std::endl;
      if(_inventory->getConsumable(i).getEffect() == "health")
	{
	  _health+=_inventory->getConsumable(i).getValue();
	  if(_health>(_stamina*10))
	    _health=_stamina*10;
	}
      else if(_inventory->getConsumable(i).getEffect() == "luck")
	_luck+=_inventory->getConsumable(i).getValue();
      else if(_inventory->getConsumable(i).getEffect() == "skill")
	_skill+=_inventory->getConsumable(i).getValue();
      else if(_inventory->getConsumable(i).getEffect() == "stamina")
	_stamina+=_inventory->getConsumable(i).getValue();
      _inventory->delCon(i);
    }
}

void Human::useEqu(int i){
  if (i>=_inventory->getCon() && i <=_inventory->getCon()+_inventory->getEqu())
    {
      Equipable equ = _inventory->getEquipable(i-_inventory->getCon());
      std::cout<<"Vous avez équipé : "<<equ.getName()<<std::endl;
      if(equ.getType()==1) {
	_equiped[0]= i-_inventory->getCon();
	_attack=equ.getPower();
      }
      else if(equ.getType()==2) {
	_equiped[1]= i-_inventory->getCon();
	_armor=equ.getPower();
      }
    }
}
