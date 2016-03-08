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
    
    //set up 2d polytopes
    
    std::vector<std::vector<double> > ver0(3,std::vector<double>(2));
    std::vector<std::vector<double> > ver1(4,std::vector<double>(2));
    std::vector<std::vector<double> > ver2(4,std::vector<double>(2));
    std::vector<std::vector<double> > ver3(3,std::vector<double>(2));
    std::vector<std::vector<double> > ver4(5,std::vector<double>(2));
    std::vector<std::vector<double> > ver5(4,std::vector<double>(2));
    std::vector<std::vector<double> > ver6(6,std::vector<double>(2));
    std::vector<std::vector<double> > ver7(4,std::vector<double>(2));
    std::vector<std::vector<double> > ver8(5,std::vector<double>(2));
    std::vector<std::vector<double> > ver9(3,std::vector<double>(2));
    std::vector<std::vector<double> > ver10(4,std::vector<double>(2));
    
    ver0[0][0] = 1;
    ver0[0][1] = 0;
    ver0[1][0] = 0;
    ver0[1][1] = 1;
    ver0[2][0] = -1;
    ver0[2][1] = -1;
    
    ver1[0][0] = 1;
    ver1[0][1] = 0;
    ver1[1][0] = 0;
    ver1[1][1] = 1;
    ver1[2][0] = -1;
    ver1[2][1] = 0;
    ver1[3][0] = 0;
    ver1[3][1] = -1;
    
    ver2[0][0] = 1;
    ver2[0][1] = 0;
    ver2[1][0] = 0;
    ver2[1][1] = 1;
    ver2[2][0] = -1;
    ver2[2][1] = 0;
    ver2[3][0] = -1;
    ver2[3][1] = -1;
    
    ver3[0][0] = 1;
    ver3[0][1] = 0;
    ver3[1][0] = 0;
    ver3[1][1] = 1;
    ver3[2][0] = -2;
    ver3[2][1] = -1;
    
    ver4[0][0] = 1;
    ver4[0][1] = 0;
    ver4[1][0] = 1;
    ver4[1][1] = 1;
    ver4[2][0] = 0;
    ver4[2][1] = 1;
    ver4[3][0] = -1;
    ver4[3][1] = 0;
    ver4[4][0] = 0;
    ver4[4][1] = -1;
    
    ver5[0][0] = 1;
    ver5[0][1] = 0;
    ver5[1][0] = 0;
    ver5[1][1] = 1;
    ver5[2][0] = -1;
    ver5[2][1] = 1;
    ver5[3][0] = -1;
    ver5[3][1] = -1;
    
    Polytope pol0(ver0,myLattice);
    Polytope pol1(ver1,myLattice);
    Polytope pol2(ver2,myLattice);
    Polytope pol3(ver3,myLattice);
    Polytope pol4(ver4,myLattice);
    Polytope pol5(ver5,myLattice);
    
    Polytope pol15 = pol0.getCorrespondingDualPolytope();
    Polytope pol14 = pol1.getCorrespondingDualPolytope();
    Polytope pol13 = pol2.getCorrespondingDualPolytope();
    Polytope pol12 = pol3.getCorrespondingDualPolytope();
    Polytope pol11 = pol4.getCorrespondingDualPolytope();
    Polytope pol10 = pol5.getCorrespondingDualPolytope();
    
    ver6[0][0] = 1;
    ver6[0][1] = 0;
    ver6[1][0] = 1;
    ver6[1][1] = 1;
    ver6[2][0] = 0;
    ver6[2][1] = 1;
    ver6[3][0] = -1;
    ver6[3][1] = 0;
    ver6[4][0] = -1;
    ver6[4][1] = -1;
    ver6[5][0] = 0;
    ver6[5][1] = -1;
    
    ver7[0][0] = 1;
    ver7[0][1] = 0;
    ver7[1][0] = -1;
    ver7[1][1] = 1;
    ver7[2][0] = -1;
    ver7[2][1] = -1;
    ver7[3][0] = 1;
    ver7[3][1] = -1;
    
    ver8[0][0] = 1;
    ver8[0][1] = 0;
    ver8[1][0] = 1;
    ver8[1][1] = 1;
    ver8[2][0] = -1;
    ver8[2][1] = 1;
    ver8[3][0] = -1;
    ver8[3][1] = 0;
    ver8[4][0] = 0;
    ver8[4][1] = -1;
    
    ver9[0][0] = 1;
    ver9[0][1] = 0;
    ver9[1][0] = -1;
    ver9[1][1] = 2;
    ver9[2][0] = -1;
    ver9[2][1] = -1;
    
    Polytope pol6(ver6,myLattice);
    Polytope pol7(ver7,myLattice);
    Polytope pol8(ver8,myLattice);
    Polytope pol9(ver9,myLattice);
    
    Polytope polytopes2D[16] = {pol0, pol1, pol2, pol3, pol4, pol5, pol6, pol7, pol8, pol9, pol10, pol11, pol12, pol13, pol14, pol15};
    Polytope polytopes2DDual[16] = {pol15, pol14, pol13, pol12, pol11, pol10, pol6, pol7, pol8, pol9, pol5, pol4, pol3, pol2, pol1, pol0};
    for(int i = 0; i < 16; ++i)
    {
        Polytope myPolytope = polytopes2D[i];
        myPolytope.drawPolytope();
    }

    //Construct 16*16 4d polytopes from this data
    
    std::vector<Polytope> polytopes4D;
    std::vector<Polytope> dualPolytopes4D;
    
    /*for(int i = 0; i < 16; ++i)
    {
        for(int j = 0; j < 16; ++j)
        {
            std::cout << "i = " << i << ", j = " << j << std::endl; 
            Polytope my4DPolytope(polytopes2D[i], polytopes2D[j], 2, 2,false);
            Polytope my4DDualPolytope(polytopes2DDual[i], polytopes2DDual[j], 2, 2, true);
            polytopes4D.push_back(my4DPolytope);
            dualPolytopes4D.push_back(my4DDualPolytope);
        }
    }*/
    return 0;
}
