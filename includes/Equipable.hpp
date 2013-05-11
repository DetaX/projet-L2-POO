#ifndef EQUIPABLE_HPP
#define EQUIPABLE_HPP
#include <string>

class Equipable {
private:
  std::string _name;
  int _power;
  int _type;
public:
  Equipable(std::string,int,int);
  std::string getName(){return _name;};
  int getPower(){return _power;};
  int getType(){return _type;};
};

#endif
