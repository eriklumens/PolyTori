#include <iostream>
#include <vector>
#include "lattice.h"

class Cone
{
    private:
    std::vector<std::vector<double> > basisVectors{std::vector<std::vector<double> >(0,std::vector<double>(0))};
    Lattice lattice{Lattice(0,std::vector<std::vector<double> >(0,std::vector<double>(0)))}; 

    public:
    Cone(std::vector<std::vector<double> > bv,Lattice lat);
    ~Cone();
    void setBasisVectors(std::vector<std::vector<double> > bv);
    std::vector<std::vector<double> > getBasisVectors();
    Cone getCorrespondingDualCone();
};
