#include <SFML/Graphics.hpp>
#include <iostream> // for the std::cout
#include <cstdlib> // for the abs()

int HEIGHT = 1024;
int WIDTH = 1024;

int pieceSize = 133.3;

sf::Sprite pieces[32]; // All the pieces in total

int board[8][8] =
{  -5,-4,-3,-2,-1,-3,-4,-5, 
   -6,-6,-6,-6,-6,-6,-6,-6,
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    6, 6, 6, 6, 6, 6, 6, 6,
    5, 4, 3, 2, 1, 3, 4, 5 
};

void loadBoard(){
    int count = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(count == 32) break;
            int piece = board[j][i];
            if(piece < 0){
                pieces[count].setTextureRect(sf::IntRect(pieceSize*(abs(piece)-1), 133.5, pieceSize, pieceSize));
            }
            else if (pieces > 0){
                pieces[count].setTextureRect(sf::IntRect(pieceSize*(abs(piece)-1), 0, pieceSize, pieceSize));
            }

            if(piece != 0){
                pieces[count].setPosition(WIDTH/8 * i, HEIGHT/8 * j);
                count++;
            }
        }
    }
}

void getNotation(int x, int y){
    int posX = WIDTH/8;
    int posY = HEIGHT/8; 
}

int main(){
    // The window

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Chess");
    
    sf::Texture boardTexture;
    //if(!boardTexture.loadFromFile("res/img/board2.png")){
    if(!boardTexture.loadFromFile("res/img/board2.png")){
        std::cout << "Error loading board texture!" << std::endl;
        system("pause");
    }
    sf::Sprite boardSprite(boardTexture);
    boardSprite.setScale(2, 2);

    sf::Texture pieceSet;
    //if(!pieceSet.loadFromFile("res/img/pieces.png")){
    if(!pieceSet.loadFromFile("res/img/pieces.png")){
        std::cout << "Error loading pieces texture!" << std::endl;
        system("pause");
    }
    for(int i = 0; i < 32; i++){
        pieces[i].setTexture(pieceSet);
    }
    loadBoard();

    bool pieceMoving = false;
    int difToCenterX, difToCenterY; // To center the pieces
    int saver;

    // the app loop
    while(window.isOpen()){
        
        sf::Vector2i localMousePosition = sf::Mouse::getPosition(window);

        // handle events
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                // Drag and drop the pieces
                case sf::Event::EventType::MouseButtonPressed:
                    if(sf::Mouse::Button::Left == event.mouseButton.button){
                        for(int i = 0; i < 32; i++){
                            if(pieces[i].getGlobalBounds().contains(localMousePosition.x, localMousePosition.y)){
                                pieceMoving = true;
                                difToCenterX = pieces[i].getPosition().x - localMousePosition.x;
                                difToCenterY = pieces[i].getPosition().y - localMousePosition.y;
                                saver = i;
                            }
                        }
                    }
                    break;
                case sf::Event::EventType::MouseButtonReleased:{
                    pieceMoving = false;
                    // Estas 3 linhas centram as peças
                    //sf::Vector2f p = pieces[saver].getPosition() + sf::Vector2f(pieceSize/2, pieceSize/2);
                    //sf::Vector2f newPos = sf::Vector2f(pieceSize*int(p.x/pieceSize), pieceSize*int(p.y/pieceSize));
                    //pieces[saver].setPosition(newPos);
                }
                    break;

                default:
                    break;
            }
        }

        if(pieceMoving) pieces[saver].setPosition(localMousePosition.x + difToCenterX, localMousePosition.y + difToCenterY);

        // update the game logic

        window.clear();

        // draw objects

        window.draw(boardSprite);
        for(int i = 0; i < 32; i++) window.draw(pieces[i]);

        window.display();
    }

    return 0;
}

// Usar estes comandos para compilar e dar run ao programa:
// g++ -c main.cpp
// g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system