#include <iostream>
#include <vector>

class Cone
{
    private:
    std::vector<std::vector<double> > basisVectors{std::vector<std::vector<double> >(0,std::vector<double>(0))};

    public:
    Cone(std::vector<std::vector<double> > bv);
    ~Cone();
    void setBasisVectors(std::vector<std::vector<double> > bv);
    std::vector<std::vector<double> > getBasisVectors();
};
