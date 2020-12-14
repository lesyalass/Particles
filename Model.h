#pragma once

#include "Geom.h"
#include <iostream>
#include <cstdlib>

struct Sphere
{
    Vector position;
    Vector velocity;
    float radius;
    float mass;
};

class Model
{
    public:
        Model();
        Model(int width, int height, int sphereNumber, float deltaT);
        Model& operator=(const Model& other);
        ~Model();
        void Update();
        Vector GetSpherePosition(int sphereID);
        float GetSphereRadius(int sphereID);
        int GetSpheresNumber();
    private:
        void CollideSphereWall(int sphereID);
        bool CheckCollisionTwoSpheres(int sphereID1, int sphereID2);
        void CollideTwoSpheres(int sphereID1, int sphereID2);

        Sphere *spheres;
        int boxSizeX;
        int boxSizeY;
        float dt;
        int sphereN;
};



