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
        std::vector<std::string> players;
    fin.open("players.txt"); 
  
    while (fin) { 
        getline(fin, line); 
        players.push_back(line);
    } 
    players.pop_back();
    fin.close(); 


    sf::Font font;
    font.loadFromFile("ARIAL.TTF");
    sf::Text text,playerText;
    text.setFont(font);
    playerText.setFont(font);
    playerText.setPosition(120,0);

    sf::String playerInput;


    text.setCharacterSize(40);
    text.setStyle(sf::Text::Bold);


    sf::RenderWindow app(sf::VideoMode(520, 420), "Arkanoid!");
    app.setFramerateLimit(60);

    sf::Texture t1,t2,t3,t4,t5;
    t1.loadFromFile("images/block01.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");
    t5.loadFromFile("images/select.png");


    sf::Sprite sBackground(t2), sBall(t3), sPaddle(t4), select(t5);
    sPaddle.setPosition(300,440);
    select.setPosition(100,0);

    sf::Sprite block[100];

    int n=0;
    for (int i=1;i<=10;i++)
    for (int j=1;j<=10;j++)
      {
        block[n].setTexture(t1);
        block[n].setPosition(i*42,j*20);
        n++;
      }
    

  float dx=2, dy=-3;
	float x=300, y=300;
  int px=280,py=410,dp=5;
  bool play = false,beginGame = false;
  int shift = 0, len = players.size();
  float option = 0;
          std::cout << len << "\n";
              

    while (app.isOpen())
    {
      

          sf::Event e;
          while (app.pollEvent(e))
          {
            
            if (e.type == sf::Event::Closed)
              app.close();
            if(play == false){
              if(option == 0 && shift == 0 && e.type == sf::Event::TextEntered){
                if(e.text.unicode < 128){
                  playerInput = playerInput + e.text.unicode;
                  playerText.setString(playerInput);
                }
              }

              switch(e.key.code){
                case sf::Keyboard::Down:{
                  if(option-shift<len){
                    if(option>4){
                      shift--;
                    }else{
                      option = option + 1;
                      std::cout << option << "\n";
                      int yPos = option*70;
                      select.setPosition(100,yPos);
                      if(yPos>0){
                        playerInput = "";
                        playerText.setString(playerInput);
                      }
                    }
                  }
                  break;
                }
                case sf::Keyboard::Up:{
                  if(option>0){
                    option = option - 1;
                    std::cout << option << "\n";
                    int yPos = option*70;
                    select.setPosition(100,yPos);
                  }else{
                    if(shift<0)
                    shift++;
                  }
                  break;
                }
              }

              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                std::string name =playerInput;
                if(option == 0){
                  players.push_back(name);
                  std::ofstream fout("players.txt",std::ios::app);
                  fout << name <<"\n";
                  len++;
                  fout.close();
                }
                y = 350,dy = -abs(dy);
                play = true;
                beginGame = true;
                sPaddle.setPosition(px,py);
              }
            }
          }

                app.clear();
                app.draw(select);


      
    if(play == false){
      app.draw(playerText);
      for(int i=0;i<len;i++){
        text.setString(players[i]);
        text.setPosition(120,(shift+i+1)*75);
        app.draw(text);
      }
    }else{
            if(beginGame == true){
              int n=0;
              for (int i=1;i<=10;i++)
              for (int j=1;j<=10;j++)
                {
                  block[n].setTexture(t1);
                  block[n].setPosition(i*42,j*20);
                  n++;
                }
                beginGame = false;
            }
            x+=dx;
            for (int i=0;i<n;i++)
            if ( sf::FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
                {block[i].setPosition(-100,0); dx=-dx;}

            y+=dy;
            for (int i=0;i<n;i++)
            if ( sf::FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
                {block[i].setPosition(-100,0); dy=-dy;}

            if (x<0 || x>510)  dx=-dx;
            if (y<0 || y>450)  dy=-dy;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
              if(px<430){
                px = px+dp;
                sPaddle.setPosition(px,py);
              }
            } 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
              if(px>0){
              px = px - dp;
              sPaddle.setPosition(px,py);
              }
            }

          if ( sf::FloatRect(x,y,12,12).intersects(sPaddle.getGlobalBounds()) ) dy=-(rand()%3 + 2);


          if(y>420){
            shift = 0;
            std::cout << "here\n";
            playerInput = "";
            playerText.setString(playerInput);
            play = false;
          }
          

          sBall.setPosition(x,y);

            app.clear();
            app.draw(sBackground);
            app.draw(sBall);
            app.draw(sPaddle);

            for (int i=0;i<n;i++)
            app.draw(block[i]);
    }

    app.display();
    }

  return 0;
}
