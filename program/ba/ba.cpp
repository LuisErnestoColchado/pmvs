#include <iostream>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef float vertice[3];
int minC;
int L;
float meanErrorReprojection;

cv::Point InitializeLocations(vertice&,std::vector<float>&);
int calculateMinC(std::vector<int>);
cv::Point NCC(cv::Point,cv::Point);
void bundleAdjustment(std::vector<std::vector<float>>&);
void updateErrorReprojection(float&,float &);

//function for accurate calibration
void accurateCalibration(std::vector<std::vector<float>> &listParameters,
                        float errorReprojection,
                        std::vector<vertice> &P,
                        std::vector<int> &V,
                        std::vector<std::vector<cv::Point>> &p,
                        std::vector<int> C,
                        std::vector<std::vector<cv::Point>> &Q){
    for(int times = 0; times < 4;times++){
        L = MAX(0,floor(log(errorReprojection)));
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
        updateErrorReprojection(errorReprojection,meanErrorReprojection); //TODO std
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

void bundleAdjustment(std::vector<std::vector<float>> &listParameters){
    //TODO
}

void updateErrorReprojection(float& errorReprojection,float& mean){
    //TODO
}

int main(){

}
