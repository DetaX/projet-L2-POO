#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP
#include <string>

class Consumable {
private:
  std::string _name;
  std::string _effect;
  int _value;
public:
  Consumable(std::string,std::string,int);
  std::string getName(){return _name;};
  std::string getEffect(){return _effect;};
  int getValue(){return _value;};
};

#endif
