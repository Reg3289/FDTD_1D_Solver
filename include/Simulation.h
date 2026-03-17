#pragma once
#include "Grid1D.h"
#include "Boundary.h"
#include "Source.h"
#include <iostream>
#include <fstream>
#include <string>

class Simulation {
private:
    Grid1D& grid;
    int max_time;
    Boundary* boundary;
    Source* source;

public:
    Simulation(Grid1D& g, int t) : grid(g), max_time(t), boundary(nullptr), source(nullptr) {}

    void setBoundary(Boundary* b) { boundary = b; }
    void setSource(Source* s) { source = s; }

    void run(const std::string& filename) {
        std::ofstream outFile(filename);
        std::cout << "Starting OOP FDTD Simulation Engine..." << std::endl;

        for (int qTime = 0; qTime < max_time; ++qTime) {
            if (boundary) boundary->saveInternal(grid);

            for (int mm = 0; mm < grid.size - 1; ++mm) {
                grid.hy[mm] = grid.hy[mm] + (grid.ez[mm + 1] - grid.ez[mm]) / grid.IMP0;
            }

            if (source) source->injectH(grid, qTime);

            for (int mm = 1; mm < grid.size - 1; ++mm) {
                grid.ez[mm] = grid.ez[mm] + (grid.hy[mm] - grid.hy[mm - 1]) * grid.IMP0 / grid.eps_r[mm];
            }

            if (source) source->injectE(grid, qTime);
            if (boundary) boundary->apply(grid);

            if (qTime % 5 == 0) {
                for (int mm = 0; mm < grid.size; ++mm) {
                    outFile << grid.ez[mm];
                    if (mm < grid.size - 1) outFile << ",";
                }
                outFile << "\n";
            }
            if (qTime % 100 == 0) std::cout << "Step: " << qTime << " / " << max_time << std::endl;
        }
        outFile.close();
        std::cout << "Simulation Complete! Data written to: " << filename << std::endl;
    }
};
