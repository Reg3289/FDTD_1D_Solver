#include "../include/Grid1D.h"
#include "../include/Boundary.h"
#include "../include/Source.h"
#include "../include/BraggGrating.h"
#include "../include/Simulation.h"

int main() {
    Grid1D grid(300);

    BraggGrating grating(100, 220, 5, 2.0, 1.5);
    grating.buildOnGrid(grid);

    MurABC myBoundary;
    UnidirectionalSource mySource(50);

    Simulation engine(grid, 800);
    engine.setBoundary(&myBoundary);
    engine.setSource(&mySource);

    engine.run("fdtd_bragg_cmake_results.csv");

    return 0;
}
