#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "ProjectiveGeometry.h"
#include "Camera.h"

using namespace cv;
using namespace std;

string path = "/Users/MacBookAir/Documents/guc-projects/cv/CV_assignment_2/";
void q1() {
    /*
     focal length = 4.3 mm
     principal point = [320, 240]
     FH=2.7446 mm
     FW=3.5311 mm
     
     
     left (x, y, z, omega, phi, kappa) ==> mm and degrees
     -1535.21 1720.84 1693.22 -35.16 -46.77 -155.57
     
     
     right (x, y, z, omega, phi, kappa)
     -1694.56 -142.25 1585.19 25.03 -55.56 -47.08
     */
    Mat left_image = imread(path + "left.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    Mat right_image = imread(path + "right.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    
    double f = 4.3;
    double u0 = 320, v0 = 240;
    double FH = 2.7446;
    double FW = 3.5311;
    double IH = left_image.rows, IW = left_image.cols;
    double left_camera_center_data[] = {-1535.21, 1720.84, 1693.22, 1};
    double left_omega = degToRad(-35.16), left_phi = degToRad(-46.77), left_kappa = degToRad(-155.57);
    double right_camera_center_data[] = {-1694.56, -142.25, 1585.19, 1};
    double right_omega = degToRad(25.03), right_phi = degToRad(-55.56), right_kappa = degToRad(-47.08);
    
    Camera camera1(f, u0, v0, FH, FW, IH, IW, left_kappa, left_phi, left_omega, left_camera_center_data);
    Camera camera2(f, u0, v0, FH, FW, IH, IW, right_kappa, right_phi, right_omega, right_camera_center_data);
    
    ProjectiveGeometry pg(&camera1, &camera2);
    
    Mat fundamental = pg.computeFundmentalMatrix();
    
    printMat("C: ", camera1.computeCameraCenterMatrix(false));
    printMat("C2: ", camera2.computeCameraCenterMatrix(false));
    printMat("A: ", camera1.computeCalibrationMatrix());
    printMat("A2: ", camera2.computeCalibrationMatrix());
    printMat("R: ", camera1.computeRotationMatrix());
    printMat("R2: ", camera2.computeRotationMatrix());
    printMat("AR: ", camera1.computeAR());
    printMat("AR2: ", camera2.computeAR());
    printMat("P: ", camera1.computePMatrix());
    printMat("P2: ", camera2.computePMatrix());
    printMat("Fundmental Matrix", pg.computeFundmentalMatrix());
    printMat("Fundmental Matrix", fundamental);
    ////    F=[e']x[A'R'][AR]^-1        //sent by Nadine Adel Zayed (not zayed bta3 el emirate)
}
void q2() {
//    X, Y, Z = 350, 0, 300
//    Tilt = 50
//    Pan = 0
//    Swing = 0
//    alpha_u = alpha_v = 100
//    SizeX = sizeY = 200
    
    Mat img = imread(path + "input.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    int sizeX = 200, sizeY = 200;
    double u0 = sizeY / 2, v0 = sizeX / 2;
    double alphaU = 100;
    double alphaV = 100;
    double pan = degToRad(0), tilt = degToRad(50), swing = degToRad(0);
    Camera camera(u0, v0, alphaU, alphaV, tilt, pan, swing, sizeX, sizeY, new double[4] {350, 0, 300, 1});

    
    ProjectiveGeometry pg(&camera , 0);
    
    Mat result = pg.computeProjectedImage(img);
    imshow("projected image", result);
//    printMat("C: ", camera.computeCameraCenterMatrix(false));
//    printMat("A: ", camera.computeCalibrationMatrix());
//    printMat("R: ", camera.computeRotationMatrix());
//    printMat("AR: ", camera.computeAR());
//    printMat("P: ", camera.computePMatrix());


}

void q3() {
//    You can use the following values to test your implementation for question 3:    
//    Left: [543, 207], Right: [393, 431], 3D: [9.85, -0.90, 0.72]
//    Left: [422, 233], Right: [330, 334], 3D: [299.07, 324.69, 15.28]
//    Left: [392, 122], Right: [367, 215], 3D: [294.90, 312.07, 496.07]
//    Left: [260, 209], Right: [204, 148], 3D: [301.40, 875.92, 514.52]
//    Left: [339, 268], Right: [233, 262], 3D: [289.37, 706.35, 144.88]
    
    Mat img = imread(path + "right.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    
    double f = 4.3;
    double u0 = 320, v0 = 240;
    double FH = 2.7446;
    double FW = 3.5311;
    double IH = img.rows, IW = img.cols;
    double left_camera_center_data[] = {-1535.21, 1720.84, 1693.22, 1};
    double left_omega = degToRad(-35.16), left_phi = degToRad(-46.77), left_kappa = degToRad(-155.57);
    double right_camera_center_data[] = {-1694.56, -142.25, 1585.19, 1};
    double right_omega = degToRad(25.03), right_phi = degToRad(-55.56), right_kappa = degToRad(-47.08);
    
    Camera camera1(f, u0, v0, FH, FW, IH, IW, left_kappa, left_phi, left_omega, left_camera_center_data);
    Camera camera2(f, u0, v0, FH, FW, IH, IW, right_kappa, right_phi, right_omega, right_camera_center_data);
    
    ProjectiveGeometry pg(&camera1 , &camera2);
    
    double * left_data = new double [10] {543, 207, 422, 233, 392, 122, 260, 209, 339, 268};
    double * right_data = new double [10] {393, 431, 330, 334, 367, 215, 204, 148, 233, 262};
    
    
    vector<Mat> left_mats;
    vector<Mat> right_mats;
    
    for (int i = 0 ; i < 10 - 1; i += 2 ) {
        left_mats.push_back(Mat(3, 1, CV_64F, new double[3] {left_data[i], left_data[i + 1], 1}));
        right_mats.push_back(Mat(3, 1, CV_64F, new double[3] {right_data[i], right_data[i + 1], 1}));
    }
    vector<Mat> resultPoints = pg.reconstruct3DPoints(left_mats, right_mats);
    
}


int main( int argc, char** argv )
{
    q3();
//    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}