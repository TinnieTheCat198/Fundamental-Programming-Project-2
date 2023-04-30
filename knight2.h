#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseKnight;
class Events;
class BaseItem;
class BaseBag;
class Node;

enum ItemType {ANTIDOTE = 1, PHONENIXDOWN_I, PHONENIXDOWN_II, PHONENIXDOWN_III, PHONENIXDOWN_IV};
class BaseBag {
protected:
    Node* head ;
    int size ;
public:
    BaseBag()
    {
        head = nullptr;
        size = 0;
    }
    virtual bool insertFirst(BaseItem * item)=0;
    void deleteFirst(Node* );
    void setNode(Node* a){ head = a; --size; }
    BaseItem * get(ItemType itemType);
    string toString() const;
    Node* getNode() const { return head; }
};
class PaladinBag : public BaseBag 
{
    public:
    PaladinBag() 
    {
        head = nullptr;
        size = 0;
    }
    bool insertFirst(BaseItem * item);
    // BaseItem * get(ItemType itemType);
    // string toString() const;
    // ~PaladinBag(){ delete head; };
};
class LancelotBag : public BaseBag 
{
    public:
    LancelotBag()  
    {
        head = nullptr;
        size = 0;
    }
    bool insertFirst(BaseItem * item);
    // BaseItem * get(ItemType itemType);
    // string toString() const;
    // ~LancelotBag(){ delete head; };
};
class DragonBag : public BaseBag 
{
    public:
    DragonBag() 
    {
        head = nullptr;
        size = 0;
    }
    bool insertFirst(BaseItem * item);
    // BaseItem * get(ItemType itemType);
    // string toString() const;
    // ~DragonBag(){ delete head; };
};
class NormalBag : public BaseBag 
{
    public:
    NormalBag()  
    {
        head = nullptr;
        size = 0;
    }
    bool insertFirst(BaseItem * item);
    // BaseItem * get(ItemType itemType);
    // string toString() const;
    // ~NormalBag(){ delete head; };;
};

enum OpponentType {MADBEAR = 0, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERRY, QUEENOFCARDS, NINADERINGS, DURIANGARDEN, OMEGAWEAPON, HADES};
class BaseOpponent
{
protected:
    OpponentType opponentType;
    int baseDamage{};
    int levelO{};
    Events *event ;
public:
    BaseOpponent() = default;
    BaseOpponent(Events *event);
    OpponentType getOpponentType(){ return opponentType; }
    void setLevelO(int, int) ;
    void setBaseDamage() ;
    int getLevelO() const { return levelO; };
    int getBaseDamage() const { return baseDamage; }
    virtual ~BaseOpponent();
};

class Madbear : public BaseOpponent 
{
public:
    Madbear(Events *event);
    void setLevelO(int, int);
    void setBaseDamage(int);
    int getBaseDamage() const;
    int getLevelO() const;
    ~Madbear();
};
class Bandit : public BaseOpponent 
{
public:
    Bandit(Events *event);
    void setLevelO(int, int);
    void setBaseDamage(int);
    int getBaseDamage() const;
    int getLevelO() const;
    ~Bandit();
};
class LordLupin : public BaseOpponent 
{
    public:
    LordLupin(Events *event);
    void setLevelO(int, int);
    void setBaseDamage(int);
    int getBaseDamage() const;
    int getLevelO() const;
    ~LordLupin();
};
class Elf : public BaseOpponent 
{
    public:
    Elf(Events *event);
    void setLevelO(int, int);
    void setBaseDamage(int);
    int getBaseDamage() const;
    int getLevelO() const;
    ~Elf();
};
class Troll : public BaseOpponent 
{
    public:
    Troll(Events *event);
    void setLevelO(int, int);
    void setBaseDamage(int);
    int getBaseDamage() const;
    int getLevelO() const;
    ~Troll();
};
class TornBerry : public BaseOpponent
{
    public:
    TornBerry(Events *event);
    void setLevelO(int, int);
    int getLevelO() const;
    int getBaseDamage() const;
    ~TornBerry();
};
class QueenOfCards : public BaseOpponent 
{
    public:
    QueenOfCards(Events*);
    void setLevelO(int, int) ;
    int getLevelO() const ;
    ~QueenOfCards();
};
class NinaDeRings : public BaseOpponent 
{
    public:
    NinaDeRings();
    ~NinaDeRings();
};
class DurianGarden : public BaseOpponent 
{
    public:
    DurianGarden();
    ~DurianGarden();
};
class OmegaWeapon : public BaseOpponent
{
    public:
    OmegaWeapon();
    ~OmegaWeapon();
};
class Hades : public BaseOpponent
{
    public:
    Hades();
    ~Hades();
};
enum KnightType { PALADIN=0 , LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:

