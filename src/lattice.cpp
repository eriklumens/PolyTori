#include <iostream>
#include <vector>
#include "lattice.h"
using namespace std;

Lattice::Lattice(int _dimension, std::vector<std::vector<double> > _basisVectors)
{
    //if ((sizeof(_basisVectors)/sizeof(_basisVectors[0])) == _dimension)
    //{
        Lattice::setDimension(_dimension);
        Lattice::setBasisVectors(_basisVectors);
    //}
    //else
    //{
    //    std::cout << "Size of array basis vectors is not equal to the dimension of the lattice! Could not construct lattice." << std::endl;
    //    std::cout << "Size of array basis vectors = " << sizeof(_basisVectors) << std::endl;
    //    std::cout << "Dimension of the lattice = " << _dimension << std::endl;
    //    return;
    //}
}

Lattice::~Lattice(){}

void Lattice::setDimension(int _dimension)
{
    dimension = _dimension;
}

void Lattice::setBasisVectors(std::vector<std::vector<double> > _basisVectors)
{   
    //if (sizeof(basisVectors) == dimension)
    //{
        basisVectors = _basisVectors;
    //}
    //else
    //{
    //    std::cout << "Could not set new basis vectors. Dimension of given array is not equal to dimension of lattice." << std::endl;
    //    return;
    //}
}

int Lattice::getDimension()
{
    return dimension;
}

std::vector<std::vector<double> > Lattice::getBasisVectors()
{
    return basisVectors;
}
