#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Point2D.h"
#include "coordfunc.h"
#include "iofunc.h"
#include "printfunc.h"
#include "strfunc.h"

int main() {
    
    int numberOfRecords = 0,
	    numberOfDupesRemoved = 0;
    std::ifstream fileReader;
    std::string dataFilename,
	            strFileReaderLine,
                strOutput;
	std::stringstream sstOutput;
    std::vector<Point2D> point2Ds;
    
    // Try to read the file
    try {
        provideStream("data.txt", fileReader);
    } catch (std::string e) {
        cpt::println(e);
        return 1;
    }
    
    cpt::print("Reading data... ");
    
    // Start reading the data
    while (fileReader.good()) {
        while (getline(fileReader, strFileReaderLine)) {
            
            if (startsWith(strFileReaderLine, "point2d")) {
                
                Point2D* pt2 = getPoint2D(strFileReaderLine);
                
                // Add the point if it is unique
                if (std::find_if(point2Ds.begin(), point2Ds.end(), [pt2](Point2D ptInVector) {
                    return ptInVector == *pt2;
                }) != point2Ds.end()) {
                    delete pt2;
                    ++numberOfDupesRemoved;
                } else {
                    point2Ds.push_back(*pt2);
                    ++numberOfRecords;
                }
                
            }
            
        }
    }
    
    cpt::println("done.");
    cpt::println();
    
    cpt::print(numberOfRecords);
    cpt::println(" record(s) loaded successfully, of which:");
    cpt::print(point2Ds.size());
    cpt::println(" are Point2D object(s).");
    cpt::print(numberOfDupesRemoved);
    cpt::println(" duplicate record(s) were not loaded.");
    cpt::println();
    
    sstOutput.str(std::string());
    sstOutput.clear();
    
    
    std::sort(point2Ds.begin(), point2Ds.end(), [](Point2D a, Point2D b) {
        return a.getScalarValue() > b.getScalarValue();
    });
                        
    sstOutput << "    X     Y    Dist. Fr Origin" << std::endl;
    sstOutput << "- - - - - - - - - - - - - - - - - - -" << std::endl;
    
    for (Point2D pt: point2Ds) {
        sstOutput << "[";
        sstOutput << std::right << std::setw(4) << pt.getX();
        sstOutput << ", ";
        sstOutput << std::right << std::setw(4) << pt.getY();
        sstOutput << "]" << "   ";
        sstOutput << std::fixed << std::setprecision(3) << pt.getScalarValue();
        sstOutput << std::endl;
    }
    
    cpt::println(sstOutput.str());
    
    return 0;
}
