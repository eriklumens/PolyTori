#include <iostream>
#include <vector>

class Lattice
{
    private:
    int dimension = 0;
    std::vector<std::vector<double> > basisVectors{std::vector<std::vector<double> >(1,std::vector<double>(1))};

    public:
    Lattice(int dim, std::vector<std::vector<double> > bv);
    ~Lattice();
    void setDimension(int dim);
    void setBasisVectors(std::vector<std::vector<double> > bv);
    int getDimension();
    std::vector<std::vector<double> > getBasisVectors();
};