    int id;
    int hp;
    int maxhp;
    int phoenixdownI;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;
    bool bePoisoned = 0;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    virtual void setBePoisoned() = 0;
    void setBeUnpoisoned(){ bePoisoned = 0; }
    bool getBePoisoned(){ return bePoisoned; }
    void setID(int id);
    void setMAXHP(int maxhp);
    void setHP(int maxhp);
    void setLEVEL(int level);
    void setGIL(int gil);
    void setANTIDOTE(int antidote);
    void setPHOENIXDOWN_I(int phoenixdownI);
    int getID();
    int getMaxHP();
    int getHP();
    int getLevel();
    int getGil();
    int getAntidote();
    int getPhoneixdownI();
    KnightType getKnightType(){ return knightType; }
    BaseBag* getBag(){ return bag; }
    virtual ~BaseKnight(){ delete bag; };
};

class PaladinKnight : public BaseKnight 
{ 
    public: 
    PaladinKnight(); 
    void setBePoisoned(){ bePoisoned = 1; } 
    ~PaladinKnight(){ delete bag; }
};
class LancelotKnight : public BaseKnight 
{ 
    public: 
    LancelotKnight();  
    void setBePoisoned(){ bePoisoned = 1;} 
    ~LancelotKnight(){ delete bag; }
    };
class DragonKnight : public BaseKnight 
{ 
    public: 
    DragonKnight();  
    void setBePoisoned(){bePoisoned = 0;}
    ~DragonKnight(){ delete bag;} 
};
class NormalKnight : public BaseKnight 
{ 
    public: 
    NormalKnight();  
    void setBePoisoned(){bePoisoned = 1;};
    ~NormalKnight(){delete bag;} 
};

class ArmyKnights {
private:
    BaseKnight** knight;
    int maxSize, changeSize;
public:
    bool shield=0, spear = 0, hair = 0, sword = 0;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    void setChangeSize(int a){ this->changeSize = a; }
    BaseKnight * lastKnight() const;
    BaseKnight ** getKnight() const;

    bool hasPaladinShield() const{ return shield; }
    bool hasLancelotSpear() const{ return spear; }
    bool hasGuinevereHair() const{ return hair; }
    bool hasExcaliburSword() const{ return sword; }

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
protected:
    string name{};
    ItemType itemType{};
public:
    BaseItem()= default;
    void setName(string name);
    string getName(){ return name; }
    ItemType getItemType(){ return itemType; }
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote : public BaseItem 
{ 
    public:
    Antidote(); 
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownI : public BaseItem 
{ 
    public:
    PhoenixDownI(); 
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownII : public BaseItem 
{ 
    public:
    PhoenixDownII(); 
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownIII : public BaseItem 
{
    public:
    PhoenixDownIII(); 
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownIV : public BaseItem 
{ 
    public:
    PhoenixDownIV(); 
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};

class Events {
private:
    int numOfEvents {};
    int *events = new int[1000];
public:
    Events ( const string & file_events );
    ~Events();
    int count() const;
    int get(int i) const;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    bool encounterOmegaWeapon = 0;
    bool encounterHades = 0;
    bool win = 0;
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

bool checkPrimeNumber(int);
bool checkDragon(int);
class Node
{
    public:
    BaseItem* data;
    Node* next = NULL;
    
    Node(BaseItem* item);
};
#endif // __KNIGHT2_H__