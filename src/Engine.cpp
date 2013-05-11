#include "Engine.hpp"
#include "Character.hpp"
#include "tinyxml.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <dirent.h> 

void Engine::save(Human* human){
  time_t timestamp;
  struct tm * t;
  char filename[80];
  timestamp = time(NULL);
  t = localtime(&timestamp);
  sprintf(filename,"saves/%d_%d_%d-%d:%d:%d", t->tm_mday,t->tm_mon,t->tm_year-100,t->tm_hour,t->tm_min,t->tm_sec);
  std::ofstream file (filename, std::ios::out);
  if(!file) exit(1);
  std::vector<std::string>::iterator i;
  for (i = _paragraph.begin()+1; i < _paragraph.end(); ++i) {
    file << *i;
    file << std::endl;
  }
  file << "---------";
  file << std::endl;
  file << human->getName(); file << std::endl;
  file << human->getStamina(); file << std::endl;
  file << human->getSkill(); file << std::endl;
  file << human->getHealth(); file << std::endl;
  file << human->getArmor(); file << std::endl;
  file << human->getAttack(); file << std::endl;
  file << human->getLuck();  file << std::endl;
  file << human->getEqu0(); file << std::endl;
  file << human->getEqu1(); file << std::endl;
  Inventory* inventory = human->getInventory();
  file << human->getInventory()->getCon(); file << std::endl;
  file << human->getInventory()->getEqu(); file << std::endl;
  int j;
  for (j=0;j<inventory->getCon();j++) {
    file << inventory->getConsumable(j).getName(); file << std::endl;
    file << inventory->getConsumable(j).getEffect(); file << std::endl;
    file << inventory->getConsumable(j).getValue(); file << std::endl;
  } 
  for (j=0;j<inventory->getEqu();j++) {
    file << inventory->getEquipable(j).getName(); file << std::endl;
    file << inventory->getEquipable(j).getPower(); file << std::endl;
    file << inventory->getEquipable(j).getType(); file << std::endl;
  }
}

void Engine::load(char filename[80]){
  std::ifstream file (filename, std::ios::in);
  if (file){
    std::string contenu,name,effect; 
    int i,skill,stamina,luck,armor,attack,health,value,type,power,con,equ; 
    int equiped[2];
    while(getline(file, contenu) && contenu != "---------"){ 
      _paragraph.push_back(contenu);
    }
    file >> name;
    file >> stamina;
    file >> skill;
    file >> health; 
    file >> armor;
    file >> attack;
    file >> luck;
    file >> equiped[0];
    file >> equiped[1];
    Human* human = new Human(name,skill,stamina,luck,armor);
    human->setStamina(stamina);
    human->setSkill(skill);
    human->setLuck(luck);
    human->setHealth(health);
    human->setAttack(attack);
    human->setEqu(equiped);
    file >> con;   
    file >> equ;
    for(i=0;i<con;i++){
      getline(file,contenu);
      getline(file, name);
      file >> effect;
      file >> value;
      Consumable c(name,effect,value);
      human->getInventory()->add(c);
    }
    for(i=0;i<equ;i++){
      getline(file,contenu);
      getline(file, name);
      file >> power;
      file >> type;
      Equipable e(name,power,type);
      human->getInventory()->add(e);
      }
    Game(human,_paragraph.back(),this);    
  }
  else 
    std::cout<<"Ce fichier de sauvegarde n'existe pas"<<std::endl;
}

Engine::Engine(){
  _paragraph.push_back("1");
}

int Engine::fight(Human* h, NPC* n) {
  int var=1;
  int health[2]={h->getStamina()*10,n->getHealth()};
  if(h->getSkill()<n->getSkill())
    n->attack(h);
  while(n->getHealth()>0 && h->getHealth()>0 && var!=2) {
    std::cout<<std::endl<<h->getName()<<"("<<h->getHealth()<<"/"<<health[0]<<") vs "<<n->getName()<<"("<<n->getHealth()<<"/"<<health[1]<<")"<<std::endl;
    var = menufight(h,n);
    if (n->getHealth()>0)
      n->attack(h);
  }
  if (var==1) {
    if (n->getHealth()>0)
      return 3;
    else
      return 2;
  }
  else
    return 1;
}

