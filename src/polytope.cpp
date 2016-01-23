#include <iostream>
#include "polytope.h"
using namespace std;

Polytope::Polytope(int _vertices, Lattice _lattice)
{
    vertices = _vertices;
    lattice = _lattice;
}

Polytope::~Polytope(){}

void Polytope::setVertices(int _vertices)
{
    vertices = _vertices;
}

void Polytope::setLattice(Lattice _lattice)
{
    lattice = _lattice;
}

int Polytope::getVertices()
{
    return vertices;
}

int Polytope::getNrOfVertices()
{
    return sizeof(vertices);
}

Lattice Polytope::getLattice()
{
    return lattice;
}

void Polytope::drawPolytope()
{
    return;
}
