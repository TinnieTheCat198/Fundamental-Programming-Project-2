#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
string BaseBag::toString() const
{
    string s = "";
    s += "Bag[count=" + to_string(size) + ';';
    Node* p = head;
    while( p != nullptr )
    {
        s += p->data->getName(); 
        if ( p->next != NULL ) s += ',';
        p = p->next;
    }
    s += "]";
    return s;
}
void BaseBag::deleteFirst(Node* a)
{
    if ( a == NULL )
       return;
    Node* tmp = a;
    a = a->next;
    tmp->next = NULL;
    --size;
    delete tmp;
}

BaseItem* BaseBag::get(ItemType itemType)
{
    Node *before = nullptr, *after = head;
    if ( head->data->getItemType() == itemType )
    {
        --size;
        head = head->next;
        after->next = NULL;
        return after->data;
    }
    else while( after->next != NULL )
    {
        before = after;
        after = after->next;
        if ( after == head->next )
        {
            --size;
            before->next = after->next;
            after->next = before;
            //head = head->next;
            return after->data;
        }
        else if ( after->data->getItemType() == itemType )
        {
            --size;
            Node* p = head, *q = head->next;
            head = NULL;
            before->next = p;
            p->next = after->next;
            after->next = q;
            head = after;
            head = head->next;
            return after->data;
        }
    }
    return NULL;
}
bool PaladinBag::insertFirst(BaseItem * item)
{
    Node* newNode = new Node(item);
    if ( head == NULL ) head = newNode;
    else
    {
        newNode->next = head;
        head = newNode;
    }    
    ++size;
    return 1;
}

bool LancelotBag::insertFirst(BaseItem * item)
{   
    if ( size >= 16 ) return false;
    Node* newNode = new Node(item);
    if ( head == NULL ) head = newNode;
    else
    {
        newNode->next = head;
        head = newNode;
    }    
    ++size;
    return 1;
}

bool DragonBag::insertFirst(BaseItem * item)
{   
    if ( size >= 14 || item->getName() == "Antidote" ) return false;
    Node* newNode = new Node(item);
    if ( head == NULL ) head = newNode;
    else
    {
        newNode->next = head;
        head = newNode;
    }    
    ++size;
    return 1;
}

bool NormalBag::insertFirst(BaseItem * item)
{   
    if ( size >= 19 ) return false;

    Node* newNode = new Node(item);
    if ( head == NULL ) head = newNode;
    else
    {
        newNode->next = head;
        head = newNode;
    }    
    ++size;
    return 1;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseItem * * */
Antidote::Antidote()
{
    name = "Antidote";
    itemType = ANTIDOTE;
}
bool Antidote::canUse( BaseKnight * knight)
{
    if (knight->getBePoisoned()) return true;
    return false;
}
void Antidote::use( BaseKnight * knight )
{
    knight->setBeUnpoisoned();
}

PhoenixDownI::PhoenixDownI()
{
    name = "PhoenixI";
    itemType = PHONENIXDOWN_I;
}

bool PhoenixDownI::canUse( BaseKnight * knight)
{
    if (knight->getHP() <= 0) return true;
    return false;
}
void PhoenixDownI::use( BaseKnight * knight )
{
    knight->setHP( knight->getMaxHP() );
}

PhoenixDownII::PhoenixDownII()
{
    name = "PhoenixII";
    itemType = PHONENIXDOWN_II;
}
bool PhoenixDownII::canUse( BaseKnight * knight)
{
    if (knight->getHP() < knight->getMaxHP()/4 ) return true;
    return false;
}
void PhoenixDownII::use( BaseKnight * knight )
{
    knight->setHP( knight->getMaxHP() );
}

PhoenixDownIII::PhoenixDownIII()
{
    name = "PhoenixIII";
    itemType = PHONENIXDOWN_III;
}
bool PhoenixDownIII::canUse( BaseKnight * knight)
{
    if (knight->getHP() < knight->getMaxHP()/3 ) return true;
    return false;
}
void PhoenixDownIII::use( BaseKnight * knight )
{
    if (knight->getHP() <= 0 ) knight->setHP( knight->getMaxHP()/3 );
    else  knight->setHP( knight->getHP() + knight->getMaxHP()/4 );
}

PhoenixDownIV::PhoenixDownIV()
{
    name = "PhoenixIV";
    itemType = PHONENIXDOWN_IV;
}
bool PhoenixDownIV::canUse( BaseKnight * knight)
{
    if (knight->getHP() < knight->getMaxHP()/2 ) return true;
    return false;
}
void PhoenixDownIV::use( BaseKnight * knight )
{
    if (knight->getHP() <= 0 ) knight->setHP( knight->getMaxHP()/2 );
    else  knight->setHP( knight->getHP() + knight->getMaxHP()/5 );
}
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseKnight * * */
static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{ 
    BaseKnight* knight = NULL;
    
    

    if ( checkPrimeNumber(maxhp) ) knight = new PaladinKnight(); 
    else if ( maxhp == 888 )       knight = new LancelotKnight();
    else if ( checkDragon(maxhp) ) knight = new DragonKnight(); 
    else                           knight = new NormalKnight();

    knight->setID(id);
    knight->setMAXHP(maxhp);
    knight->setHP(maxhp);
    knight->setLEVEL(level);
    knight->setGIL(gil);
    
    for (int i = 1; i <= phoenixdownI; i++)
    {
        BaseItem* item2 = new PhoenixDownI();
        knight->getBag()->insertFirst(item2);
    }
    
    for (int i = 1; i <= antidote; i++)
    {
        BaseItem* item1 = new Antidote();
        knight->getBag()->insertFirst(item1);
    }
    
    return knight;
}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    
    string s("");
    s += "[Knight:id:" + to_string(id) +','
        + "hp:" + to_string(hp)  +','
        + "maxhp:" + to_string(maxhp) +','
        + "level:" + to_string(level) +','
        + "gil:" + to_string(gil) +','
        + bag->toString() +','
        + "knight_type:" + typeString[knightType]
        + "]";
    return s;
}

