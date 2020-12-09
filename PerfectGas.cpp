#include <SFML/Graphics.hpp>
#include <cmath>
#define N 11
 
using namespace sf; 
struct Vector
{
    float X;
    float Y;
};

struct Sphere
{
    Vector position;
    Vector velocity;
    int Radius;
    int redRate;
    int greenRate;
    int blueRate;
    int Gradient;
};

void drawSphere(Sphere* sphere, CircleShape* shapes, RenderWindow* window)
{
    for (int i = 0; i < N; i++)
    {
        shapes[i].setPosition(sphere[i].position.X, sphere[i].position.Y);
        window->draw(shapes[i]);
    }
}

void moveSphere(Sphere *sphere, float dt)
{
    sphere->position.X += sphere->velocity.X * dt;
    sphere->position.Y += sphere->velocity.Y * dt;
}

bool checkCollisionTwoSpheres(Sphere* sphere1, Sphere* sphere2)
{
    if (sphere1->Radius + sphere2->Radius > std::sqrt(std::pow(sphere1->position.X - sphere2->position.X, 2)+ std::pow(sphere1->position.Y - sphere2->position.Y, 2)))
    {
        return true;
    }
    return false;
}

void collisionSphereWall(Sphere* sphere, int screenSizeX, int screenSizeY)
{
    if (sphere->position.X > screenSizeX - 2*sphere->Radius || sphere->position.X < 0)
        {
            sphere->velocity.X = - sphere->velocity.X;
        }

    if (sphere->position.Y > screenSizeY - 2*sphere->Radius|| sphere->position.Y < 0)
        {
            sphere->velocity.Y = - sphere->velocity.Y;
        }
}

float projectionVector( float vectorX, float vectorY, float axisX, float axisY)
{
    float scalarComposition = vectorX * axisX + vectorY * axisY;
    float moduleAxis = std::pow(axisX * axisX + axisY * axisY, 0.5);
    float projection = scalarComposition / moduleAxis;
    return projection;
}

void changeVelocitySphere(Sphere* sphere1, Sphere* sphere2)
{
    float axisX = sphere1->position.X - sphere2->position.X;
    float axisY = sphere1->position.Y - sphere2->position.Y;
    float moduleAxis = std::pow(axisX * axisX + axisY * axisY, 0.5);
    float projectionVelocity1 = projectionVector( sphere1->velocity.X, sphere1->velocity.Y, axisX, axisY);
    float projectionVelocity2 = projectionVector( sphere2->velocity.X, sphere2->velocity.Y, axisX, axisY);
    float dv = projectionVelocity1 - projectionVelocity2;

    if (dv < 0)
    {
        sphere2->velocity.X +=   dv * axisX / moduleAxis;
        sphere2->velocity.Y +=   dv * axisY / moduleAxis;
        sphere1->velocity.X += - dv * axisX / moduleAxis;
        sphere1->velocity.Y += - dv * axisY / moduleAxis;
    }
}

int main()
{	
    int screenSizeX = 1000;
    int screenSizeY = 800;
    float dt = 0.1;
	RenderWindow window(VideoMode(screenSizeX, screenSizeY), "SFML Works!");
    CircleShape Circles[N];
    Sphere spheres[N];
    for (int i = 0; i < N; i++)
    {
        spheres[i].position = {(float)50*((float)i+1), (float)50*((float)i+1)};
        spheres[i].velocity = {1, 1};
        spheres[i].Radius = 30;
        spheres[i].redRate = 200;
        spheres[i].greenRate = 50;
        spheres[i].blueRate = 200;
        Circles[i].setRadius(spheres[i].Radius);
        Circles[i].setFillColor(Color(spheres[i].redRate, spheres[i].greenRate, spheres[i].blueRate));
        Circles[i].setPosition(spheres[i].position.X, spheres[i].position.Y);
    }    
    
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			window.close(); 
		}
		window.clear(Color(250, 220, 100, 0));
        for (int i = 0; i < N; i++)
        {
            moveSphere(&spheres[i], dt);
        }
        drawSphere(spheres, Circles, &window);
        
		window.display();

        for (int i = 0; i < N; i++)
        {
            collisionSphereWall(&spheres[i], screenSizeX, screenSizeY);
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (checkCollisionTwoSpheres(&spheres[i], &spheres[j]))
                {
                    changeVelocitySphere(&spheres[i], &spheres[j]);
                }
            }
        }
	}
 
	return 0;
}