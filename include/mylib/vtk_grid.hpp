#pragma once

#include <fstream>

#include "grid.hpp"

class VtkGrid : public Grid
{
private:
    /* data */
public:
    string Version;

    string Title;

    string File_format; // ASCII or Binary

    string Dataset;

    int Format = -1;

    enum FORMAT
    {
        STRUCTURED_POINTS,
        STRUCTURED_GRID,
        RECTILINEAR_GRID,
        POLYDATA,
        UNSTRUCTURED_GRID,
        FIELD
    };

    VtkGrid(/* args */);
    ~VtkGrid();

    int FromFile(string filename);
};

VtkGrid::VtkGrid(/* args */)
{
}

VtkGrid::~VtkGrid()
{
}

int VtkGrid::FromFile(string filename)
{
    ifstream newfile(filename);

    if (newfile.is_open())
    {
        getline(newfile, Version);

        getline(newfile, Title);

        getline(newfile, File_format);

        string dataset_keyword; // keyword DATASET
        newfile >> dataset_keyword;

        newfile >> Dataset; // DATASET, expamle: UNSTRUCTURED_GRID

        {
            if (Dataset == "STRUCTURED_POINTS")
            {
                Format = FORMAT::STRUCTURED_POINTS;
            }

            if (Dataset == "STRUCTURED_GRID")
            {
                Format = FORMAT::STRUCTURED_GRID;
            }

            if (Dataset == "UNSTRUCTURED_GRID")
            {
                Format = FORMAT::UNSTRUCTURED_GRID;
            }

            if (Dataset == "POLYDATA")
            {
                Format = FORMAT::POLYDATA;
            }

            if (Dataset == "RECTILINEAR_GRID")
            {
                Format = FORMAT::RECTILINEAR_GRID;
            }

            if (Dataset == "FIELD")
            {
                Format = FORMAT::FIELD;
            }

            if (Format == -1)
            {

                return 3;
            }
        }

        string points_keyword;
        newfile >> points_keyword;

        newfile >> Nodes_count;

        string nodes_type;
        newfile >> nodes_type;

        for (int i = 0; i < Nodes_count; ++i)
        {
            double x, y, z;
            try
            {
                newfile >> x >> y >> z;
            }
            catch (...)
            {
                return 3;
            }

            Nodes.push_back(Node(x, y, z));
        }

        string cells_keyword;
        newfile >> points_keyword;

        try
        {
            newfile >> Cells_count;
        }
        catch (...)
        {
            return 3;
        }

        int nodes_count;
        try
        {
            newfile >> nodes_count;
        }
        catch (...)
        {
            return 3;
        }

        for (int i = 0; i < Cells_count; ++i)
        {
            Cell cell = Cell();

            int n; // число узлов в текущей ячейке

            try
            {
                newfile >> n;
            }
            catch (...)
            {
                return 3;
            }

            for (int j = 0; j < n; ++j)
            {
                int index_j; // номер узла j в текущей ячейке
                try
                {

                    newfile >> index_j;
                }
                catch (...)
                {
                    return 3;
                }
                cell.Indecies.push_back(index_j);
            }

            Cells.push_back(cell);
        }

        string cells_type_keyword;
        newfile >> cells_type_keyword;

        int cells_type_count;
        newfile >> cells_type_count;

        if (cells_type_count != Cells_count)
        {
            return 4;
        }

        for (int i = 0; i < Cells_count; ++i)
        {
            newfile >> Cells[i].type;
        }
    }
    else
    {
        return 2; // ошибка чтения файла
    }

    newfile.close();

    return 0;
}
