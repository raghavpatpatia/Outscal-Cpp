#include <iostream>

class Player
{
private:
  int health = 100;
  int bullets = 10;
public:
  void Shoot()
  {
    bullets--;
    std::cout << "Bullets left: " << bullets << std::endl;
  }
  int TakeDamage(int damage)
  {
    health = health - damage;
    return health;
  }
  int ReviveHealth(int value)
  {
    health += value;
    return health;
  }
};

int main() {
  Player player;
  std::cout << player.TakeDamage(20) << std::endl;
  std::cout <<player.ReviveHealth(5) << std::endl;
  player.Shoot();
}