int Engine::escape(Human* h,NPC* n){
  if (n->getSkill()>h->getSkill()) {
    std::cout<<"Vous avez échoué dans votre tentative de fuite"<<std::endl;
    return 1;
  }
  else if(rand()%2 == 1)  {
    std::cout<<"Votre tentative de fuite a réussi"<<std::endl;
    return 2;
  }
  else { 
    std::cout<<"Vous avez échoué dans votre tentative de fuite"<<std::endl;
    return 1;
  }
}

int Engine::menufight(Human* h, NPC* n) {
  int var=1;
  std::string choice="c";
  std::cout<<"0. Attaquer"<<std::endl;
  std::cout<<"1. Voir l'inventaire"<<std::endl;
  std::cout<<"2. Tenter de fuir"<<std::endl;
  while (choice!="0" && choice!="1" && choice!="2"){
    std::cout<<"Quel est votre choix ? ";
    std::cin>>choice;
  }
  if(choice == "0") 
    h->attack(n);
  else if(choice == "1")
    h->showInventory();
  else if(choice=="2") {
    var = escape(h,n);
  }
  return var;
}


void Engine::getJourney(){
  unsigned int i;
  std::cout<<"***************************"<<std::endl;
  std::cout<<"* Parcours du personnage  *"<<std::endl;
  std::cout<<"***************************"<<std::endl;
  for (i=0;i<_paragraph.size();i++) {
    std::cout<<_paragraph[i];
    if(i!=_paragraph.size()-1)
      std::cout<<"->";
    else
      std::cout<<std::endl;
  }
}

Human* Engine::MakeClass(std::string name,TiXmlElement *elem){
  int skill,stamina,luck,armor;
  elem=elem->FirstChildElement("class");

  elem->QueryIntAttribute("skill", &skill);
  elem->QueryIntAttribute("stamina", &stamina);
  elem->QueryIntAttribute("luck", &luck);
  elem->QueryIntAttribute("armor", &armor);

  Human* human = new Human(name,skill,stamina,luck,armor);
  return human;
}

Human* Engine::EditClass(Human* h,TiXmlElement* elem){
  int skill,stamina,luck,armor;
  elem=elem->FirstChildElement("class");

  elem->QueryIntAttribute("skill", &skill);
  elem->QueryIntAttribute("stamina", &stamina);
  elem->QueryIntAttribute("luck", &luck);
  elem->QueryIntAttribute("armor", &armor);

  h->setSkill(skill+h->getSkill());
  h->setStamina(stamina+h->getStamina());
  h->setHealth(h->getStamina()*10);
  h->setArmor(armor+h->getArmor());
  h->setLuck(luck+h->getLuck());

  return h;
}

std::string Engine::Choice(TiXmlElement* elem) {
  std::vector<std::string> vecChoice;
  std::string choice;
  int i;
  elem=elem->FirstChildElement("choice");
  std::cout<<std::endl;
  while (elem) {
    std::cout<<elem->Attribute("id")<<" : "<<elem->GetText()<<std::endl;
    vecChoice.push_back(elem->Attribute("id"));
    elem = elem->NextSiblingElement();
  }
  while(1) {
    std::cout<<std::endl<<"Quel est votre choix ? "<<std::endl;
    std::cin>>choice;
    for(i=0;i!=(int)vecChoice.size();i++)
      if (vecChoice[i]==choice || choice=="m")
	return choice;
  }
}

