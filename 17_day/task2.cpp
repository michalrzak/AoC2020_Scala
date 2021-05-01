#include <map>
#include <tuple>
#include <fstream>
#include <iostream>

int main(){

    std::fstream input;
    input.open("input.txt");


    //environment variables
    std::map<std::tuple<int, int, int, int>, int> space; //x, y, z, w
    int xmin {0};
    int xmax {1};
    int wmin {0};
    int wmax {1};
    int ymin {0};
    int ymax {0};
    int zmin {0};
    int zmax {0};


    std::string line;
    int y {0};
    while(getline(input, line)){
        for (int z {0}; z < line.size(); ++z){
            space[{0, y, z, 0}] = line.at(z) == '#' ? 1 : 0;
        }
        ++y;
    }
    ymax = y;
    zmax = line.size();


    /*for (int xi {xmin}; xi < xmax; ++xi){
        std::cout << xi << '\n';
        for (int yi {ymin}; yi < ymax; ++yi){
            for (int zi {zmin}; zi < zmax; ++zi){
                std::cout << space[{xi, yi, zi}];
            }
            std::cout << '\n';
        }
    }
    std::cout << xmin << ' ' << xmax << '\n';
    std::cout << ymin << ' ' << ymax << '\n';
    std::cout << zmin << ' ' << zmax << '\n';   
*/

    for (int k {0}; k < 6; ++k){
        std::map<std::tuple<int, int, int, int>, int> neighbours;
        int xmin2 {xmin};
        int xmax2 {xmax};
        int ymin2 {ymin};
        int ymax2 {ymax};
        int zmin2 {zmin};
        int zmax2 {zmax};
        int wmin2 {wmin};
        int wmax2 {wmax};

        for (int xi {xmin}; xi < xmax; ++xi)
            for (int yi {ymin}; yi < ymax; ++yi)
                for (int zi {zmin}; zi < zmax; ++zi)
                    for (int wi {wmin}; wi < wmax; ++wi)
                        if (space[{xi, yi, zi, wi}] == 1){
                            if (xi-1 < xmin2) xmin2 = xi-1;
                            if (xi+1 >= xmax2) xmax2 = xi+2;
                            if (yi-1 < ymin2) ymin2 = yi-1;
                            if (yi+1 >= ymax2) ymax2 = yi+2;
                            if (zi-1 < zmin2) zmin2 = zi-1;
                            if (zi+1 >= zmax2) zmax2 = zi+2; 
                            if (wi-1 < wmin2) wmin2 = wi-1;
                            if (wi+1 >= wmax2) wmax2 = wi+2; 


                            for (int xj {-1}; xj <= 1; ++xj)
                                for (int yj {-1}; yj <= 1; ++yj)
                                    for (int zj {-1}; zj <= 1; ++zj)
                                        for (int wj {-1}; wj <= 1; ++wj) {
                                            if (xj == 0 && yj == 0 && zj == 0 && wj == 0) continue;

                                            neighbours[{xi+xj, yi+yj, zi+zj, wi+wj}] += 1;
                                            //std::cout << "i am gamming B) on " << xi+xj << ' ' << yi+yj << ' ' << zi+zj << '\n';
                                        }
                            
                        }
        
        xmin = xmin2;
        xmax = xmax2;
        ymin = ymin2;
        ymax = ymax2;
        zmin = zmin2;
        zmax = zmax2;
        wmin = wmin2;
        wmax = wmax2;

        for (int xi {xmin}; xi < xmax; ++xi)
            for (int yi {ymin}; yi < ymax; ++yi)
                for (int zi {zmin}; zi < zmax; ++zi)
                    for (int wi {wmin}; wi < wmax; ++wi){
                        if (space[{xi, yi, zi, wi}] == 1 && !(neighbours[{xi, yi, zi, wi}] == 2 || neighbours[{xi, yi, zi, wi}] == 3)){
                            std::cout << xi << ' ' << yi << ' ' << zi << '\n' << neighbours[{xi, yi, zi, wi}] << '\n' << space[{xi, yi, zi, wi}] << '\n';
                            space[{xi, yi, zi, wi}] = 0;
                        }
                        else if (space[{xi, yi, zi, wi}] == 0 && neighbours[{xi, yi, zi, wi}] == 3)
                            space[{xi, yi, zi, wi}] = 1;
                    }
    
        /*for (int xi {xmin}; xi < xmax; ++xi){
        std::cout << xi << '\n';
        for (int yi {ymin}; yi < ymax; ++yi){
            for (int zi {zmin}; zi < zmax; ++zi){
                std::cout << neighbours[{xi, yi, zi}];
            }
            std::cout << '\n';
        }
    }*/


    }

    int sum {0};

    for (int xi {xmin}; xi < xmax; ++xi){
        std::cout << xi << '\n';
        for (int yi {ymin}; yi < ymax; ++yi){
            for (int zi {zmin}; zi < zmax; ++zi){
                for (int wi {wmin}; wi < wmax; ++wi){
                    sum += space[{xi, yi, zi, wi}];
                    std::cout << space[{xi, yi, zi, wi}];
                }
                std::cout << '\n';
            }
        }
    }

    std::cout << "The result is: " << sum << '\n';
    std::cout << xmin << ' ' << xmax << '\n';
    std::cout << ymin << ' ' << ymax << '\n';
    std::cout << zmin << ' ' << zmax << '\n';
    
    return 0;
}

