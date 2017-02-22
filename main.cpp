#include <SFML/Graphics.hpp>

#define WIDE 800
#define HIGH 600

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"Adventure!");

  sf::CircleShape circle(100);
  circle.setFillColor(sf::Color::White);
  circle.setPosition(100,100);

  int circleDirection = 0;

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
    window.clear(sf::Color::Black);

    //update stuff - This is Aaron
    if(circleDirection == 0)
    {
      circle.move(0.1,0);
    }
    else
    {
      circle.move(-0.1,0);
    }
    if(circle.getPosition().x > 600)
    {
      circleDirection = 1;
    }
    if(circle.getPosition().x < 0)
    {
      circleDirection = 0;
    }

    //render - This is Max
    window.draw(circle);
    window.display();
  }
}