void Engine::Menu(Human* human,Engine* engine) {
  std::string choice="c";
  std::cout<<"******************"<<std::endl;
  std::cout<<"*****  Menu  *****"<<std::endl;
  std::cout<<"******************"<<std::endl;
  std::cout<<"0. Revenir au jeu"<<std::endl;
  std::cout<<"1. Voir la fiche du personnage"<<std::endl;
  std::cout<<"2. Voir l'inventaire"<<std::endl;
  std::cout<<"3. Sauvegarder"<<std::endl;
  std::cout<<"4. Quitter"<<std::endl;
  while (choice!="0" && choice!="1" && choice!="2" && choice!="3" && choice!="4"){
    std::cout<<"Quel est votre choix ? ";
    std::cin>>choice;
  }
  if(choice=="1") {
    human->info();
    engine->getJourney();
  }
  else if (choice=="2")
    human->showInventory();
  else if (choice=="3")
    engine->save(human);
  else if (choice=="4"){
    engine->save(human);
    exit(1);
    }
  std::cout<<"***************************"<<std::endl;
  std::cout<<
}

Inventory* Engine::itemize(Inventory* inventory,TiXmlElement* elem2) {
   TiXmlElement* elem3=elem2;
   elem2 = elem2->FirstChildElement("inventory");
   elem3 = elem3->FirstChildElement("inventory");
   elem2=elem2->FirstChildElement("equipable");
   while(elem2) {
     int power,type;
     elem2->QueryIntAttribute("power", &power);
     elem2->QueryIntAttribute("type", &type);
     Equipable e(elem2->Attribute("name"), power,type);
     inventory->add(e);
     elem2=elem2->NextSiblingElement("equipable");
   }
   elem3=elem3->FirstChildElement("consumable");   
   while(elem3) {
     int value;
     elem3->QueryIntAttribute("value", &value);
     Consumable c(elem3->Attribute("name"), elem3->Attribute("effect") , value);
     inventory->add(c);
     elem3=elem3->NextSiblingElement("consumable");
   }
   return inventory;
}

void Engine::Game(Human* human,std::string choice,Engine* engine) {
  bool find=false;
  int winfight;
  TiXmlDocument doc("stories/starskytor.xml");  
  if(!doc.LoadFile()){
    std::cerr << "erreur lors du chargement" << std::endl;
    std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
    exit(1);
  }
  TiXmlHandle hdl(&doc);
  TiXmlElement *elem = hdl.FirstChildElement("paragraph").Element();

  while (elem && !find) {
      if(std::string(elem->Attribute("id")) == choice) {
	find = true;
	break;
      }
      elem = elem->NextSiblingElement();
    }
  if (elem) {
    _paragraph.push_back(choice);
    if (elem->FirstChildElement("class")) 
      human = EditClass(human,elem);
    if (elem->FirstChildElement("text")) 
      std::cout<<std::endl<<elem->FirstChildElement("text")->GetText()<<std::endl;
    if (elem->FirstChildElement("fight")) {
      TiXmlElement* elem2 = elem->FirstChildElement("fight");
      int skill,health,armor,luck;
      std::string name =  elem2->Attribute("name");
      elem2->QueryIntAttribute("skill", &skill);
      elem2->QueryIntAttribute("health", &health);
      elem2->QueryIntAttribute("armor", &armor); 
      elem2->QueryIntAttribute("luck", &luck);
      Inventory *inventory = new Inventory();
      itemize(inventory,elem2);
      NPC* npc = new NPC(name,skill,health,armor,luck,inventory);
      winfight=engine->fight(human,npc);
      if (winfight == 3) {
	std::cout<<"oO, vous êtes mort !"<<std::endl;
	human->setHealth(human->getStamina()*10);
	engine->Game(human,getLast(),engine);
      }
      else if (winfight == 2) {
	std::cout<<"Bravo, vous avez tué : "<<npc->getName()<<std::endl;
	std::cout<<"Vous avez récupéré :"<<std::endl;
	inventory->show();
	human->getInventory()->add(inventory);
      }
    }
    if (elem->FirstChildElement("inventory")) {
      itemize(human->getInventory(),elem);
    }  
    if (elem->FirstChildElement("choice")) {
      choice = Choice(elem);
      while(choice=="m") {
	engine->Menu(human,engine);
	if (elem->FirstChildElement("text")) 
	  std::cout<<std::endl<<elem->FirstChildElement("text")->GetText()<<std::endl;
	choice=Choice(elem);
      }
      engine->Game(human,choice,engine); 
    }
  }
  else
    std::cout<<"Paragraphe "<<choice<<" inexistant"<<std::endl;
}

