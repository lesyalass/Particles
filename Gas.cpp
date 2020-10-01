#include "TXLib.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

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

void drawSphere(Sphere* sphere)
{
    for (int i = 0; i < sphere->Gradient; i++)
    {
        int X = sphere->position.X + sphere->Radius * i / 3 / sphere->Gradient;
        int Y = sphere->position.Y + sphere->Radius * i / 2 / sphere->Gradient;

        txSetFillColor(RGB(i * sphere->redRate / sphere->Gradient, i * sphere->greenRate / sphere->Gradient, i * sphere->blueRate / sphere->Gradient));
        txSetColor    (RGB(i * sphere->redRate / sphere->Gradient, i * sphere->greenRate / sphere->Gradient, i * sphere->blueRate / sphere->Gradient));
        txCircle(sphere->position.X, sphere->position.Y, sphere->Radius - sphere->Radius * i / sphere->Gradient);
    }
}

void moveSphere(Sphere *sphere, float dt)
{
    sphere->position.X += sphere->velocity.X * dt;
    sphere->position.Y += sphere->velocity.Y * dt;
}

bool checkCollisionTwoSpheres(Sphere* sphere1, Sphere* sphere2)
{
    if (sphere1->Radius + sphere2->Radius > sqrt(pow(sphere1->position.X - sphere2->position.X, 2)+ pow(sphere1->position.Y - sphere2->position.Y, 2)))
    {
        return true;
    }
    return false;
}

void collisionSphereWall(Sphere* sphere, int screenSizeX, int screenSizeY)
{
    if (sphere->position.X > screenSizeX - sphere->Radius || sphere->position.X < sphere->Radius)
        {
            sphere->velocity.X = - sphere->velocity.X;
        }

    if (sphere->position.Y > screenSizeY - sphere->Radius || sphere->position.Y < sphere->Radius)
        {
            sphere->velocity.Y = - sphere->velocity.Y;
        }
}


float projectionVector( float vectorX, float vectorY, float axisX, float axisY)
{
    float scalarComposition = vectorX * axisX + vectorY * axisY;
    float moduleAxis = pow (axisX * axisX + axisY * axisY, 0.5 );
    float projection = scalarComposition / moduleAxis;
    return projection;
}

void changeVelocitySphere(Sphere* sphere1, Sphere* sphere2)
{
    float axisX = sphere1->position.X - sphere2->position.X;
    float axisY = sphere1->position.Y - sphere2->position.Y;
    float moduleAxis = pow (axisX * axisX + axisY * axisY, 0.5 );
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
    int screenSizeY = 600;

    float dt = 1;
    Sphere particles[100];

    txCreateWindow(screenSizeX, screenSizeY);
    txSetColor(RGB(0, 0, 0));


    while(true)
    {
        for (int i = 0; i < 100; i++)
        {
            moveSphere(&particles[i], dt);
        }


        for (int i = 0; i < 100; i++)

        {
            txBegin();
            drawSphere(&particles[i]);
            txEnd();
            cout « “Object coords “ « &particles[i].X « “ “ « &particles[i].Y;
        }

        txClear();
        for (int i = 0; i < 100; i++)
        {
            collisionSphereWall(&particles[i], screenSizeX, screenSizeY);
        }


        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (checkCollisionTwoSpheres(&particles[i], &particles[j]))
                {
                    changeVelocitySphere(&particles[i], &particles[j]);
                }
            }
        }
    }

return 0;
}

