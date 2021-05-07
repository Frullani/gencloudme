//
//  interface.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#include "interface.hpp"

//CREATED BY ARSENIY KLEVAKIN 211 GROUP

interface::interface(){
    in.open("in.txt");
    incon.open("loginter.txt", ios_base::app);
    incon <<endl  << "New session --- " << gettime();
}

string interface::get(){
    //char str[30];
    in >> com;
    //cout << com;
        //in.getline(in, com);
    //incon << "get command " << com <<" " << t << endl;
    return com;
}

void interface::readcom(){//schitivaem komandu
    int k;
    string line;
    if(com == "mfield"){
        rol.genfield();
        incon << "gen field" <<" --- "<<  gettime();
    }
    else {
        if(com == "mcloud"){
            //cout << "enter x, y, Dx, Dy and N" << endl;
            in >> x >> y >> Dx >> Dy >>N;
            incon << "gen cloud " << "arround (" << x <<"," << y <<") with Dispersia po x y " << Dx <<" " << Dy<< " with "<< N <<" points"<<" --- "<<  gettime();
             rol.gencloud(x, y, Dx, Dy, N);
        }
        else{
            if(com == "write"){ rol.write();
                incon << "get command " << com <<" --- " <<  gettime();
            }
            else{
                if(com == "gistoramm_cloud"){
                    //enter num of cloud, kolvo kuskov
                    in >> a >> k;
                    rol.gistogramm_cloud(rol.F->clouds[a], k);
                }
                else {
                    if(com == "gistoramm_all"){
                        in >> k;
                        rol.gistogramm_all(k);
                    }
                    else {
                        if(com == "matrix"){
                            rol.F->gen_distant_M();
                            incon << "build" << "distanse " <<com <<" --- " <<  gettime();
                        }
                        else{
                            if(com == "find_clasters_by_kmeans"){
                                in >> delta;
                                incon << "start " << com <<" clasters=" <<delta  <<" --- " << gettime();
                                rol.F->k_means(delta);
                                incon << "finish " << com <<" --- " << gettime();
                            }
                            else{
                                if(com == "find_clasters_by_volna"){
                                    in >> delta >> k;
                                    
                                    rol.F->point_numbering();
                                    rol.F->DBSCAN(delta, k);
                                    rol.F->find_by_wave();
                                    rol.write_clasters();
                                }
                                else{
                                    if(com=="find_clasters_by_kmeans_core"){
                                        in >> delta >> k;
                                        incon << "start " << com <<" clasters=" <<delta <<" " <<" cores=" <<delta <<" --- " << gettime();
                                        rol.F->point_numbering();
                                        rol.F->k_means_core(delta, k);
                                        rol.write_clasters();
                                        incon << "finish " << com <<" --- " << gettime();
                                    }
                                    
                                    else{
                                        if(com=="find_clasters_by_EM"){
                                            in >> k;
                                            incon << "start " << com <<" " <<" clasters=" <<k <<" --- " << gettime();
                                            rol.F->point_numbering();
                                            rol.F->EM_algo(k);
                                            rol.write_clasters();
                                            incon << "finish " << com <<" --- " << gettime();
                                        }
                                        else{
                                            if(com=="find_clasters_by_forel"){
                                                in >> delta >> k;
                                                rol.F->point_numbering();
                                                rol.F->all_points=rol.F->find_all_points();
                                                incon << "start " << com <<" " <<" clasters=" <<k <<"R= " <<delta <<" --- " << gettime();
                                                rol.F->forel(rol.F->all_points, delta, k);
                                                rol.write_clasters();
                                            }
                                            else {
                                                    if(com=="find_clasters_by_ierarh"){
                                                        incon << "start " << com <<" --- " << gettime();
                                                        rol.F->ierarh();
                                                        rol.write_clasters();
                                                        incon << "finish " << com <<" --- " << gettime();
                                                    }
                                                    else{
                                                        if(com=="exit"){
                                                            incon << com << " --- " <<gettime();
                                                        }
                                                        else{
                                                            if(com=="Cpycloud"){
                                                                in >> line;
                                                                rol.F->cpycloud(line);
                                                            }
                                                            else{
                                                            cout << "Do not understand" << endl;
                                                                incon << "Do not understand command = " << com <<" --- " <<gettime();}
                                                        }
                                                        
                                                    }
                                            }
                                        }
                                    }
                                }
                                    
                            }
                        }
                    }
                }
                
            }
        }
    }
    
}

char* interface::gettime(){
    char *t;
    time_t now = time(0);
    t = ctime(&now);
    return t;
}
