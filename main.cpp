#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define WIDE 800
#define HIGH 640

#define TILESIZE 32

bool testColl(sf::Sprite a, sf::Sprite b)
{
  return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

bool testWallColl(sf::Sprite a, std::vector<sf::Sprite> walls)
{
  for(int i=0; i<walls.size(); i++)
  {
    if(a.getGlobalBounds().intersects(walls[i].getGlobalBounds()))
    {
      return true;
    }
  }
  return false;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"Adventure!");

  int tileW = WIDE/TILESIZE;
  int tileH = HIGH/TILESIZE;

  std::vector<std::vector<bool> > map;

  for(int i=0; i<tileH; i++)
  {
    std::vector<bool> temp;
    for(int j=0; j<tileW; j++)
    {
      temp.push_back(false);
    }
    map.push_back(temp);
  }

  map[3][3] = true;
  map[4][6] = true;
  map[9][14] = true;
  
  for(int i=3; i<14; i++)
  {
  	if(i % 3 != 0)
  	{
  		map[i][3] = true;
  	}
  	
  	map[2][i] = true;
  }
  
  for(int i=1; i<21; i++)
  {
  	map[1][i] = true;
  }

  for(int i=0; i<map.size(); i++)
  {
    for(int j=0; j<map[i].size(); j++)
    {
      if(map[i][j] == true)
      {
        std::cout << '0';
      }
      else
      {
        std::cout << ' ';
      }
    }
    std::cout << std::endl;
  }

  sf::Texture crab_texture;
  if(!crab_texture.loadFromFile("Assets/crabEnemy.png"))
  {
    std::cout << "Error loading crab texture!" << std::endl;
  }
  sf::Sprite crab;
  crab.setTexture(crab_texture);
  crab.setScale(sf::Vector2f(2,2));

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
  hero.setScale(sf::Vector2f(2,2));

  sf::Texture wall_texture;
  if(!wall_texture.loadFromFile("Assets/object.png"))
  {
    std::cout << "Error loading wall texture!" << std::endl;
  }

  std::vector<sf::Sprite> wallArr;
  for(int i=0; i<map.size(); i++)
  {
    for(int j=0; j<map[i].size(); j++)
    {
      if(map[i][j] == true)
      {
        sf::Sprite temp;
        temp.setTexture(wall_texture);
        temp.setScale(sf::Vector2f(2,2));
        temp.setPosition(j*TILESIZE,i*TILESIZE);
        wallArr.push_back(temp);
      }
    }
  }

  sf::Texture ground_texture;
  if(!ground_texture.loadFromFile("Assets/ground.png"))
  {
    std::cout << "Error loading ground texture!" << std::endl;
  }

  sf::Sprite ground;
  ground.setTexture(ground_texture);
  ground.setScale(sf::Vector2f(2,2));

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
      if(testWallColl(hero, wallArr))
      {
        hero.move(0,heroSpeed);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getPosition().y < HIGH-TILESIZE)
    {
      hero.move(0,heroSpeed);
      if(testWallColl(hero, wallArr))
      {
        hero.move(0,-heroSpeed);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hero.getPosition().x < WIDE-TILESIZE)
    {
      hero.move(heroSpeed,0);
      if(testWallColl(hero, wallArr))
      {
        hero.move(-heroSpeed,0);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hero.getPosition().x > 0)
    {
      hero.move(-heroSpeed,0);
      if(testWallColl(hero, wallArr))
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

    //update stuff - This is me
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
    for(int i=0; i<tileH ; i++)
    {
      for(int j=0; j<tileW ; j++)
      {
        ground.setPosition(j*TILESIZE, i*TILESIZE);
        window.draw(ground);
      }
    }

    window.draw(crab);
    for(int i=0; i<wallArr.size(); i++)
    {
      window.draw(wallArr[i]);
    }
    window.draw(hero);
    window.draw(livesDisp);
    window.display();
  }
}
