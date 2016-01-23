#include <iostream>
#include <vector>
#include "polytope.h"

int main()
{
    //set up basisvectors
    std::vector<std::vector<double> > basis(2,std::vector<double>(2));
    basis[1][1] = 2;
    basis[1][0] = 0;
    basis[0][1] = 0;
    basis[0][0] = 2;
    
    //define two dimensional lattice
    Lattice myLattice(2,basis);
    
    //set up polytope vertices
    std::vector<std::vector<double> > projTwo(3,std::vector<double>(2));
    projTwo[2][1] = -1;
    projTwo[2][0] = -1;
    projTwo[1][1] = 0;
    projTwo[1][0] = 1;
    projTwo[0][1] = 1;
    projTwo[0][0] = 0;
    
    //define polytope
    Polytope myPolytope(projTwo,myLattice);
    
    //show the values of the vertices given the basis vectors
    std::cout << myPolytope.getVerticesInLattice()[2][0] << std::endl;
    std::cout << myPolytope.getVerticesInLattice()[2][1] << std::endl;
    std::cout << myPolytope.getVerticesInLattice()[1][0] << std::endl;
    std::cout << myPolytope.getVerticesInLattice()[1][1] << std::endl;
    std::cout << myPolytope.getVerticesInLattice()[0][0] << std::endl;
    std::cout << myPolytope.getVerticesInLattice()[0][1] << std::endl;
    
    //show the value of the direction of a line between two vertices
    std::cout << "begin x: "<< std::endl;
    std::vector<std::vector<Line> > myLines = myPolytope.getLinesBetweenVertices();
    std::cout << "begin x: "<< std::endl;
    Line myLine(myLines[0][1]);
    std::cout << "begin x: "<< std::endl;
     
    std::cout << "direction x: "<< myLine.getDirection()[0] << std::endl;
    std::cout << "direction y: "<< myLine.getDirection()[1] << std::endl;
    std::cout << "begin x: "<< std::endl;
    std::cout << "begin y: "<< std::endl;
    std::cout << "end x: "<< std::endl;
    std::cout << "end y: "<< std::endl;
    
    return 0;
}
