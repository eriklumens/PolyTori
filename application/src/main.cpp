#include <iostream>
#include <vector>
#include "polytope.h"
#include <math.h>

int main()
{
    //set up basisvectors
    std::vector<std::vector<double> > basis2(2,std::vector<double>(2));
    basis2[0][0] = 1;
    basis2[0][1] = 0;
    basis2[1][0] = 0;
    basis2[1][1] = 1;
    
    //define lattice
    Lattice myLattice(2,basis2);
    
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

    //Construct 16*16 4d polytopes from this data
    
    std::vector<Polytope> polytopes4D;
    std::vector<Polytope> dualPolytopes4D;
    
    
    for(int i = 0; i < 16; ++i)
    {
        for(int j = 0; j < 16; ++j)
        {
            Polytope my4DPolytope(polytopes2D[i], polytopes2D[j], 2, 2,false);
            Polytope my4DDualPolytope(polytopes2DDual[i], polytopes2DDual[j], 2, 2, true);
            polytopes4D.push_back(my4DPolytope);
            dualPolytopes4D.push_back(my4DDualPolytope);
        }
    }

    Polytope projWeighted = pol9.getModularTransform(-1,-1,1,0);
    Polytope polPaper(pol15,projWeighted,1,2,false);
    Polytope projWeightedDual = projWeighted.getCorrespondingDualPolytope();
    Polytope polPaperDual(pol15.getCorrespondingDualPolytope(),projWeightedDual,2,1,true);
    
    
    std::vector<std::vector<double> > verticesPolPaper = polPaper.getVertices();
    std::vector<std::vector<double> > verticesPolPaperDual = polPaperDual.getVertices();
    std::vector<int> dualVerticesOrder = polPaper.getDualVerticesOrdering(pol15,projWeighted,1,2);
    
    for(int i = 0; i < verticesPolPaperDual.size(); ++i)
    {
        std::cout << "(" << verticesPolPaperDual[i][0] << "," << verticesPolPaperDual[i][1] << "," << verticesPolPaperDual[i][2] << "," << verticesPolPaperDual[i][3] << ")" << std::endl;
    }
    
    std::cout << "------------------------------" << std::endl;
    std::cout << "La moment supreme:" << std::endl;
    std::cout << "h1,1 = " << polPaper.hodgeOneOne(pol15,projWeighted,1,2) << std::endl;
    std::cout << "h2,1 = " << polPaper.hodgeTwoOne(pol15,projWeighted,1,2) << std::endl;
    
    std::vector<std::vector<double> > basis(4,std::vector<double>(4));
    basis[0][0] = 1;
    basis[0][1] = 0;
    basis[0][2] = 0;
    basis[0][3] = 0;
    
    basis[1][0] = 0;
    basis[1][1] = 1;
    basis[1][2] = 0;
    basis[1][3] = 0;
    
    basis[2][0] = 0;
    basis[2][1] = 0;
    basis[2][2] = 1;
    basis[2][3] = 0;
    
    basis[3][0] = 0;
    basis[3][1] = 0;
    basis[3][2] = 0;
    basis[3][3] = 1;
    Lattice myLattice4(4,basis);
    
    
    Polytope quintic({{-1,-1,-1,-1},{4,-1,-1,-1},{-1,4,-1,-1},{-1,-1,4,-1},{-1,-1,-1,4}},myLattice4);
    Polytope quinticDual({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1},{-1,-1,-1,-1}},myLattice4);
    
    std::cout << "------------------------------" << std::endl;
    std::cout << "For the quintic we obtain:" << std::endl;
    std::cout << "h1,1 = " << quintic.hodgeOneOne(quinticDual) << std::endl;
    std::cout << "h2,1 = " << quintic.hodgeTwoOne(quinticDual) << std::endl;
    std::cout << "and for its dual:" << std::endl;
    std::cout << "h1,1 = " << quinticDual.hodgeOneOne(quintic) << std::endl;
    std::cout << "h2,1 = " << quinticDual.hodgeTwoOne(quintic) << std::endl;
    
    Polytope Batyrev({{-1,-1,-1,-1},{17,-1,-1,-1},{-1,17,-1,-1},{-1,-1,2,-1},{-1,-1,-1,1}},myLattice4);
    Polytope BatyrevDual({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1},{-1,-1,-6,-9}},myLattice4);
    
    std::cout << "------------------------------" << std::endl;
    std::cout << "For the batyrev P4(1,1,1,6,9) we obtain:" << std::endl;
    std::cout << "h1,1 = " << Batyrev.hodgeOneOne(BatyrevDual) << std::endl;
    std::cout << "h2,1 = " << Batyrev.hodgeTwoOne(BatyrevDual) << std::endl;
    std::cout << "and for its dual:" << std::endl;
    std::cout << "h1,1 = " << BatyrevDual.hodgeOneOne(Batyrev) << std::endl;
    std::cout << "h2,1 = " << BatyrevDual.hodgeTwoOne(Batyrev) << std::endl;
    
    Polytope paper({{12,-6,-1,-1},{-6,12,-1,-1},{-6,-6,-1,-1},{0,0,2,-1},{0,0,-1,1}},myLattice4);
    Polytope paperDual({{1,0,-2,-3},{0,1,-2,-3},{-1,-1,-2,-3},{0,0,1,0},{0,0,0,1}},myLattice4);
    
    std::cout << "------------------------------" << std::endl;
    std::cout << "For the paper P4(1,1,1,6,9) we obtain:" << std::endl;
    std::cout << "h1,1 = " << paper.hodgeOneOne(paperDual) << std::endl;
    std::cout << "h2,1 = " << paper.hodgeTwoOne(paperDual) << std::endl;
    std::cout << "and for its dual:" << std::endl;
    std::cout << "h1,1 = " << paperDual.hodgeOneOne(paper) << std::endl;
    std::cout << "h2,1 = " << paperDual.hodgeTwoOne(paper) << std::endl;
    
    Polytope test1({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1},{-2,-1,-1,-1}},myLattice4);
    Polytope test1Dual({{2,-1,-1,-1},{-1,5,-1,-1},{-1,-1,5,-1},{-1,-1,-1,5},{-1,-1,-1,-1}},myLattice4);
    std::cout << "------------------------------" << std::endl;
    std::cout << "For the test1 we obtain:" << std::endl;
    std::cout << "h1,1 = " << test1.hodgeOneOne(test1Dual) << std::endl;
    std::cout << "h2,1 = " << test1.hodgeTwoOne(test1Dual) << std::endl;
    std::cout << "and for its dual:" << std::endl;
    std::cout << "h1,1 = " << test1Dual.hodgeOneOne(test1) << std::endl;
    std::cout << "h2,1 = " << test1Dual.hodgeTwoOne(test1) << std::endl;
    
    Polytope test2({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1},{-5,-2,-1,-1}},myLattice4);
    Polytope test2Dual({{1,-1,-1,-1},{-1,4,-1,-1},{-1,-1,9,-1},{-1,-1,-1,9},{-1,-1,-1,-1}},myLattice4);
    std::cout << "------------------------------" << std::endl;
    std::cout << "For the test2 we obtain:" << std::endl;
    std::cout << "h1,1 = " << test2.hodgeOneOne(test2Dual) << std::endl;
    std::cout << "h2,1 = " << test2.hodgeTwoOne(test2Dual) << std::endl;
    std::cout << "and for its dual:" << std::endl;
    std::cout << "h1,1 = " << test2Dual.hodgeOneOne(test2) << std::endl;
    std::cout << "h2,1 = " << test2Dual.hodgeTwoOne(test2) << std::endl;    

    return 0;
}
