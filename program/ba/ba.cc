#include <iostream>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../base/image/image.h"
#include <string>
#include <fstream>
#include "../main/pmvs2.cc"

typedef float vertice[3];
int minC;
int L;
float meanErrorReprojection;

std::vector<float> points;
std::vector<float> normals;
int numberVisibility;
int numberNonVisibility;
std::vector<float> visibility;
std::vector<float> nonVisibility;

std::vector<std::vector<std::vector<float>>> imagePoints;
std::vector<std::vector<float>> worldPoints;
std::vector<std::vector<float>> worldNormals;
std::vector<int> visibilityImages;
std::vector<int> nonVsibilityImages;
std::vector<std::vector<float>> worldVisibility;
std::vector<std::vector<float>> worldNonVisibility;

std::vector<std::vector<std::vector<float>>> matrixParameters;

cv::Point InitializeLocations(vertice&,std::vector<float>&);
int calculateMinC(std::vector<int>);
cv::Point NCC(cv::Point,cv::Point);
void bundleAdjustment(std::vector<std::vector<float>>&);
void updateErrorReprojection(float&,float &);
void getParameters();
void createFileOption(std::string);
void readImage();
void resizeImage(std::vector<cv::Mat> images,int level);
void readPatch(const char * namefile);
void getLocations(std::vector<std::vector<float>> &,std::vector<std::vector<float>>,std::vector<std::vector<float>>);

void bundleAdjustment(std::vector<std::vector<float>> &listParameters){
    
}

void readPatch(std::string folder){
    std::ifstream infile(folder + "txt.txt");
    std::string line;
    int countLine = 0;
    while(std::getline(infile, line))
    {
        if(countLine > 2){
            int indexLine = 0;
            if(line .find_first_not_of(' ') != std::string::npos)
            {
                switch(indexLine){
                    case 0:
                        points.push_back(line[0]);
                        break;
                    case 1:
                        normals.push_back(line[0]);
                        break;
                    case 2:
                        numberVisibility = line[0];
                        break;
                    case 3:
                        visibility.push_back(line[0]);
                        break;
                    case 4: 
                        numberNonVisibility = line[0];
                        break;
                    case 5:
                        nonVisibility.push_back(line[0]);
                        break;
                    case 7:
                        worldPoints.push_back(points);
                        worldNormals.push_back(normals);
                        visibilityImages.push_back(numberVisibility);
                        nonVsibilityImages.push_back(numberNonVisibility);
                        worldVisibility.push_back(visibility);
                        worldNonVisibility.push_back(nonVisibility);
                        indexLine = 0;
                        break;
                }
            }
            indexLine+=1;
        }

        countLine+=1;
    }
}
void createFileOption(std::string folder,int level,int numImage){
    std::fstream file; 

    file.open(folder + "/option_" + std::to_string(level) + ".txt",std::ios::out); 
    
    if(!file) 
    { 
        std::cout << "Error in creating file!!!" << std::endl;
    } 
    else{
        file << "level " << level << std::endl;
        file << "csize 2" << std::endl;
        file << "threshold 0.7" << std::endl;
        file << "wsize 7" << std::endl;
        file << "minImageNum 3" << std::endl;
        file << "CPU 4" << std::endl;
        file << "useVisData 0" << std::endl;
        file << "sequence -1" << std::endl;
        file << "timage -1 0 " << numImage << std::endl;
        file << "oimage 0" << std::endl;
        std::cout <<"File created successfully." << std::endl; 
    }   
    file.close(); 
}
void functionModel(std::vector<float> &point,std::vector<float> worldPoint,std::vector<std::vector<float>> parameters){
    for(auto row : parameters){
        float sum = 0;
        int i = 0;
        for(float value : row){
            sum += value * worldPoint[i++];
        }
        point.push_back(sum);
    }
}
void getLocations(  std::vector<std::vector<std::vector<float>>> & imagePoints, 
                    std::vector<std::vector<float>> worldPoints, 
                    std::vector<std::vector<std::vector<float>>> matrixParameters){
    
    for(int i = 0;i < worldPoints.size();i++){
        for(int j = 0;j < imagePoints.size();j++){
            functionModel(imagePoints[i][j],worldPoints[i],matrixParameters[j]);
        }
    }
}

//function for accurate calibration
void accurateCalibration(std::string folder,std::vector<std::vector<float>> &listParameters,
                        float errorReprojection,
                        std::vector<vertice> &P,
                        std::vector<int> &V,
                        std::vector<std::vector<cv::Point>> &p,
                        std::vector<int> C,
                        std::vector<std::vector<cv::Point>> &Q){
    L = MAX(0,floor(log(errorReprojection)));
    for(int times = 0; times < 4;times++){
        //run PMVS with level L
        mainPMVSOptimization(folder,"option_" + L);
        //read result of PMVS
        readPatch(folder+"models/S.patch");
        //calculate features locations
        getLocations(imagePoints,worldPoints,matrixParameters);
        //for each features which whitin visibility
        for(int i = 0;i < worldPoints.size();i++){
            for(int j = 0;j < imagePoints[i].size();j++){
                for(int v = 0;v < worldVisibility[i].size();v++){
                    if(j == worldVisibility[i][v]){
                        //identify reference camera 

                        //for each features which whitout visibility 
                        for(int jn = 0;jn < imagePoints[i].size();jn++){
                            for(int vn = 0;vn < worldVisibility[i].size();vn++){
                                if(jn != worldVisibility[i][vn]){
                                    for(int l = L;l >= 0;l--){
                                        //use NCC
                                    }
                                }
                            }
                            
                        }
                    }
                }
            }
        }
        for(int i = 0;i < P.size();i++){
            for(int j = 0; j<P.size();j++){
                p[i][j] = InitializeLocations(P[i],listParameters[j]);
                if(j == V[i]){
                    minC = calculateMinC(C);
                    if(j != minC){
                        for(int k = L;k>0;k--){
                            p[i][j] = NCC(Q[i][j],Q[i][minC]);
                        }
                    }
                }         
            }

        }
        meanErrorReprojection += errorReprojection/(times+1);
        bundleAdjustment(listParameters);
        updateErrorReprojection(errorReprojection,meanErrorReprojection); 
    }

}

cv::Point InitializeLocations(vertice &vertice,std::vector<float> &parameters){
    //TODO
}

int calculateMinC(std::vector<int> C){
    //TODO
}

cv::Point NCC(cv::Point q,cv::Point q0){
    //TODO
}



void updateErrorReprojection(float& errorReprojection,float& mean){
    //TODO
}

int main(int argc,char * argv[]){
    
    std::string folder = argv[0];
    int errorReprojection = int(argv[1]);
    int numImage = int(argv[2]);
    int logError = log2(errorReprojection);
    if(logError > L) L = logError;
    createFileOption(folder,L,numImage);

    
    




}
