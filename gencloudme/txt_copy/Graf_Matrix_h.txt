//
//  Graf_Matrix.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#ifndef Graf_Matrix_hpp
#define Graf_Matrix_hpp

#include <stdio.h>
#include <vector>

//#include "field.hpp"
using namespace std;

class Graf_Matrix{
public:
    vector<vector<bool>> BI;
    void build_GM(vector<vector<double>> M, double beta);
};
#endif /* Graf_Matrix_hpp */
