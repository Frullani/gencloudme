//
//  Graf_Matrix.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#include "Graf_Matrix.hpp"

void Graf_Matrix::build_GM(vector<vector<double>> M, double beta){
    BI.resize(M.size());
    for(int i=0; i<M.size(); i++){
        BI[i].resize(M.size());
        for(int j=0; j<M.size(); j++){
            if(M[i][j]<beta){
                BI[i][j]=1;
            }
            else{
                BI[i][j]=0;
            }
        }
    }
    for(int i=0; i<M.size(); i++){
        BI[i][i]=0;
    }
    /*for(int i=0; i<M.size(); i++){
        for(int j=0; j<M[i].size(); j++){
            cout << BI[i][j] << " ";
        }
        cout << endl;
    }*/
}
