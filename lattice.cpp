#include <iostream>
#include "lattice.h"

Lattice::Lattice(int dimension, double basisVectors)
{
    setDimension(int dimension);
    if basisVectors.size() == dimension
    {
        setBasisVectors(double basisVectors);
    }
    else
    {
        std::cout << "Size of array basis vectors is not equal to the dimension of the lattice! Could not construct lattice." << std::endl;
        return;
    }
}

void Lattice::setDimension(int dimension)
{
    mDimension = dimension;
}

void Lattice::setBasisVectors(double basisVectors)
{   
    if basisVectors.size() == mDimension
    {
        mBasisVectors = basisVectors;
    }
    else
    {
        std::cout << "Could not set new basis vectors. Dimension of given array is not equal to dimension of lattice." << std::endl;
        return;
    }
}

int Lattice::getDimension()
{
    return mDimension;
}

double Lattice::getBasisVectors()
{
    return mBasisVectors;
}
