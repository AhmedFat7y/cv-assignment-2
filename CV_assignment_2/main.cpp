#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "ProjectiveGeometry.h"
#include "Camera.h"

using namespace cv;
using namespace std;


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
    
    Mat left_image = imread("/Users/MacBookAir/Documents/guc-projects/cv/CV_assignment_2/left.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    Mat right_image = imread("/Users/MacBookAir/Documents/guc-projects/cv/CV_assignment_2/right.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    
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
    Mat img = imread("/Users/MacBookAir/Documents/guc-projects/cv/CV_assignment_2/input.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    double sizeX = 200, sizeY = 200;
    double u0 = sizeY / 2, v0 = sizeX / 2;
    double alphaU = 300;
    double alphaV = 300;
    double pan = degToRad(0), tilt = degToRad(50), swing = degToRad(0);
    
    Camera camera(u0, v0, alphaU, alphaV, tilt, pan, swing, sizeX, sizeY, new double[4] {350, 0, 300, 1});

    
    ProjectiveGeometry pg(&camera , 0);
    
    Mat result = pg.computeProjectedImage(img);
    imshow("projected image", result);
}

int main( int argc, char** argv )
{
    q2();
    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}