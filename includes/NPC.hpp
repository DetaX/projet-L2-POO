#ifndef NPC_HPP
#define NPC_HPP
#include "Character.hpp"

class NPC : public Character {
public:
  NPC(std::string,int,int,int,int,Inventory*);  
};

#endif
