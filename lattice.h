#include <iostream>

class Lattice
{
    private:
    int mDimension;
    double mBasisVectors[mDimension];

    public:
    Lattice(int, double);
    void setDimension(int);
    void setBasisVectors(double);
    int getDimension();
    double getBasisVectors();
};
