#include <iostream>
#include <vector>
#include "polytope.h"

int main()
{
    //set up basisvectors
    std::vector<std::vector<double> > basis(2,std::vector<double>(2));
    basis[0][0] = 1;
    basis[0][1] = 0;
    basis[1][0] = 0;
    basis[1][1] = 1;
    //3DIMENSIONS
    /*std::vector<std::vector<double> > basis(3,std::vector<double>(3));
    basis[0][0] = 1;
    basis[0][1] = 0;
    basis[0][2] = 0;
    
    basis[1][0] = 0;
    basis[1][1] = 1;
    basis[1][2] = 0;
    
    basis[2][0] = 0;
    basis[2][1] = 0;
    basis[2][2] = 1;*/
    
    //define lattice
    Lattice myLattice(2,basis);
    //Lattice myLattice(3,basis);
    
    //set up polytope vertices
   
    std::vector<std::vector<double> > projTwo(3,std::vector<double>(2));
    projTwo[0][0] = -1;
    projTwo[0][1] = -1;
    projTwo[1][0] = 2;
    projTwo[1][1] = -1;
    projTwo[2][0] = -1;
    projTwo[2][1] = 2;
    
    std::vector<std::vector<double> > projTwoWeighted(3,std::vector<double>(2));
    projTwoWeighted[0][0] = -1;
    projTwoWeighted[0][1] = -1;
    projTwoWeighted[1][0] = 2;
    projTwoWeighted[1][1] = -1;
    projTwoWeighted[2][0] = -1;
    projTwoWeighted[2][1] = 1;
    
    
    //set up polytope vertices
   
    
    //SQUARE IN 3D
    /*std::vector<std::vector<double> > square(8,std::vector<double>(3));
    square[0][0] = 1;
    square[0][1] = 1;
    square[0][2] = 1;
    
    square[1][0] = -1;
    square[1][1] = 1;
    square[1][2] = 1;
    
    square[2][0] = -1;
    square[2][1] = -1;
    square[2][2] = 1;
    
    square[3][0] = 1;
    square[3][1] = -1;
    square[3][2] = 1;
    
    square[4][0] = 1;
    square[4][1] = 1;
    square[4][2] = 0;
    
    square[5][0] = -1;
    square[5][1] = 1;
    square[5][2] = 0;
    
    square[6][0] = -1;
    square[6][1] = -1;
    square[6][2] = 0;
    
    square[7][0] = 1;
    square[7][1] = -1;
    square[7][2] = 0;*/
    
    std::vector<std::vector<double> > square(4,std::vector<double>(2));
    square[0][0] = 1;
    square[0][1] = -1;
    square[1][0] = 1;
    square[1][1] = 1;
    square[2][0] = -1;
    square[2][1] = 1;
    square[3][0] = -1;
    square[3][1] = -1;
    
    //define polytope
    Polytope myPolytope(projTwo,myLattice);
    
    
    /*//show the values of the vertices given the basis vectors
    std::cout << "VERTICES" << std::endl;
    std::cout << "Vertex 3, x = " << myPolytope.getVerticesInLattice()[2][0] << std::endl;
    std::cout << "Vertex 3, y = " << myPolytope.getVerticesInLattice()[2][1] << std::endl;
    std::cout << "Vertex 2, x = " << myPolytope.getVerticesInLattice()[1][0] << std::endl;
    std::cout << "Vertex 2, y = " << myPolytope.getVerticesInLattice()[1][1] << std::endl;
    std::cout << "Vertex 1, x = " << myPolytope.getVerticesInLattice()[0][0] << std::endl;
    std::cout << "Vertex 1, y = " << myPolytope.getVerticesInLattice()[0][1] << std::endl;
    std::cout << "----------------------" << std::endl;*/
    
    //show the value of the direction of a line between two vertices
    std::vector<std::vector<Line> > myLines = myPolytope.getLinesBetweenVertices();
    /*Line myLine(myLines[0][2]);
    
    std::cout << "LINE" << std::endl; 
    std::cout << "direction x: "<< myLine.getDirection()[0] << std::endl;
    std::cout << "direction y: "<< myLine.getDirection()[1] << std::endl;
    std::cout << "begin x: " << myLine.getBeginPoint()[0] << std::endl;
    std::cout << "begin y: "<<  myLine.getBeginPoint()[1] << std::endl;
    std::cout << "end x: "<<  myLine.getEndPoint()[0] <<std::endl;
    std::cout << "end y: "<<  myLine.getEndPoint()[1] <<std::endl;
    std::cout << "----------------------" << std::endl;*/
    
    //get Edges of the polytope
    std::cout << "EDGES OF THE POLYTOPE" << std::endl;
    std::vector<Line> myEdges = myPolytope.getEdges();
    std::cout << "----------------------" << std::endl;
    std::cout << "nr Of Edges = " << myEdges.size() << std::endl;
    for(int i = 0; i < myEdges.size();++i)
    {
        std::cout << "Edge nr = " << i  << std::endl;
        Line myEdge = myEdges[i];
        std::cout << "        " << myEdge.getBeginPoint()[0] << std::endl;
        std::cout << "Begin = " << myEdge.getBeginPoint()[1] << std::endl;
        std::cout << "        " << myEdge.getBeginPoint()[2] << std::endl;
        std::cout << "" << std::endl;
        std::cout << "        " << myEdge.getEndPoint()[0] << std::endl;
        std::cout << "End =   " << myEdge.getEndPoint()[1] << std::endl;
        std::cout << "        " << myEdge.getEndPoint()[2] << std::endl;
        std::cout << "----------------------" << std::endl;
    }
    
    
    std::vector<Cone> myDualCones = myPolytope.getConesOverFaces();
    std::cout << "DUAL CONES OF THE POLYTOPE" << std::endl;
    std::cout << "----------------------" << std::endl;
    for(int i = 0; i < myDualCones.size();++i)
    {
        std::cout << "Cone nr = " << i  << std::endl;
        Cone myCone = myDualCones[i];
        std::vector<std::vector<double> > myBVs = myCone.getBasisVectors();
        std::cout << "        " << myBVs[0][0] << std::endl;
        std::cout << "Ray 1 = " << myBVs[0][1] << std::endl;
        std::cout << "        " << myBVs[0][2] << std::endl;
        std::cout << "" << std::endl;
        std::cout << "        " << myBVs[1][0] << std::endl;
        std::cout << "Ray 2 = " << myBVs[1][1] << std::endl;
        std::cout << "        " << myBVs[1][2] << std::endl;
        std::cout << "----------------------" << std::endl;
    }
    
    Fan myDualFan(myDualCones, myLattice);
    
    Fan myFan = myDualFan.getCorrespondingDualFan();
    std::vector<Cone> myCones = myFan.getCones();
    std::cout << "CONES OF THE POLYTOPE" << std::endl;
    std::cout << "----------------------" << std::endl;
    for(int i = 0; i < myCones.size();++i)
    {
        std::cout << "Cone nr = " << i  << std::endl;
        Cone myCone = myCones[i];
        std::vector<std::vector<double> > myBVs = myCone.getBasisVectors();
        std::cout << "        " << myBVs[0][0] << std::endl;
        std::cout << "Ray 1 = " << myBVs[0][1] << std::endl;
        std::cout << "        " << myBVs[0][2] << std::endl;
        std::cout << "" << std::endl;
        std::cout << "        " << myBVs[1][0] << std::endl;
        std::cout << "Ray 2 = " << myBVs[1][1] << std::endl;
        std::cout << "        " << myBVs[1][2] << std::endl;
        std::cout << "----------------------" << std::endl;
    }
    
    Polytope myDualPolytope = myPolytope.getCorrespondingDualPolytope();
    
    myPolytope.drawPolytope();
    myDualPolytope.drawPolytope();
    myFan.drawFan();
    myDualFan.drawFan();
  
    return 0;
}
