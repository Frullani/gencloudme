//
//  point.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 12.10.2020.
//

#ifndef point_hpp
#define point_hpp

#include <iostream>
#include <stdio.h>

using namespace std;
//CREATED BY ARSENIY KLEVAKIN 211 GROUP
class point{ //klas tocki
public:
    double x, y;
    double color=0;
    int priv_state, new_state=0; //for volnovy algroritm
    int NumP;
    
    int metka=100; //for k_means
    
    int marker=3; //for dbscan 1-kornevaya 2-pereferiynaya 3-dust
    
    void in(double X, double Y);
    void out();
};
#endif /* point_hpp */
