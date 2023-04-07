#pragma once

class Node
{
private:
public:
    double X;
    double Y;
    double Z;

    Node(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }
    ~Node()
    {
    }
};
