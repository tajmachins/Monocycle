#pragma once
#include <string>
#include <stdexcept>

class NoManaException : public std::exception
{
public:
    const char* what() const noexcept override;
};

class Character
{
    std::string name;
    int health;
    int maxHealth;
public:
    Character(std::string name, int health = 100) : name(name), health(health), 
        maxHealth(health) {}
    std::string getName();
    int getHealth();
    bool isAlive();
    void takeDamage(int damage);
    void heal(int heal);
    virtual void attack(Character* target) = 0; 
};

class CanUseMelee
{
    virtual void performMeleeAttack(Character* target) = 0;
};

class Warrior : public Character, public CanUseMelee 
{
    int meleeDamage;
public:
    Warrior(const std::string& name, int health = 120, int damage = 15) : 
        meleeDamage(damage), Character(name, health) {} 
    void attack(Character* target) override;
    void performMeleeAttack(Character* target) override;
};

class CanCastSpells
{
    int mana;
    int maxMana;
public:
    int getMana();
    void addMana(int amount);
    void useMana(int amount);
    virtual void castSpell(Character* target) = 0;
    CanCastSpells(int mana) : mana(mana), maxMana(mana) {}
    virtual ~CanCastSpells() = default;
};

class Mage : public Character, public CanCastSpells
{
    int spellDamage;
public:
    Mage(const std::string& name, int health = 80, int mana = 150, 
        int damage = 20) : spellDamage(damage), Character(name, health), 
        CanCastSpells(mana) {} 
    void attack(Character* target) override;
    void castSpell(Character* target) override;
};

class BattleMage : public Character, public CanCastSpells, public CanUseMelee
{
    int battleSpellDamage;
    int battleMeleeDamage;
public:
    BattleMage(std::string name, int health = 100, int mana = 100,
        int meleeDmg = 10, int spellDmg = 15) : Character(name, health), 
        CanCastSpells(mana), battleSpellDamage(spellDmg), battleMeleeDamage(meleeDmg) {}
    void attack(Character* target) override;
    void castSpell(Character* target) override;
    void performMeleeAttack(Character* target) override;
};

class Rogue : public Character, public CanUseMelee
{
    int basicAttackDamage;
    int backstabDamage;
public:
    Rogue(std::string name, int health = 90, int basicDmg = 12, 
        int backstabDmg = 30) : Character(name, health), basicAttackDamage(basicDmg),
        backstabDamage(basicDmg) {}
    void backstab(Character* target);
    void performMeleeAttack(Character* target) override;
    void attack(Character* target) override;
};
