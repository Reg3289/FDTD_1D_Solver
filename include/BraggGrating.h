#pragma once
#include "Grid1D.h"

class BraggGrating {
private:
    int start_idx;
    int end_idx;
    int period_thickness;
    double n_high;
    double n_low;

public:
    BraggGrating(int start, int end, int thickness, double nh, double nl) 
        : start_idx(start), end_idx(end), period_thickness(thickness), n_high(nh), n_low(nl) {}

    void buildOnGrid(Grid1D& grid) {
        double eps_high = n_high * n_high;
        double eps_low = n_low * n_low;
        int period_total = period_thickness * 2;

        for (int mm = start_idx; mm < end_idx; ++mm) {
            if ((mm - start_idx) % period_total < period_thickness) {
                grid.eps_r[mm] = eps_high;
            } else {
                grid.eps_r[mm] = eps_low;
            }
        }
    }
};
