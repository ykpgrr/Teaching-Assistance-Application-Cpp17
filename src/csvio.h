/**
    CS 509 Advanced C++ Programming - Project, csvio.h
    Purpose: reads the csv files row by row.

    @author Yakup Gorur @ykpgrr csvreading code mostly taked from Martin York:
    https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
    @version 0.1 June 7, 2019
*/

#ifndef CSVIO_H
#define CSVIO_H

#include <iostream>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//class CsvIo
//{
//private:

//    std::string fileName;
//    char delimiter;

//public:
//    /**
//        Default ctor.

//        @param string;char, filename which is csv to read data and delimiter to
//        parsing data
//        @return void
//    */
//    CsvIo(const std::string &filename, char delimiter=',');
//};



/*
 * A class to read&write data from a csv file
 */
class CSVRow
{
private:
    std::vector<std::string> m_data;    // keep cells (rowXcolumn cells)
    uint line_count;    // count total line

public:

    std::istream& readNextRow(std::istream& str)
    {
        // Read current line
        auto line = std::string{};
        std::getline(str, line);

        this->line_count++; // Increase line counter

        auto lineStream = std::stringstream(line);
        auto cell = std::string{};

        m_data.clear(); // Clean the old row
        // Read all cell and add them in the m_data
        while(std::getline(lineStream, cell, ','))
        {
            m_data.push_back(cell);
        }

        // This checks for a trailing comma with no data after it.
        if (!lineStream && cell.empty())
        {
            // If there was a trailing comma then add an empty element.
            m_data.push_back("");
        }
        return str;
    }

    std::size_t size() const
    {
        return m_data.size();
    }

    std::string const& operator[](std::size_t index) const
    {
        return m_data[index];
    }



};

//std::istream& operator>> (std::istream& str, CSVRow& data)
//{
//    data.readNextRow(str);
//    return str;
//}

#endif // CSVIO_H