void Engine::startGame(Engine *engine){
  std::string name,choice; 
  bool find=false;
  TiXmlDocument doc("stories/starskytor.xml");
  if(!doc.LoadFile()){
    std::cerr << "erreur lors du chargement" << std::endl;
    std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
    exit(1);
  }
  TiXmlHandle hdl(&doc);
  TiXmlElement *elem = hdl.FirstChildElement("paragraph").Element();
  while (elem && !find)
    {
      if(std::string(elem->Attribute("id")) == "1") {
	find = true;
	break;
      }
      elem = elem->NextSiblingElement();
    }
  if (elem) { 
    if (elem->FirstChildElement("class") && elem->FirstChildElement("text") && elem->FirstChildElement("choice")) {
      std::cout<<std::endl<<elem->FirstChildElement("text")->GetText()<<std::endl;
      std::cout<<std::endl<<"Entrez votre nom : ";
      std::cin>>name;
      Human* human = MakeClass(name,elem);
      choice = Choice(elem);
      while(choice =="m") {
	engine->Menu(human,engine);
	if (elem->FirstChildElement("text")) 
	  std::cout<<std::endl<<elem->FirstChildElement("text")->GetText()<<std::endl;
	choice=Choice(elem);
      }
      engine->Game(human, choice, engine);
    }
    else
      std::cout<<"Paragraphe 1 érroné"<<std::endl;
  }
  else
    std::cout<<"Paragraphe 1 manquant"<<std::endl;
}

void purge()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    {}
}

void clean (char *string){
  char *p = strchr(string, '\n');
  if (p) 
    *p = 0;
  else
    purge();
}

void Engine::start(Engine* engine){
  std::string choice="c";
  std::cout<<"Bienvenue dans le jeu dont vous êtes le héros"<<std::endl;
  std::cout<<"------------------"<<std::endl;
  std::cout<<"Menu"<<std::endl;
  std::cout<<"0. Quitter"<<std::endl;
  std::cout<<"1. Nouvelle partie"<<std::endl;
  std::cout<<"2. Charger une partie"<<std::endl;
  while (choice!="0" && choice!="1" && choice!="2"){
    std::cout<<"Quel est votre choix ? ";
    std::cin>>choice;
  }
  if(choice=="0") {
    exit(1);
  }
  else if (choice=="1")
   engine->startGame(engine);
  else if (choice=="2") {
    purge();
    engine->list_save(engine);
  }
}

void Engine::list_save(Engine* engine) {
  char filename[80];
  struct dirent *lecture;
  DIR *rep;
  rep = opendir("saves/" );
  while ((lecture = readdir(rep))) 
    if(strcmp(lecture->d_name,"..") != 0 && strcmp(lecture->d_name,".") != 0 )
      printf("%s\n", lecture->d_name);
  closedir(rep);
  printf("Choisissez le fichier de sauvegarde : ");
  fgets(filename,80,stdin);
  clean(filename);
  char file[80] = "saves/";
  strcat(file,filename);
  engine->load(file);
}

int main() {
  srand (time(NULL)); 
  TiXmlBase::SetCondenseWhiteSpace(false); // Permet les retours à la ligne lors du parsing avec GetText
  Engine *engine = new Engine;
  engine->start(engine);
  return 0;
}
