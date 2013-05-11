#include "NPC.hpp"

NPC::NPC(std::string name, int skill, int health, int armor, int luck, Inventory* inventory) {
  _attack=0;
  _name=name;
  _armor=armor;
  _health=health;
  _skill=skill;
  _luck=luck;
}
