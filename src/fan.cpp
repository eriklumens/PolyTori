#include <iostream>
#include <vector>
#include "fan.h"
#include <GLFW/glfw3.h>

Fan::Fan(std::vector<Cone> con, Lattice lat)
{
    cones = con;
    lattice = lat;
    return;
}

Fan::~Fan(){}

void Fan::setCones(std::vector<Cone> con)
{   
        cones = con;
        return;
}

std::vector<Cone> Fan::getCones()
{
    return cones;
}

//Works for arbitrary dimension.
Fan Fan::getCorrespondingDualFan()
{
    int dimensionOfLattice = lattice.getDimension();
    std::vector<std::vector<double> > myDualBasis(0,std::vector<double>(dimensionOfLattice));
    std::vector<Cone> myDualCones(0,Cone(myDualBasis,lattice));
    
    for(int i = 0; i < cones.size(); ++i)
    {
        Cone myCone = cones[i];
        Cone myDualCone = myCone.getCorrespondingDualCone();
        myDualCones.push_back(myDualCone);
    }
    
    Fan myDualFan(myDualCones, lattice);
    return myDualFan;
}

int Fan::drawFan()
{
    int nrOfCones = cones.size();
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glLineWidth(2.5);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        for(int i = 0; i < nrOfCones; ++i)
        {
            Cone myCone = cones[i];
            std::vector<std::vector<double> > myBVs = myCone.getBasisVectors();
            int nrOfBVs = myBVs.size();
            for(int j = 0; j < nrOfBVs; ++j)
            {
                glVertex3f(0, 0, 0);
                glVertex3f(myBVs[j][0], myBVs[j][1], myBVs[j][2]);
            }
        }
        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
