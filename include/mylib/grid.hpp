#pragma once
#include <vector>
#include <iostream>

#include "node.hpp"
#include "cell.hpp"

using namespace std;

class Grid
{
private:
    vector<bool> Nodes_belong_boundary;

    vector<int> Nodes_differences; // transform vector for node indices from global to local (boundary)

    void DefineBoundaryCells()
    {
        for (int i = 0; i < Cells_count; ++i)
        {

            if (Cells[i].type < 10 || (20 < Cells[i].type && Cells[i].type < 24))
            {
                Boundary_cell_indecies.push_back(i);
            }
        }
    }

    void DefineNodesBelongBoundary()
    {
        Nodes_belong_boundary.reserve(sizeof(bool) * Nodes_count);
        for (int i = 0; i < Nodes_count; ++i)
        {

            Nodes_belong_boundary.push_back(false);
        }

        for (int i = 0; i < Boundary_cell_indecies.size(); ++i)
        {
            const Cell &cell = Cells[Boundary_cell_indecies[i]]; // getting cell from global cell array

            for (int j = 0; j < cell.Indecies.size(); ++j)
            {
                Nodes_belong_boundary[cell.Indecies[j]] = true;
            }
        }
    }

    void DefineNodeDifferences()
    {
        int init_value = 0;

        for (int i = 0; i < Nodes_count; ++i)
        {

            if (Nodes_belong_boundary[i] == false)
            {
                init_value++;
            }
            else
            {
                Boundary_nodes_indecies.push_back(i);
            }

            Nodes_differences.push_back(init_value);
        }
    }

public:
    int Nodes_count;
    vector<Node> Nodes; // nodes array

    vector<int> Boundary_nodes_indecies; // boundary node indecies array

    int Cells_count;
    vector<Cell> Cells; // cells array

    vector<int> Boundary_cell_indecies; // boundary cell indices array

    virtual int FromFile(string filename);

    Grid();
    ~Grid();
};

Grid::Grid()
{
}

Grid::~Grid()
{
}

int Grid::FromFile(string filename)
{
}