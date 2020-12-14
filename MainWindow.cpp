#include "MainWindow.h"

MainWindow::MainWindow(int width, int height, int sphereNumber)
{
    window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML Works!");
    model = Model(width, height, sphereNumber, 0.01);
    circles = new sf::CircleShape[sphereNumber];
    texture.loadFromFile("../sphere.png");
    for(int i = 0; i < sphereNumber; i++)
    {
        circles[i].setTexture(&texture);
        circles[i].setFillColor(sf::Color(255, 100, 255));
    }
}

MainWindow::~MainWindow()
{
    delete[] circles;
    delete window;
}

int MainWindow::Start()
{
    int step = 0;
    while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
            {
                window->close();
            }
		}
        UpdateWindow();
        UpdateModel();
        step += 1;
	}
    return 0;
}

void MainWindow::UpdateModel()
{
    model.Update(); 
}

void MainWindow::UpdateWindow()
{
    window->clear(sf::Color(250, 220, 100, 0));
    int spheresNumber = model.GetSpheresNumber();
    for (int i = 0; i < spheresNumber; i++)
    {
        Vector pos = model.GetSpherePosition(i);
        float radius = model.GetSphereRadius(i);
        circles[i].setRadius(radius);
        circles[i].setPosition(pos.X - radius, pos.Y - radius);        
        window->draw(circles[i]);
    }
    window->display();
}