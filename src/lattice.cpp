#include <iostream>
#include <vector>
#include "lattice.h"
using namespace std;

Lattice::Lattice(int _dimension, std::vector<std::vector<double> > _basisVectors)
{
    if ((unsigned) _dimension == _basisVectors.size())
    {
        Lattice::setDimension(_dimension);
        Lattice::setBasisVectors(_basisVectors);
        return;
    }
    else
    {
        std::cout << "Size of array basis vectors is not equal to the dimension of the lattice! Could not construct lattice." << std::endl;
        std::cout << "Size of array basis vectors = " << _basisVectors.size() << std::endl;
        std::cout << "Dimension of the lattice = " << _dimension << std::endl;
        return;
    }
}

Lattice::~Lattice(){}

void Lattice::setDimension(int _dimension)
{
    dimension = _dimension;
}

void Lattice::setBasisVectors(std::vector<std::vector<double> > _basisVectors)
{   
    if ((unsigned)_basisVectors.size() == dimension)
    {
        basisVectors = _basisVectors;
    }
    else
    {
        std::cout << "Could not set new basis vectors. Dimension of given array is not equal to dimension of lattice." << std::endl;
        return;
    }
}

int Lattice::getDimension()
{
    return dimension;
}

std::vector<std::vector<double> > Lattice::getBasisVectors()
{
    return basisVectors;
}