void BaseKnight::setID(int id){ this->id = id; }
void BaseKnight::setMAXHP(int maxhp){ this->maxhp = maxhp; }
void BaseKnight::setLEVEL(int level)
{ 
    if ( level > 10 ) this->level = 10;
    else this->level = level; 
}
void BaseKnight::setGIL(int gil){ if (gil <= 999) this->gil = gil; else this->gil = 999; }
void BaseKnight::setANTIDOTE(int antidote){ this->antidote = antidote; } 
void BaseKnight::setHP(int hp){ this->hp = hp; }
void BaseKnight::setPHOENIXDOWN_I(int phoenixdownI){ this->phoenixdownI = phoenixdownI; };
int BaseKnight:: getID(){ return id; }
int BaseKnight:: getMaxHP(){ return maxhp; }
int BaseKnight:: getHP(){ return hp; }
int BaseKnight:: getLevel(){ return level; }
int BaseKnight:: getGil(){ return gil; }
int BaseKnight:: getAntidote(){ return antidote; }
int BaseKnight:: getPhoneixdownI(){ return phoenixdownI; }

PaladinKnight::PaladinKnight()
{
    bag = new PaladinBag();
    knightType = PALADIN;
}
LancelotKnight::LancelotKnight()
{
    bag = new LancelotBag();
    knightType = LANCELOT;
}
DragonKnight::DragonKnight()
{
    bag = new DragonBag();
    knightType = DRAGON;
}
NormalKnight::NormalKnight()
{
    bag = new NormalBag();
    knightType = NORMAL;
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights)
{
    fstream knights_info;
    knights_info.open(file_armyknights, ios::in);
    // cout << knights_info.is_open() << endl;
    knights_info >> maxSize;
    changeSize = maxSize;    

    knight = new BaseKnight*[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        int maxhp, level, phoenixdownI, gil, antidote;
        knights_info >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        knight[i] = create(i+1,maxhp, level, gil, antidote, phoenixdownI);
        // cout << knight[i]->maxhp << " " << knight[i]->level << " " << knight[i]->phoenixdownI << " " <<knight[i]->gil << " " <<knight[i]->antidote << endl;
    }


    knights_info.close();
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
       << ";LancelotSpear:" << this->hasLancelotSpear()
       << ";GuinevereHair:" << this->hasGuinevereHair()
       << ";ExcaliburSword:" << this->hasExcaliburSword()
       << endl
       << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

int ArmyKnights::count() const
{
    return changeSize;
}

bool ArmyKnights::fight(BaseOpponent * opponent)
{
    BaseKnight *armyFight = lastKnight();
    int knight_level = armyFight->getLevel();
    int opponent_level = opponent->getLevelO();
    switch( opponent->getOpponentType() )
    {
        case MADBEAR:
        {
            if ( knight_level >= opponent_level || armyFight->getKnightType() == PALADIN || armyFight->getKnightType() == LANCELOT ) armyFight->setGIL( armyFight->getGil() + 100 );
            else armyFight->setHP(  armyFight->getHP() - opponent->getBaseDamage() * ( opponent_level - knight_level ) );
            if (armyFight->getHP() <= 0)
            {
                Node* p = armyFight->getBag()->getNode();
                while(p != NULL)
                {
                    if ( p->data->getItemType() == PHONENIXDOWN_I || p->data->getItemType() == PHONENIXDOWN_II || p->data->getItemType() == PHONENIXDOWN_III || p->data->getItemType() == PHONENIXDOWN_IV )
                    {
                        p->data->use(armyFight);
                        armyFight->getBag()->get(p->data->getItemType());
                        break;
                    }
                    p = p->next;
                }
                if (armyFight->getHP() <= 0)
                { 
                    if (armyFight->getGil() >= 100)
                    {    
                    armyFight->setGIL( armyFight->getGil() - 100 );
                    armyFight->setHP( armyFight->getMaxHP()/2 );
                    }
                    else
                    {
                        --changeSize;
                        return false;
                    }
                }
                
                
            }
            break;
        }

        case BANDIT:
        {
            if ( knight_level >= opponent_level || armyFight->getKnightType() == PALADIN || armyFight->getKnightType() == LANCELOT) armyFight->setGIL( armyFight->getGil() + 150 );
            else armyFight->setHP(  armyFight->getHP() - opponent->getBaseDamage() * ( opponent_level - knight_level ) );            if (armyFight->getHP() <= 0)
            {
                
                Node* p = armyFight->getBag()->getNode();
                while(p != NULL)
                {
                    if ( p->data->getItemType() == PHONENIXDOWN_I || p->data->getItemType() == PHONENIXDOWN_II || p->data->getItemType() == PHONENIXDOWN_III || p->data->getItemType() == PHONENIXDOWN_IV )
                    {
                        p->data->use(armyFight);
                        armyFight->getBag()->get(p->data->getItemType());
                        break;
                    }
                    p = p->next;
                }
                if (armyFight->getHP() <= 0)
                { 
                    if (armyFight->getGil() >= 100)
                    {    
                    armyFight->setGIL( armyFight->getGil() - 100 );
                    armyFight->setHP( armyFight->getMaxHP()/2 );
                    }
                    else
                    {
                        --changeSize;
                        return false;
                    }
                }
               
                
            }
            break;
        }

        case LORDLUPIN:
        {
            if ( knight_level >= opponent_level || armyFight->getKnightType() == PALADIN || armyFight->getKnightType() == LANCELOT ) armyFight->setGIL( armyFight->getGil() + 450 );
            else armyFight->setHP(  armyFight->getHP() - opponent->getBaseDamage() * ( opponent_level - knight_level ) );            if (armyFight->getHP() <= 0)
            {
                Node* p = armyFight->getBag()->getNode();
                while(p != NULL)
                {
                    if ( p->data->getItemType() == PHONENIXDOWN_I || p->data->getItemType() == PHONENIXDOWN_II || p->data->getItemType() == PHONENIXDOWN_III || p->data->getItemType() == PHONENIXDOWN_IV )
                    {
                        p->data->use(armyFight);
                        armyFight->getBag()->get(p->data->getItemType());
                        break;
                    }
                    p = p->next;
                }
                if (armyFight->getHP() <= 0)
                { 
                    if (armyFight->getGil() >= 100)
                    {    
                    armyFight->setGIL( armyFight->getGil() - 100 );
                    armyFight->setHP( armyFight->getMaxHP()/2 );
                    }
                    else
                    {
                        --changeSize;
                        return false;
                    }
                }
                
                
            }
            break;
        }

        case ELF:
        {
            if ( knight_level >= opponent_level || armyFight->getKnightType() == PALADIN || armyFight->getKnightType() == LANCELOT ) armyFight->setGIL( armyFight->getGil() + 750 );
            else armyFight->setHP(  armyFight->getHP() - opponent->getBaseDamage() * ( opponent_level - knight_level ) );            
            if (armyFight->getHP() <= 0)
            {
                Node* p = armyFight->getBag()->getNode();
                while(p != NULL)
                {
                    if ( p->data->getItemType() == PHONENIXDOWN_I || p->data->getItemType() == PHONENIXDOWN_II || p->data->getItemType() == PHONENIXDOWN_III || p->data->getItemType() == PHONENIXDOWN_IV )
                    {
                        p->data->use(armyFight);
                        armyFight->getBag()->get(p->data->getItemType());
                        break;
                    }
                    p = p->next;
                }
                if (armyFight->getHP() <= 0)
                { 
                    if (armyFight->getGil() >= 100)
                    {    
                    armyFight->setGIL( armyFight->getGil() - 100 );
                    armyFight->setHP( armyFight->getMaxHP()/2 );
                    }
                    else
                    {
                        --changeSize;
                        return false;
                    }
                }
                
                
            }
            break;
        }

        case TROLL:
        {
            if ( knight_level >= opponent_level || armyFight->getKnightType() == PALADIN || armyFight->getKnightType() == LANCELOT ) armyFight->setGIL( armyFight->getGil() + 800 );
            else armyFight->setHP(  armyFight->getHP() - opponent->getBaseDamage() * ( opponent_level - knight_level ) );            
            if (armyFight->getHP() <= 0)
            {
                Node* p = armyFight->getBag()->getNode();
                while(p != NULL)
                {
                    if ( p->data->getItemType() == PHONENIXDOWN_I || p->data->getItemType() == PHONENIXDOWN_II || p->data->getItemType() == PHONENIXDOWN_III || p->data->getItemType() == PHONENIXDOWN_IV )
                    {
                        p->data->use(armyFight);
                        armyFight->getBag()->get(p->data->getItemType());
                        break;
                    }
                    p = p->next;
                }
                if (armyFight->getHP() <= 0)
                { 
                    if (armyFight->getGil() >= 100)
                    {    
                    armyFight->setGIL( armyFight->getGil() - 100 );
                    armyFight->setHP( armyFight->getMaxHP()/2 );
                    }
                    else
                    {
                        --changeSize;
                        return false;
                    }
                }
                
                
            }
            break;
        }

        case TORNBERRY:
        {
            if ( knight_level >= opponent_level ) armyFight->setLEVEL( knight_level + 1 );
            else
            {
                if ( armyFight->getKnightType() == DRAGON ) break; // DragonKnight check?
                else armyFight->setBePoisoned();
                Node* u = armyFight->getBag()->getNode();  // Find Antidote

                while(u != NULL)
                {
                    if ( u->data->getItemType() == ANTIDOTE )
                    {
                        u->data->use(armyFight);
                        armyFight->getBag()->get(u->data->getItemType());
                        //cout << "error" << endl;
                        break;
                    }
                    u = u->next;
                }

                if (!(armyFight->getBePoisoned())) goto Exit;
                // Delete 3 recent items in the bag
                for(int i=1; i <=3; i++)
                {
                    Node* p = armyFight->getBag()->getNode();
                    if ( p == NULL ) break;
                    Node* tmp = p;
                    p = p->next;
                    delete tmp;
                    armyFight->getBag()->setNode(p);
                    // armyFight->getBag()->deleteFirst( armyFight->getBag()->getNode() );
                    // cout << armyFight->getBag()->toString()<< endl;
                }
                // HP - 10
                armyFight->setHP( armyFight->getHP() - 10 );
                if (armyFight->getHP() <= 0)
                {
                    Node* p = armyFight->getBag()->getNode();
                    while(p != NULL)
                    {
                        if ( p->data->getItemType() == PHONENIXDOWN_I || p->data->getItemType() == PHONENIXDOWN_II || p->data->getItemType() == PHONENIXDOWN_III || p->data->getItemType() == PHONENIXDOWN_IV )
                        {
                            p->data->use(armyFight);
                            armyFight->getBag()->get(p->data->getItemType());
                            break;
                        }
                        p = p->next;
                    }
                    if (armyFight->getHP() <= 0)
                    { 
                        if (armyFight->getGil() >= 100)
                        {    
                            armyFight->setGIL( armyFight->getGil() - 100 );
                            armyFight->setHP( armyFight->getMaxHP()/2 );
                        }
                        else
                        {
                            --changeSize;
                            return false;
                        }   
                    }
                }   
            }
            Exit:
            break;
        }

        case QUEENOFCARDS:
        {
            if ( knight_level >= opponent_level ) 
            {
                int totalGil = armyFight->getGil() * 2;
                armyFight->setGIL( totalGil );
                if ( totalGil > 999 )
                {
                    int residualGil = totalGil - 999;
                    for(int i = changeSize - 2; i >= 0; i --)
                    {
                        if ( residualGil > 0 )
                        {
                            int totalGil_i = knight[i]->getGil() + residualGil;
                            knight[i]->setGIL( totalGil_i );
                            residualGil = totalGil_i - 999;
                        }
                        else break;
                    } 
                }
            }
            else
            {
                if ( armyFight->getKnightType() == PALADIN ) break;
                armyFight->setGIL( armyFight->getGil()/2 );
            }
            break;
        }
        
        case NINADERINGS:
        {
            if ( armyFight->getHP() < armyFight->getMaxHP()/3 )
            {
                if ( armyFight->getGil() >= 50 )
                {
                    if (armyFight->getKnightType() != PALADIN) armyFight->setGIL( armyFight->getGil() - 50 );
                    armyFight->setHP( armyFight->getHP() + armyFight->getMaxHP()/5 );
                } 
                else 
                {
                    if (armyFight->getKnightType() == PALADIN) armyFight->setHP( armyFight->getHP() + armyFight->getMaxHP()/5 );
                }               
            }
        
            break;
        }

        case DURIANGARDEN:
        {
            armyFight->setHP( armyFight->getMaxHP() );
            break;
        }

        case OMEGAWEAPON:
        {
            if ( armyFight->getKnightType() == DRAGON || armyFight->getHP() == armyFight->getMaxHP() && armyFight->getLevel() == 10 )
            {
                armyFight->setLEVEL(10);
                armyFight->setGIL(999);
            }
            else armyFight->setHP(0);

            if (armyFight->getHP() <= 0)
                {
                    Node* p = armyFight->getBag()->getNode();
                    while(p != NULL)
                    {
                        if ( p->data->getItemType() == PHONENIXDOWN_I || p->data->getItemType() == PHONENIXDOWN_II || p->data->getItemType() == PHONENIXDOWN_III || p->data->getItemType() == PHONENIXDOWN_IV )
                        {
                            p->data->use(armyFight);
                            armyFight->getBag()->get(PHONENIXDOWN_I);
                            break;
                        }
                        p = p->next;
                    }
                    if (armyFight->getHP() <= 0)
                    { 
                        if (armyFight->getGil() >= 100)
                        {    
                            armyFight->setGIL( armyFight->getGil() - 100 );
                            armyFight->setHP( armyFight->getMaxHP()/2 );
                        }
                        else
                        {
                            --changeSize;
                            return false;
                        }   
                    }
                }
            break;
        }

        case HADES:
        {
            if ( armyFight->getKnightType() == PALADIN && armyFight->getLevel() >= 8 || armyFight->getLevel() == 10 )
                shield = 1;
            else armyFight->setHP(0);
            if (armyFight->getHP() <= 0)
                {
                    Node* p = armyFight->getBag()->getNode();
                    while(p != NULL)
                    {
                        if ( p->data->getItemType() == PHONENIXDOWN_I || p->data->getItemType() == PHONENIXDOWN_II || p->data->getItemType() == PHONENIXDOWN_III || p->data->getItemType() == PHONENIXDOWN_IV )
                        {
                            p->data->use(armyFight);
                            armyFight->getBag()->get(p->data->getItemType());
                            break;
                        }
                        p = p->next;
                    }
                    if (armyFight->getHP() <= 0)
                    { 
                        if (armyFight->getGil() >= 100)
                        {    
                            armyFight->setGIL( armyFight->getGil() - 100 );
                            armyFight->setHP( armyFight->getMaxHP()/2 );
                        }
                        else
                        {
                            --changeSize;
                            return false;
                        }   
                    }
                }
        }
    }
    return true;
}

BaseKnight * ArmyKnights::lastKnight() const
{
    return knight[changeSize-1];
}

BaseKnight ** ArmyKnights::getKnight() const
{
    return knight;
}

ArmyKnights::~ArmyKnights()
{
    //for (int i = 0; i < maxSize; i++)
    //{
    //    delete knight[i];
    //}
    //delete knight;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class Events * * */
Events::Events( const string & file_events )
{
    fstream events_list;
    events_list.open(file_events, ios::in);
    events_list >> numOfEvents;
    for (int i = 0; i < numOfEvents; i++)
    {
        events_list >> events[i];
    }
    events_list.close();
}

int Events::count() const
{
    return numOfEvents;
}

int Events::get(int i) const
{
    return events[i];
}

Events:: ~Events()
{
    //delete [] events;
}
/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure()
{
    delete armyKnights;
    delete events;
}

void KnightAdventure::loadArmyKnights(const string & file_armyKnights)
{
    armyKnights = new ArmyKnights(file_armyKnights);
}

void KnightAdventure::loadEvents(const string & file_events)
{
    events = new Events(file_events);
}


void KnightAdventure::run()
{
   
    for(int i = 0; i < events->count(); i++)
    {
        // armyKnights->printInfo();
        int current = events->get(i);
        switch( current )
        {
            case 1:
            {
                BaseOpponent *p = new Madbear(&events[i]);
                p->setLevelO(i, current);
                while ( 1 )
                {
                    if (armyKnights->fight(p)) break;
                }
                break;
            }

            case 2:
            {   
                BaseOpponent *p = new Bandit(&events[i]);
                p->setLevelO(i, current);
                while ( 1 )
                {
                    if (armyKnights->fight(p)) break;
                }
                break;
            }

            case 3:
            {   
                BaseOpponent *p = new LordLupin(&events[i]);
                p->setLevelO(i, current);
                while ( 1 )
                {
                    if (armyKnights->fight(p)) break;
                }
                break;
            }

            case 4:
            {   
                BaseOpponent *p = new Elf(&events[i]);
                p->setLevelO(i, current);
                while ( 1 )
                {
                    if (armyKnights->fight(p)) break;
                }
                break;
            }

            case 5:
            {    
                BaseOpponent *p = new Troll(&events[i]);
                p->setLevelO(i, current);
                while ( 1 )
                {
                    if (armyKnights->fight(p)) break;
                }
                break;
            }

            case 6:
            {
                BaseOpponent *p = new TornBerry(&events[i]);
                p->setLevelO(i, current);
                armyKnights->fight(p);
                break;
            }

            case 7:
            {
                BaseOpponent *p = new QueenOfCards(&events[i]);
                p->setLevelO(i, current);
                armyKnights->fight(p);
                break;
            }

            case 8:
            {
                BaseOpponent *p = new NinaDeRings();
                armyKnights->fight(p);
                break;
            }

            case 9:
            {
                BaseOpponent *p = new DurianGarden();
                armyKnights->fight(p);
                goto Print;
            }

            case 10:
            {
                BaseOpponent *p = new OmegaWeapon();
                armyKnights->fight(p);
                break;
            }

            case 11:
            {
                BaseOpponent *p = new Hades();
                armyKnights->fight(p);
                break;
            }

            case 112:
            {
                int i = armyKnights->count() - 1;
                BaseItem* p = new PhoenixDownII();
                while( armyKnights->getKnight()[i]->getBag()->insertFirst(p) )
                {
                    --i;
                    if ( i < 0 ) break;
                }
                break;
            }

            case 113:
            {
                int i = armyKnights->count() - 1;
                BaseItem* p = new PhoenixDownIII();
                while( armyKnights->getKnight()[i]->getBag()->insertFirst(p) )
                {
                    --i;
                    if ( i < 0 ) break;
                }
                break;
            }

            case 114:
            {
                int i = armyKnights->count() - 1;
                BaseItem* p = new PhoenixDownIV();
                while( armyKnights->getKnight()[i]->getBag()->insertFirst(p) )
                {
                    --i;
                    if ( i < 0 ) break;
                }
                break;
            }

            case 95:
            {
                if ( armyKnights->hasPaladinShield() == 1 ) break;
                armyKnights->shield = 1;
                break;
            }

            case 96:
            {
                armyKnights->spear = 1;
                break;
            }

            case 97:
            {
                armyKnights->hair = 1;
                break;
            }

            case 98:
            {
                if ( armyKnights->hasGuinevereHair() && armyKnights->hasLancelotSpear() && armyKnights->hasPaladinShield() )
                armyKnights->sword = 1;
                break;
            }
            
            case 99:
            {
                int UltimeciaHP = 5000;
                if ( armyKnights->hasExcaliburSword() ) break;
                else if ( armyKnights->hasGuinevereHair() && armyKnights->hasLancelotSpear() && armyKnights->hasPaladinShield() )
                {
                    int i = armyKnights->count() - 1;
                    while( i >= 0 )
                    {
                        if ( armyKnights->getKnight()[i]->getKnightType() == LANCELOT )
                            UltimeciaHP -= 0.05*armyKnights->getKnight()[i]->getHP()*armyKnights->getKnight()[i]->getLevel();
                        else if ( armyKnights->getKnight()[i]->getKnightType() == DRAGON )
                            UltimeciaHP -= 0.06*armyKnights->getKnight()[i]->getHP()*armyKnights->getKnight()[i]->getLevel();
                        else if ( armyKnights->getKnight()[i]->getKnightType() == PALADIN )
                            UltimeciaHP -= 0.075*armyKnights->getKnight()[i]->getHP()*armyKnights->getKnight()[i]->getLevel();
                        --i;
                    }
                    if ( UltimeciaHP <= 0 )
                    {
                        win = 1;
                        break;
                    }
                    else 
                    {
                        win = 0;
                        armyKnights->setChangeSize(0);
                    }
                }
                else
                {
                    for(int i = 0; i < armyKnights->count(); i++)
                    {
                        armyKnights->getKnight()[i]->setHP(0);
                    }
                    armyKnights->setChangeSize(0);
                    win = 0;
                }
                goto Print;
                break;
            }
        }
        if ( armyKnights->lastKnight()->getHP() < armyKnights->lastKnight()->getMaxHP() )
        {
            Node* p = armyKnights->lastKnight()->getBag()->getNode();
            while(p != NULL)
            {
                switch ( p->data->getItemType() )
                {
                    case PHONENIXDOWN_I:
                    {
                        if ( p->data->canUse(armyKnights->lastKnight()) )
                        {
                            p->data->use(armyKnights->lastKnight());
                            armyKnights->lastKnight()->getBag()->get(p->data->getItemType());
                        }
                        break;
                    }

                    case PHONENIXDOWN_II:
                    {
                        if ( p->data->canUse(armyKnights->lastKnight()) )
                        {
                            p->data->use(armyKnights->lastKnight());
                            armyKnights->lastKnight()->getBag()->get(p->data->getItemType());
                        }
                        break;
                    }

                    case PHONENIXDOWN_III:
                    {
                        if ( p->data->canUse(armyKnights->lastKnight()) )
                        {
                            p->data->use(armyKnights->lastKnight());
                            armyKnights->lastKnight()->getBag()->get(p->data->getItemType());
                        }
                        break;
                    }

                    case PHONENIXDOWN_IV:
                    {
                        if ( p->data->canUse(armyKnights->lastKnight()) )
                        {
                            p->data->use(armyKnights->lastKnight());
                            armyKnights->lastKnight()->getBag()->get(p->data->getItemType());
                        }
                        break;
                    }

                }
                p = p->next;
            }
        }

        Print:
        armyKnights->printInfo();
        if ( armyKnights->count() > 0 ) win = 1;
        if ( i == events->count()-1 || armyKnights->count() == 0 ) armyKnights->printResult( win );
    }
}
/* * * END implementation of class KnightAdventure * * */

/* * * BEGIN implementation of subclass of BaseOpponent * * */
BaseOpponent::BaseOpponent(Events *event)
    : event{event} 
    {}
void BaseOpponent::setLevelO(int i, int event_id)
{
    levelO = (i + event_id)%10 + 1;
}
BaseOpponent::~BaseOpponent(){ delete event; }
// class Madbear
Madbear::Madbear(Events *event)
    : BaseOpponent(event) 
    {
        opponentType = MADBEAR;
        baseDamage = 10;
    }
void Madbear::setLevelO(int i, int event_id )
{
    levelO = (i + event_id)%10 + 1;
}
int Madbear::getBaseDamage() const { return 10; }
int Madbear::getLevelO() const { return levelO; }
Madbear::~Madbear() { delete event; }
// class Bandit
Bandit::Bandit(Events *event)
    : BaseOpponent( event)
    {
        opponentType = BANDIT;
        baseDamage = 15;
    }
void Bandit::setLevelO(int i, int event_id )
{
    levelO = (i + event_id)%10 + 1;
}
int Bandit::getBaseDamage() const { return 15; }
int Bandit::getLevelO() const { return levelO; }
Bandit::~Bandit() { delete event; }
// class LordLupin
LordLupin::LordLupin(Events *event)
    : BaseOpponent(event)
    {
        opponentType = LORDLUPIN;
        baseDamage = 45;
    }
void LordLupin::setLevelO(int i, int event_id )
{
    levelO = (i + event_id)%10 + 1;
}
int LordLupin::getBaseDamage() const { return 45; }
int LordLupin::getLevelO() const { return levelO; }
LordLupin::~LordLupin() { delete event; }
// class Elf
Elf::Elf(Events *event)
    : BaseOpponent(event)
    {
        opponentType = ELF;
        baseDamage = 75;
    }
void Elf::setLevelO(int i, int event_id )
{
    levelO = (i + event_id)%10 + 1;
}
int Elf::getBaseDamage() const { return 75; }
int Elf::getLevelO() const { return levelO; }
Elf::~Elf() { delete event; }
// class Troll
Troll::Troll(Events *event)
    : BaseOpponent(event)
    {
        opponentType = TROLL;
        baseDamage = 95;
    }
void Troll::setLevelO(int i, int event_id )
{
    levelO = (i + event_id)%10 + 1;
}
int Troll::getBaseDamage() const { return 95; }
int Troll::getLevelO() const { return levelO; }
Troll::~Troll() { delete event; }
// class TornBerry
TornBerry::TornBerry(Events* event)
    : BaseOpponent(event)
{
    opponentType = TORNBERRY;
}
void TornBerry::setLevelO(int i, int event_id )
{
    levelO = (i + event_id)%10 + 1;
}
int TornBerry::getLevelO() const { return levelO; }
int TornBerry::getBaseDamage() const { return baseDamage; }
TornBerry::~TornBerry(){ delete event; }
// class Queen Of Cards
QueenOfCards::QueenOfCards(Events* event)
    : BaseOpponent(event)
{
    opponentType = QUEENOFCARDS;
}
void QueenOfCards::setLevelO(int i, int event_id)
{
    levelO = (i + event_id)%10 + 1;
}
int QueenOfCards::getLevelO() const { return levelO; }
QueenOfCards::~QueenOfCards(){ delete event; }
// class NinaDeRings
NinaDeRings::NinaDeRings()
{
    opponentType = NINADERINGS;
}
NinaDeRings::~NinaDeRings(){ delete event; }
// class DurianGarden
DurianGarden::DurianGarden()
{
    opponentType = DURIANGARDEN;
}
DurianGarden::~DurianGarden(){ delete event; }
// class OmegaWeapon
OmegaWeapon::OmegaWeapon()
{
    opponentType = OMEGAWEAPON;
}
OmegaWeapon::~OmegaWeapon(){ delete event; }
// class Hades
Hades::Hades()
{
    opponentType = HADES;
}
Hades::~Hades(){ delete event; }

/* * * END implementation of subclass of BaseOpponent * * */

/*** BEGIN imlepment of additional function*/

bool checkPrimeNumber(int n) 
{
    if (n < 2) 
    {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) 
    {
        if (n % i == 0) 
        {
            return 0;
        }
    }
    return 1;
}

bool checkDragon(int maxhp) {
    if (maxhp < 100 || maxhp > 999) 
    {
        return 0;
    }
    // Extract the three digits from the initial HP
    int a = maxhp / 100; // the first digit
    int b = (maxhp / 10) % 10; // the second digit
    int c = maxhp % 10; // the third digit
    // Check if the three digits form a Pythagorean triple
    if ( (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a ) && ( a > 0 ) && ( b > 0 ) && ( c > 0 ) )
        return 1; 
  // Otherwise, the initial HP is not valid
    return 0;
}

Node::Node(BaseItem* item)
{
    data = item;
    next = nullptr;
}