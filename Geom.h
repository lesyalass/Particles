#pragma once
#include <cmath>

struct Vector
{
    float X;
    float Y;

    float projectionVector( Vector axis)
    {
        float scalarProduct = X * axis.X + Y * axis.Y;
        float moduleAxis = axis.EuclidNorm();
        float projection = scalarProduct / moduleAxis;
        return projection;
    }

    Vector operator+ (const Vector& other) const
    {
        return {this->X + other.X, this->Y + other.Y};
    }

    Vector operator-(const Vector& other) const
    {
        return {this->X - other.X, this->Y - other.Y};
    }

    Vector operator* (const float& k) const
    {
        return {this->X * k, this->Y * k};
    }

    float EuclidNorm() const
    {
        return std::sqrt(X * X + Y * Y);
    }
};
