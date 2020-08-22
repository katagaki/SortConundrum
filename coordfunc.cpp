#include <string>
#include "Point2D.h"
#include "strfunc.h"

Point2D* getPoint2D(std::string data) {
    
    if (startsWith(data, "point2d")) {
        
        // Split string by comma > get right side > trim spaces > gets back coodinates
        // "[x, y]"
        std::string strRightSideData = trimString(getRightSide(data, ","));
        
        // Split data by comma > get left side > trim spaces > remove the first [ > trim again > gets back x
        // "x"
        std::string strX = trimString(removeFirstChar(trimString(getLeftSide(strRightSideData, ","))));
        int x = std::stoi(strX);
        
        // Split data by comma > get right side > trim spaces > remove the last ] > trim again > gets back y
        // "y"
        std::string strY = trimString(removeLastChar(trimString(getRightSide(strRightSideData, ","))));
        int y = std::stoi(strY);
        
        Point2D* pt = new Point2D(x, y);
                
        return pt;
        
    } else {
        throw std::string("The object specified is not a Point2D object: " + data);
    }
    
}
