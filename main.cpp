#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <math.h>

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
  map[1][3] = true;
  map[3][5] = true;

  for(int i=0; i<tileH; i++)
  {
    map[i][0] = true;
    map[i][tileW-1] = true;
  }
  for(int i=0; i<tileW; i++)
  {
    map[0][i] = true;
    map[tileH-1][i] = true;
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
  crab.setPosition(TILESIZE*6,TILESIZE);

  sf::Texture seaweed_texture;
  if(!seaweed_texture.loadFromFile("Assets/seaweedEnemy.png"))
  {
    std::cout << "Error loading seaweed texture!" << std::endl;
  }
  sf::Sprite seaweed;
  seaweed.setTexture(seaweed_texture);
  seaweed.setScale(sf::Vector2f(2,2));
  seaweed.setPosition(TILESIZE*7,TILESIZE*3);

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
  hero.setPosition(TILESIZE,TILESIZE);

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

  sf::SoundBuffer grunt_buffer;
  if(!grunt_buffer.loadFromFile("Assets/grunt.wav"))
  {
    std::cout << "Error loading grunt sound!" << std::endl;
  }

  sf::Sound grunt;
  grunt.setBuffer(grunt_buffer);
  grunt.setPitch(1.4);

  sf::SoundBuffer (music_buffer);
  if(!music_buffer.loadFromFile("Assets/Lolita Compiex.wav"))
   {
     std::cout << "Error loading music!" << std::endl;
   }

   sf::Sound music;
   music.setBuffer(music_buffer);
   music.setLoop(true);

  int enemyDirection = 0;

  double heroSpeed = 0.75;

  double homingX = 0.5;
  double homingY = 0.5;
  double homingDist = 0;

  int lives = 10;
  bool takingDamage = false;

  music.play();

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
        grunt.play();
        takingDamage = true;
      }
    }
    else
    {
      takingDamage = false;
    }

    //Put seaweed damadge here

    livesDisp.setString(std::to_string(lives));

    window.clear(sf::Color::Black);

    //update stuff - This is me
    if(enemyDirection == 0)
    {
      crab.move(0.5,0);
    }
    else
    {
      crab.move(-0.5,0);
    }
    if(crab.getPosition().x > 760)
    {
      enemyDirection = 1;
    }
    if(crab.getPosition().x < 0)
    {
      enemyDirection = 0;
    }
    if(testWallColl(crab, wallArr))
    {
      if(enemyDirection == 0)
      {
        enemyDirection = 1;
      }
      else
      {
        enemyDirection = 0;
      }
    }

    homingDist = sqrt(pow(hero.getPosition().x - seaweed.getPosition().x, 2) +
            pow(hero.getPosition().y - seaweed.getPosition().y, 2));
      homingX = (hero.getPosition().x - seaweed.getPosition().x)/homingDist;
      homingY = (hero.getPosition().y - seaweed.getPosition().y)/homingDist;
      seaweed.move(homingX/3, homingY/3);

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
    window.draw(seaweed);
    window.draw(hero);
    window.draw(livesDisp);
    window.display();
  }
}
