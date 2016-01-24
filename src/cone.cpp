#include <iostream>
#include <vector>
#include "cone.h"

Cone::Cone(std::vector<std::vector<double> > _basisVectors)
{
    basisVectors = _basisVectors;
    return;
}

Cone::~Cone(){}

void Cone::setBasisVectors(std::vector<std::vector<double> > _basisVectors)
{   
        basisVectors = _basisVectors;
}

std::vector<std::vector<double> > Cone::getBasisVectors()
{
    return basisVectors;
}
