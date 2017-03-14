#include <SFML/Graphics.hpp>
#include <iostream>

#define WIDE 800
#define HIGH 600

#define TILESIZE 64

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"Adventure!");

  sf::Texture crab_texture;
  if(!crab_texture.loadFromFile("Assets/crabEnemy.png"))
  {
    std::cout << "Error loading crab texture!" << std::endl;
  }
  sf::Sprite crab;
  crab.setTexture(crab_texture);
  crab.setScale(sf::Vector2f(4,4));
  crab.setPosition(100,100);

  sf::Font font;
  if(!font.loadFromFile("Assets/ARCADECLASSIC.TTF"))
  {
    std::cout << "Error loading font!" << std::endl;
  }
  sf::Text livesDisp;
  livesDisp.setFont(font);
  livesDisp.setCharacterSize(24);
  livesDisp.setColor(sf::Color::White);

  sf::Texture hero_texture;
  if(!hero_texture.loadFromFile("Assets/hero.png"))
  {
    std::cout << "Error loading hero texture!" << std::endl;
  }

  sf::Sprite hero;
  hero.setTexture(hero_texture);
  hero.setScale(sf::Vector2f(4,4));

  sf::Texture wall_texture;
  if(!wall_texture.loadFromFile("Assets/object.png"))
  {
    std::cout << "Error loading wall texture!" << std::endl;
  }

  sf::Sprite wall;
  wall.setTexture(wall_texture);
  wall.setScale(sf::Vector2f(4,4));
  wall.setPosition(100,200);

  int circleDirection = 0;

  double heroSpeed = 1;

  int lives = 10;
  bool takingDamage = false;

  //Game Loop
  while(window.isOpen())
  {
    //Handles Events
    sf::Event event;
    while(window.pollEvent(event))
    {
      //Close Events
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && hero.getPosition().y > 0)
    {
      hero.move(0,-heroSpeed);
      if(hero.getGlobalBounds().intersects(wall.getGlobalBounds()))
      {
        hero.move(0,heroSpeed);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getPosition().y < HIGH-TILESIZE)
    {
      hero.move(0,heroSpeed);
      if(hero.getGlobalBounds().intersects(wall.getGlobalBounds()))
      {
        hero.move(0,-heroSpeed);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hero.getPosition().x < WIDE-TILESIZE)
    {
      hero.move(heroSpeed,0);
      if(hero.getGlobalBounds().intersects(wall.getGlobalBounds()))
      {
        hero.move(-heroSpeed,0);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hero.getPosition().x > 0)
    {
      hero.move(-heroSpeed,0);
      if(hero.getGlobalBounds().intersects(wall.getGlobalBounds()))
      {
        hero.move(heroSpeed,0);
      }
    }

    if(hero.getGlobalBounds().intersects(crab.getGlobalBounds()))
    {
      if(takingDamage == false)
      {
        lives --;
        takingDamage = true;
      }
    }
    else
    {
      takingDamage = false;
    }

    livesDisp.setString(std::to_string(lives));

    window.clear(sf::Color::Black);

    //update stuff - This is Aaron
    if(circleDirection == 0)
    {
      crab.move(0.5,0);
    }
    else
    {
      crab.move(-0.5,0);
    }
    if(crab.getPosition().x > 760)
    {
      circleDirection = 1;
    }
    if(crab.getPosition().x < 0)
    {
      circleDirection = 0;
    }

    //render - This is Max
    window.draw(crab);
    window.draw(wall);
    window.draw(hero);
    window.draw(livesDisp);
    window.display();
  }
}
