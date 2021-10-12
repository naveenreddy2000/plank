#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <time.h>

int main()
{
  srand(time(0));

  std::ifstream fin;
  std::string line;

  //loading font
  sf::Font font;
  font.loadFromFile("ARIAL.TTF");
  //loading text
  sf::Text text, playerText;
  text.setFont(font);
  playerText.setFont(font);
  playerText.setPosition(120, 0);

  text.setCharacterSize(40);
  text.setStyle(sf::Text::Bold);

  sf::RenderWindow app(sf::VideoMode(520, 420), "Arkanoid!");
  app.setFramerateLimit(60);

  //Images required are embded
  sf::Texture t1, t2, t3, t4, t5;
  t1.loadFromFile("images/block01.png");
  t2.loadFromFile("images/background.jpg");
  t3.loadFromFile("images/ball.png");
  t4.loadFromFile("images/paddle.png");
  t5.loadFromFile("images/select.png");

  sf::Sprite sBackground(t2), sBall(t3), sPaddle(t4), select(t5);
  sPaddle.setPosition(300, 440);
  select.setPosition(100, 100);

  sf::Sprite block[100];

  //setting up the start of the game
  int n = 0;
  for (int i = 1; i <= 10; i++)
    for (int j = 1; j <= 10; j++)
    {
      block[n].setTexture(t1);
      block[n].setPosition(i * 42, j * 20);
      n++;
    }

  // speed of ball
  float dx = 2, dy = -3;
  // initial position of ball
  float x = 300, y = 300;
  int px = 280, py = 410, dp = 5;
  bool play = false, beginGame = false;
  int shift = 0;
  float option = 0;

  // game loop
  while (app.isOpen())
  {

    sf::Event e;
    // capturing event from the player
    while (app.pollEvent(e))
    {

      if (e.type == sf::Event::Closed)
        app.close();
      if (play == false)
      {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
          y = 350, dy = -abs(dy);
          play = true;
          beginGame = true;
          sPaddle.setPosition(px, py);
        }
      }
    }

    app.clear();
    app.draw(select);

    // game on/off condition
    if (play == false)
    {
      text.setString("Press Enter!");
      text.setPosition(140, 100);
      app.draw(text);
    }
    else
    {
      if (beginGame == true)
      {
        int n = 0;
        for (int i = 1; i <= 10; i++)
          for (int j = 1; j <= 10; j++)
          {
            block[n].setTexture(t1);
            block[n].setPosition(i * 42, j * 20);
            n++;
          }
        beginGame = false;
      }
      x += dx;
      for (int i = 0; i < n; i++)
        if (sf::FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
        {
          block[i].setPosition(-100, 0);
          dx = -dx;
        }

      y += dy;
      for (int i = 0; i < n; i++)
        if (sf::FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
        {
          block[i].setPosition(-100, 0);
          dy = -dy;
        }

      if (x < 0 || x > 510)
        dx = -dx;
      if (y < 0 || y > 450)
        dy = -dy;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
        if (px < 430)
        {
          px = px + dp;
          sPaddle.setPosition(px, py);
        }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
        if (px > 0)
        {
          px = px - dp;
          sPaddle.setPosition(px, py);
        }
      }

      if (sf::FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds()))
        dy = -(rand() % 3 + 2);

      if (y > 420)
      {
        shift = 0;
        std::cout << "here\n";
        play = false;
      }

      sBall.setPosition(x, y);

      app.clear();
      app.draw(sBackground);
      app.draw(sBall);
      app.draw(sPaddle);

      for (int i = 0; i < n; i++)
        app.draw(block[i]);
    }

    app.display();
  }

  return 0;
}
