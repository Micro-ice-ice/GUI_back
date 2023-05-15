#pragma once
#include <vector>
#include <iostream>

#include "node.hpp"
#include "cell.hpp"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace std;
using namespace rapidjson;

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

    int ToJson(StringBuffer &buffer);
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

int Grid::ToJson(StringBuffer &buffer)
{
    DefineBoundaryCells();
    DefineNodesBelongBoundary();
    DefineNodeDifferences();

    Document document;
    document.SetObject();

    // add nodes
    Value nodes(kArrayType);
    for (int i = 0; i < Boundary_nodes_indecies.size(); ++i)
    {
        int index = Boundary_nodes_indecies[i];
        Value node(kObjectType);
        node.AddMember("x", Nodes[index].X, document.GetAllocator());
        node.AddMember("y", Nodes[index].Y, document.GetAllocator());
        node.AddMember("z", Nodes[index].Z, document.GetAllocator());
        node.AddMember("value", 0, document.GetAllocator());
        nodes.PushBack(node, document.GetAllocator());
    }
    document.AddMember("nodes", nodes, document.GetAllocator());

    // add cell
    Value cells(kArrayType);
    for (int i = 0; i < Boundary_cell_indecies.size(); ++i)
    {
        Value cell(kObjectType);
        int index = Boundary_cell_indecies[i];
        cell.AddMember("type", Cells[index].type, document.GetAllocator());

        Value indecies(kArrayType);
        for (int j = 0; j < Cells[index].Indecies.size(); ++j)
        {
            int node_index = Cells[index].Indecies[j];
            indecies.PushBack(node_index - Nodes_differences[node_index], document.GetAllocator());
        }
        cell.AddMember("nodes", indecies, document.GetAllocator());

        cell.AddMember("value", 0, document.GetAllocator());
        cells.PushBack(cell, document.GetAllocator());
    }
    document.AddMember("cells", cells, document.GetAllocator());

    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    return 0;
}