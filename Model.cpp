#include "Model.h"


Model::Model(int width, int height, int sphereNumber, float deltaT)
{
    srand(1234);
    boxSizeX = width;
    boxSizeY = height;
    sphereN = sphereNumber;
    dt = deltaT;
    spheres = new Sphere[sphereN];

    for(int i = 0; i < sphereN; i++)
    {
        spheres[i].radius = 40;
        spheres[i].position = Vector{(2 * spheres[i].radius + 10) * i + spheres[i].radius + 10,  (2 * spheres[i].radius + 10) * i + spheres[i].radius + rand() % (int)spheres[i].radius };
        spheres[i].velocity = Vector{(float) (rand() % 20),(float) (rand() % 20)};
        spheres[i].mass = 100.0;

    }
}

Model::~Model()
{
    delete[] spheres;
}

Model::Model()
{
    spheres = nullptr;
}


Model& Model::operator=(const Model& other)
{
    if (this != &other)
    {
        this->boxSizeX = other.boxSizeX;
        this->boxSizeY = other.boxSizeY;
        this->dt = other.dt;
        this->sphereN = other.sphereN;
        if (spheres != nullptr)
        {
            delete[] spheres;
        }
        spheres = new Sphere[sphereN];

        for(int i = 0; i < sphereN; i++)
        {
            spheres[i] = other.spheres[i];
        }
    }
    return *this;
}

void Model::Update()
{
    for (int i = 0; i < sphereN; i++)
    {
        CollideSphereWall(i);
    }

    for (int i = 0; i < sphereN; i++)
    {
        for (int j = i + 1; j < sphereN; j++)
        {
            CollideTwoSpheres(i, j);
        }
    }

    for(int i = 0; i < sphereN; i++)
    {
        spheres[i].position.X += spheres[i].velocity.X * dt;
        spheres[i].position.Y += spheres[i].velocity.Y * dt;
    }
}

Vector Model::GetSpherePosition(int sphereID)
{
    return spheres[sphereID].position;
}

float Model::GetSphereRadius(int sphereID)
{
    return spheres[sphereID].radius;
}

int Model::GetSpheresNumber()
{
    return sphereN;
}

bool Model::CheckCollisionTwoSpheres(int sphereID1, int sphereID2)
 {
    if ((spheres[sphereID1].radius + spheres[sphereID2].radius) > (spheres[sphereID1].position - spheres[sphereID2].position).EuclidNorm())
    {
        return true;
    }
    return false;
 }

 void Model::CollideSphereWall(int sphereID)
 {
     if (spheres[sphereID].position.X > boxSizeX - spheres[sphereID].radius || spheres[sphereID].position.X < spheres[sphereID].radius)
     {
         spheres[sphereID].velocity.X = - spheres[sphereID].velocity.X;
     }

     if (spheres[sphereID].position.Y > boxSizeY - spheres[sphereID].radius || spheres[sphereID].position.Y < spheres[sphereID].radius)
     {
         spheres[sphereID].velocity.Y = - spheres[sphereID].velocity.Y;
     }
 }

 void Model::CollideTwoSpheres(int sphereID1, int sphereID2)
 {
     if (sphereID1 != sphereID2 && CheckCollisionTwoSpheres(sphereID1, sphereID2))
     {
         Vector axis = spheres[sphereID1].position - spheres[sphereID2].position;
         float moduleAxis = axis.EuclidNorm();
         float projectionVelocity1 = spheres[sphereID1].velocity.projectionVector(axis);
         float projectionVelocity2 = spheres[sphereID2].velocity.projectionVector(axis);
         float dv = projectionVelocity1 - projectionVelocity2;

         if(dv < 0)
         {
             spheres[sphereID1].velocity = spheres[sphereID1].velocity + axis * -dv * (1 / moduleAxis);
             spheres[sphereID2].velocity = spheres[sphereID2].velocity + axis * dv * (1 / moduleAxis);
         }
      }

 }


