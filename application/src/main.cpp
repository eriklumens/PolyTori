#include <iostream>
#include <vector>
#include "lattice.h"

int main()
{
    std::vector<std::vector<double> > vec(2,std::vector<double>(2));
    vec[1][1] = 1;
    std::cout << "hello" << std::endl;
    vec[1][0] = 0;
    std::cout << "hello" << std::endl;
    vec[0][1] = 0;
    std::cout << "hello" << std::endl;
    vec[0][0] = 1;
    std::cout << "hello" << std::endl;
    Lattice myLattice(2,vec);
    std::cout << myLattice.getDimension() << std::endl;
    myLattice.setDimension(2);
    std::cout << myLattice.getDimension() << std::endl;
    return 0;
}
