#include "Character.hpp"
#include <iostream>
#include <cstdlib>
#include <typeinfo>

std::string Character::getName() { return name; }

int Character::getHealth() { return health; }

bool Character::isAlive() { return health > 0; }

void Character::takeDamage(int damage) 
{
    if (health < damage)
    {
        std::cout << "Damage taken: " << health << "\n";
        health = 0;
        std::cout << name << " died" << std::endl;
    }
    else
    {
        health -= damage;
        std::cout << "Damage taken: " << damage << "\n";
        std::cout << "Health remaining: " << health << std::endl;
    }
}

void Character::heal(int heal)
{
    health += heal;
    if (health > maxHealth)
    {
        std::cout << "Health regained: " << heal - health + maxHealth << "\n";
        health = maxHealth;
    }
    else
    {
        std::cout << "Health regained: " << heal << "\n";
    }
    std::cout << "Health remaining: " << health << std::endl;
}

void Warrior::attack(Character* target)
{
    std::cout << "Preparing to attack\n";
    performMeleeAttack(target);
}

void Warrior::performMeleeAttack(Character* target)
{
    target->takeDamage(meleeDamage);
    std::cout << "Melee damage outgoing: " << meleeDamage << std::endl;
}

void Mage::attack(Character* target)
{
    std::cout << "Preparing to attack\n";
    castSpell(target);
}

void Mage::castSpell(Character* target)
{
    try{
        useMana(10);
    }catch(const NoManaException& e) 
    {
        std::cout << "Not enought mana!" << std::endl;
        return;
    }
    std::cout << "Spell damage outgoing: ";
    if (dynamic_cast<CanUseMelee*>(target) != nullptr)
    {
        std::cout << spellDamage + 10 << " (Bonus +10)" << std::endl;
        target->takeDamage(spellDamage + 10);
    }
    else
    {
        std::cout << spellDamage << std::endl;
        target->takeDamage(spellDamage);
    }
}

const char* NoManaException::what() const noexcept 
{
    return "Not enough mana!";
}

int CanCastSpells::getMana() { return mana; }

void CanCastSpells::addMana(int amount)
{
    mana += amount;
    if (mana > maxMana)
    {
        std::cout << "Mana regained: " << amount - mana + maxMana << "\n";
        mana = maxMana;
    }
    else
    {
        std::cout << "Mana regained: " << amount << "\n";
    }
    std::cout << "Mana remaining: " << mana << std::endl;
}

void CanCastSpells::useMana(int amount)
{
    if (amount > mana)
    {
        throw NoManaException();
    }
    mana -= amount;
    std::cout << "Mana used: " << amount << "\n";
    std::cout << "Mana remaining: " << mana << std::endl;
}

void BattleMage::performMeleeAttack(Character* target)
{
    std::cout << "Melee damage outgoing: " << battleMeleeDamage << std::endl;
    target->takeDamage(battleMeleeDamage);
}

void BattleMage::castSpell(Character* target)
{
    try{
        useMana(8);
    }catch(const NoManaException& e) 
    {
        std::cout << "Not enought mana!" << std::endl;
        return;
    }
    std::cout << "Spell damage outgoing: " << battleSpellDamage << std::endl;
    target->takeDamage(battleSpellDamage);
}

void BattleMage::attack(Character* target)
{
    if (rand() % 2)
    {
        std::cout << "Preparing to perform a melee attack" << std::endl;
        performMeleeAttack(target);
    }
    else
    {
        std::cout << "Preparing to perform a magic attack" << std::endl;
        try{
            castSpell(target);
        }catch(NoManaException){
            std::cout << "Magic attack failed, preparing to perform a melee attack" 
            << std::endl;
            performMeleeAttack(target);
        }
    }
}

void Rogue::backstab(Character* target)
{
    if (typeid(*target) == typeid(Mage) || typeid(*target) == typeid(BattleMage))
    {
        std::cout << "Backstab didn't succed" << std::endl;
    }
    else{
        target->takeDamage(backstabDamage);
    }
}

void Rogue::performMeleeAttack(Character* target)
{
    std::cout << "Melee damage outgoing: " << basicAttackDamage << std::endl;
    target->takeDamage(basicAttackDamage);
}

void Rogue::attack(Character* target)
{
    if (rand() % 2)
    {
        std::cout << "Preparing to perform a back stab attack" << std::endl;
        backstab(target);
    }
    else
    {
        std::cout << "Preparing to perform a melee attack" << std::endl;
        performMeleeAttack(target);
    }
}
