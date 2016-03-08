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
    
    
    //define lattice
    Lattice myLattice(2,basis);
    
    //set up cones
    
    Cone Sigma0 = Cone({{1,0},{0,1}},myLattice);
    Cone Sigma11 = Cone({{0,1},{-1,0}},myLattice);
    Cone Sigma12 = Cone({{-1,0},{-1,-1}},myLattice);
    Cone Sigma13 = Cone({{-1,-1},{-2,-3}},myLattice);
    Cone Sigma21 = Cone({{-2,-3},{-1,-2}},myLattice);
    Cone Sigma22 = Cone({{-1,-2},{0,-1}},myLattice);
    Cone Sigma23 = Cone({{0,-1},{1,0}},myLattice);
    
    //Define fan
    std::vector<Cone> myCones = {Sigma0, Sigma11, Sigma12, Sigma13, Sigma21, Sigma22, Sigma23};
    Fan myFan(myCones,myLattice);
    
    //Get dual fan
    Fan myDualFan = myFan.getCorrespondingDualFan();
    
    
    std::vector<Cone> myDualCones = myDualFan.getCones();
    std::cout << "CONES OF THE DUAL FAN" << std::endl;
    std::cout << "----------------------" << std::endl;
    for(int i = 0; i < myDualCones.size();++i)
    {
        std::cout << "Cone nr = " << i  << std::endl;
        Cone myDualCone = myDualCones[i];
        std::vector<std::vector<double> > myBVs = myDualCone.getBasisVectors();
        std::cout << "        " << myBVs[0][0] << std::endl;
        std::cout << "Ray 1 = " << myBVs[0][1] << std::endl;
        std::cout << "        " << myBVs[0][2] << std::endl;
        std::cout << "" << std::endl;
        std::cout << "        " << myBVs[1][0] << std::endl;
        std::cout << "Ray 2 = " << myBVs[1][1] << std::endl;
        std::cout << "        " << myBVs[1][2] << std::endl;
        std::cout << "----------------------" << std::endl;
    }
    
    myFan.drawFan();
    myDualFan.drawFan();
  
    return 0;
}
