//
//  field.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#ifndef field_hpp
#define field_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include <string> 

#include "cloud.hpp"
#include "distant_matrix.hpp"
#include "find_clasters.hpp"
#include "buffer.hpp"

using namespace std;

//CREATED BY ARSENIY KLEVAKIN 211 GROUP

class field{ //klass pola
public:
    find_clasters *FC;
    distant_matrix *DM;
    buffer buff;
    
    string state="ok";
    int countC=0;
    int countP=0;
    vector<cloud> clouds;
    vector<point*> all_points;
    
    void gencloud(double x, double y, double Dx, double Dy, int N);
    void cpycloud(string file);
    void gen_distant_M();
    void point_numbering();
    point* find_point_by_number(int n);
    
    vector<find_clasters> fin_cl;
    int FC_count = 0;
    
    void wave_algo(vector<vector<bool>> B, int p);
    void find_by_wave();
    
    void k_means(int k);
    double mod(double a);
    double D(point a, point b);
    void razmetka(int k, vector<point> c);
    vector<point *> find_group(int metka, vector<point *> g);
    point center_mass(vector<point*> g);
    
    void DBSCAN(double d, int k);
    
    void build_matix();
    
    void k_means_core(int k, int p);
    void razmetka_in_group(int p, vector<point*> dot, vector<point> c);
    vector<point> k_means_for_group(int k, vector<point*> group, int marker);
    void razmetka_by_core(int k, vector<vector<point>> core);
    void write_cores_to_file(vector<vector<point>> c, ofstream &out);
    
    void EM_algo(int k);
    vector<vector<double>> matrix_mult(vector<vector<double>> A, vector<vector<double>> B);
    double mah_dis(vector<vector<double>> sum, vector<double> mu, point a);
    double parametr_of_distribution(point a, vector<vector<double>> sum, vector<double> mu);
    double mat_D(vector<vector<double>> sum);
    vector<vector<double>> mat_inv(vector<vector<double>> a);
    void write_elips_to_file(vector<vector<double>> sum, vector<double> mu, int Num, ofstream &out);
    void razmetka_for_EM(int k);
    void write_dots_in_iteration(ofstream &out);
    
    void forel(vector<point*> dots, double R, int n);
    void zero_metka(vector<point*> dots);
    vector<point*> turtle(vector<point*> group, point c, double R);
    vector<point*> turtle_for_all_dots(point c, double R);
    vector<point*> find_all_points();
    void write_circle_to_file(ofstream &out, vector<point> c, double R);
    vector<point *> find_group_in_group(vector<point*> group, int metka);
    void write_centers_to_file(ofstream &out, vector<point> c);
    
    void ierarh();
    double D_clasters(claster A, claster B);
    claster merge_clasters(claster A, claster B);
    claster* find_claster_by_number(int n);
    
    void put_cloud_in_buth(int N);
    void put_field_in_buth();
    void shift_buth(point A);
    void homothety_buth(double k);
    void write_buffer_to_cloud();
};
#endif /* field_hpp */
