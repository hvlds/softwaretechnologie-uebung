#include "rectangle.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>

Polygon convex_hull_polygon(std::vector <Point> points);
void printDiv();

int main(){
    Point p1 {1, 1};
    Point p2 {3, 1};
    Point p3 {6, 2};
    Point p4 {3, 2};
    Point p5 {2, 3};
    Point p6 {6, 4};
    Point p7 {1, 4};
    
    std::vector <Point> points {p1, p2, p3, p4, p5, p6, p7};   
    convex_hull_polygon(points);
    return 0;
}

void printDiv(){
    // Print divider
    std::cout << "---- ---- ----" << std::endl;
}

Polygon convex_hull_polygon(std::vector <Point> points){
    // Using Graham Scan Algorithm    

    // Find lowest y of the cloud of points
    Point lowest_point;
    for(auto it = points.begin(); it != points.end(); ++it){
        if(it == points.begin()){
            lowest_point = *it;
        } else {
            if(it->getY() < lowest_point.getY()){
                lowest_point = *it;
            } else if( (it->getY() == lowest_point.getY()) && (it->getX() < lowest_point.getX())){
                lowest_point = *it;
            }
        }
    }
    std::cout << "Lowest point in the cloud: " << lowest_point << std::endl;
    printDiv();

    // Cloud without the lowest point
    std::map<float, Point> cloud;
    for(auto point : points){
        if(!(point == lowest_point)){
            float angle = atan2(point.getY() - lowest_point.getY(), 
            point.getX() - lowest_point.getX());
            cloud.insert({angle, point});
        }        
    } 

    // Automatic sorted in map template
    std::vector <Point> sorted_points{lowest_point};
    std::cout << "Sorted cloud of points (without lowest point)" << std::endl << std::endl;
    for(auto point : cloud){
        std::cout << point.second << ": " << point.first << std::endl;
        sorted_points.push_back(point.second); // Add point to vector
    }
    printDiv();
    std::cout << "Determine left and right turns" << std::endl << std::endl;
    // Iterate all the sorted points to create new vector of points (left/right turn part)
    std::vector <Point> polygon_points; // lowest point is the first point
    for(auto it = sorted_points.begin(); it != sorted_points.end(); ++it){
        int index = it - sorted_points.begin();
        if(index < 2){
            polygon_points.push_back(*it);
        } else {
            Point p1 = polygon_points.at(polygon_points.size() - 2);
            Point p2 = polygon_points.at(polygon_points.size() - 1);
            Point p3 = *it;
            double cross_product = (p2.getX() - p1.getX()) * (p3.getY() - p2.getY())
                                - (p2.getY() - p1.getY()) * (p3.getX() - p2.getX());
            std::cout << "p1: " << p1 << std::endl;
            std::cout << "p2: " << p2 << std::endl;
            std::cout << "p3: " << p3 << std::endl;
            std::cout << "cross product: " << cross_product << std::endl << std::endl;
            if(cross_product < 0){
                polygon_points.pop_back();
                polygon_points.push_back(*it);
            } else {
                polygon_points.push_back(*it);
            }  
        }
    }
    printDiv();
    std::cout << "Points in the Convex Hull: " << std::endl << std::endl;
    for(auto point : polygon_points){
        std::cout << point << std::endl;
    }

    Polygon pol{polygon_points};    
    return pol;
}   