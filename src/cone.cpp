#include <iostream>
#include <vector>
#include "cone.h"
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>

using namespace Eigen;
using Eigen::MatrixXd;

Cone::Cone(std::vector<std::vector<double> > _basisVectors, Lattice _lattice)
{
    basisVectors = _basisVectors;
    lattice = _lattice;
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

//Works for arbitrary dimension
Cone Cone::getCorrespondingDualCone()
{
    int nrOfBasisVectors = basisVectors.size();
    int dimensionOfLattice = lattice.getDimension();
    std::vector<std::vector<double> > myDualBasis(0,std::vector<double>(dimensionOfLattice));
    
    for(int i = 0; i < nrOfBasisVectors; ++i)
    { 
        std::vector<std::vector<double> > copyOfBasisVectors = basisVectors;
        copyOfBasisVectors.erase(copyOfBasisVectors.begin()+i);
        std::vector<std::vector<double> > subsetOfBasisVectors = copyOfBasisVectors;
        
        MatrixXd m(subsetOfBasisVectors.size(),dimensionOfLattice);
        //We set m to be the matrix of this subset
        for(int j = 0; j < subsetOfBasisVectors.size(); ++j)
        {
            for(int k = 0; k < dimensionOfLattice; ++k)
            {
                m(j,k) = subsetOfBasisVectors[j][k];
            }
        }
        //Solve equation B*x = 0 for x
        MatrixXd ker = m.fullPivLu().kernel(); 
        
        //look at inproduct with remaining generator and ask that it is positive
        for(int j = 0; j < ker.cols(); ++j)
        {
            double sum = 0;
            for(int k = 0; k < dimensionOfLattice; ++k)
            {
                sum = sum + ker(k,j)*basisVectors[i][k];
            }

            if (sum < 0)
            {
                std::vector<double> myGenerator(dimensionOfLattice,0);
                for(int k = 0; k < dimensionOfLattice; ++k)
                { 
                    myGenerator[k] = (-1)*ker(k,j);
                }
                myDualBasis.push_back(myGenerator);
            }
            else if (sum > 0)
            {
                std::vector<double> myGenerator(dimensionOfLattice,0);
                for(int k = 0; k < dimensionOfLattice; ++k)
                { 
                    myGenerator[k] = ker(k,j); 
                }
                myDualBasis.push_back(myGenerator);
            }
        }    
    }
    
    Cone myCone(myDualBasis,lattice);
    return myCone;
}
