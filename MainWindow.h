#pragma once
#include <SFML/Graphics.hpp>
#include "Model.h"

class MainWindow
{
    public:
        MainWindow() = default;
        MainWindow(int width, int height, int sphereNumber);
        ~MainWindow();
        int Start();
    private:
        void UpdateWindow();
        void UpdateModel();
        sf::RenderWindow *window;
        sf::Texture texture;
        sf::CircleShape *circles;
        Model model;

}; 