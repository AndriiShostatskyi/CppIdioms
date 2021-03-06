#include <iostream>
#include <memory>
#include <stdexcept>

/*
 * Resource Return 
 * It indicates the transfer of ownership of a resource explicitly 
 * in the return type of a factory function. 
 * It's used together with RAII idiom and helps avoid situations 
 * when a caller is implcitly responsible for a resource and prevents 
 * possible resource leakage. It should be used in functions 
 * that create or build some resource and return it to the caller.
 */

class Weapon {
public:
    virtual ~Weapon() = default;
    virtual void shoot() = 0;
};

class AK47 : public Weapon  {
public:
    ~AK47() = default;
    void shoot() override { std::cout << "AK47" << std::endl; }
};

class M16 : public Weapon {
public:
    ~M16() = default;
    void shoot() override { std::cout << "M16" << std::endl; }
};

enum class WeaponType{ AK47, M16 };

struct WeaponFactory
{
    static std::unique_ptr<Weapon> create(const WeaponType type)
    {
        switch (type)
        {
            case WeaponType::M16:
                return std::make_unique<M16>();
            case WeaponType::AK47:
                return std::make_unique<AK47>();
            default:
                throw std::logic_error{"Invalid type"};
        }
    }
};

int main()
{
    auto weapon = WeaponFactory::create(WeaponType::AK47);
    weapon->shoot();
    return 0;
}
