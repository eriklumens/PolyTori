#include <iostream>
#include 'polytope.h'

Polytope::Polytope(int _vertices, Lattice* _lattice)
{
    vertices = _vertices;
    lattice = _lattice;
}

Polytope::~Polytope(){}

void Polytope::setVertices(int _vertices)
{
    vertices = _vertices;
}

void Polytope::setLattice(Lattice* _lattice)
{
    lattice = _lattice;
}

int Polytope::getVertices()
{
    return vertices;
}

int Polytope::getNrOfVertices()
{
    return vertices.size();
}

Lattice* Polytope::getLattice()
{
    return lattice;
}

void Polytope::drawPolytope()
{
    return;
}
