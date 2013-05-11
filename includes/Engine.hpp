#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <vector>
#include "tinyxml.hpp"
#include "Inventory.hpp"
#include "Human.hpp"
#include "NPC.hpp"

class Engine {
private:
  std::vector<std::string> _paragraph;
public:
  Engine();
  ~Engine(){};
  void startGame(Engine*);
  void Game(Human*,std::string,Engine*);
  Human* MakeClass(std::string,TiXmlElement*);
  Human* EditClass(Human*,TiXmlElement*);
  std::string Choice(TiXmlElement*);
  void Menu(Human*, Engine*);
  void getJourney();
  int fight(Human*,NPC*);
  int menufight(Human*,NPC*);
  int escape(Human*,NPC*);
  std::string getLast(){return _paragraph[_paragraph.size()-2];};
  Inventory* itemize(Inventory*,TiXmlElement*);
  void save(Human*);
  void load(char*);
  void start(Engine*);
  void list_save(Engine*);
};

#endif
