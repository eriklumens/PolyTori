#include <iostream>

class Lattice
{
    private:
    int mDimension;
    double mBasisVectors[mDimension];

    public:
    Lattice(int dimension, double basisVectors)
    {
        setDimension(int dimension);
        if basisVectors.size() == dimension
        {
            setBasisVectors(double basisVectors);
        }
        else
        {
            std::cout << "Size of array basis vectors is not equal to the dimension of the lattice! Could not construct lattice." << std::endl;
        return;
        }
    }

    void setDimension(int dimension)
    {
        mDimension = dimension;
    }

    void setBasisVectors(double basisVectors)
    {   
        if basisVectors.size() == mDimension
        {
            mBasisVectors = basisVectors;
        }
        else
        {
            std::cout << "Could not set new basis vectors. Dimension of given array is not equal to dimension of lattice." << std::endl;
            return;
        }
    }

    int getDimension()
    {
        return mDimension;
    }

    double getBasisVectors()
    {
        return mBasisVectors;
    }
};
