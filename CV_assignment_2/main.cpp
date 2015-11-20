#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "ProjectiveGeometry.h"
#include "Camera.h"

using namespace cv;
using namespace std;
#ifndef degToRad
    #define degToRad(c) (c) * 3.1415926 / 180
#endif

void printMat(char const *msg, Mat mat) {
    cout << msg << endl << mat << endl << endl;
}

int main( int argc, char** argv )
{
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
//    double alphau = f * IW / FW , alphav = f * IH / FH ;
//
//    Mat p = Mat::zeros(3, 4, CV_64F);
//    p.at<double>(0,0) = 1;
//    p.at<double>(1,1) = 1;
//    p.at<double>(2,2) = 1;
//    
    double left_camera_center_data[] = {-1535.21, 1720.84, 1693.22, 1};
    double left_omega = degToRad(-35.16), left_phi = degToRad(-46.77), left_kappa = degToRad(-155.57);
    double right_camera_center_data[] = {-1694.56, -142.25, 1585.19, 1};
    double right_omega = degToRad(25.03), right_phi = degToRad(-55.56), right_kappa = degToRad(-47.08);
//
//    Mat right_camera_center = Mat(4, 1, CV_64F, right_camera_center_data);
//    Mat left_camera_center = Mat(4, 1, CV_64F, left_camera_center_data);
//    
//    
//    double calibration_data[] = {
//        -1 * alphau, 0, u0,
//        0, alphav, v0,
//        0, 0, 1};
//    
//    Mat calibration_matrix = Mat(3, 3, CV_64F, calibration_data);
//    printMat("Calibration Matrix: ", calibration_matrix);
//    double left_rkappa_data[] = {
//        cos(left_kappa), sin(left_kappa), 0,
//        -sin(left_kappa), cos(left_kappa), 0,
//        0, 0, 1};
//    double left_rphi_data[] = {
//        cos(left_phi), 0, -sin(left_phi),
//        0, 1, 0,
//        sin(left_phi), 0, cos(left_phi)};
//    double left_romega_data[] = {
//        1, 0, 0,
//        0, cos(left_omega), sin(left_omega),
//        0, -sin(left_omega), cos(left_omega)};
//    
//    Mat left_rkappa = Mat(3, 3, CV_64F, left_rkappa_data);
//    Mat left_rphi = Mat(3, 3, CV_64F, left_rphi_data);
//    Mat left_romega = Mat(3, 3, CV_64F, left_romega_data);
//    Mat left_r = left_rkappa * (left_rphi * left_romega);
//    
//    double right_rkappa_data[] = {
//        cos(right_kappa), sin(right_kappa), 0,
//        -sin(right_kappa), cos(right_kappa), 0,
//        0, 0, 1};
//    double right_rphi_data[] = {
//        cos(right_phi), 0, -sin(right_phi),
//        0, 1, 0,
//        sin(right_phi), 0, cos(right_phi)};
//    double right_romega_data[] = {
//        1, 0, 0,
//        0, cos(right_omega), sin(right_omega),
//        0, -sin(right_omega), cos(right_omega)};
//    
//    Mat right_rkappa = Mat(3, 3, CV_64F, right_rkappa_data);
//    Mat right_rphi = Mat(3, 3, CV_64F, right_rphi_data);
//    Mat right_romega = Mat(3, 3, CV_64F, right_romega_data);
//    Mat right_r = right_rkappa * (right_rphi * right_romega);
////    double left_d_data[] = {
////        left_r.at<double>(0,0), left_r.at<double>(0,1), left_r.at<double>(0,2), left_camera_center_data[0],
////        left_r.at<double>(1,0), left_r.at<double>(1,1), left_r.at<double>(1,2), left_camera_center_data[1],
////        left_r.at<double>(2,0), left_r.at<double>(2,1), left_r.at<double>(2,2), left_camera_center_data[2],
////        0, 0, 0, 1
////    };
////    Mat left_d = Mat(4,4, CV_64F, left_d_data);
////    
////    double right_d_data[] = {
////        right_r.at<double>(0,0), right_r.at<double>(0,1), right_r.at<double>(0,2), right_camera_center_data[0],
////        right_r.at<double>(1,0), right_r.at<double>(1,1), right_r.at<double>(1,2), right_camera_center_data[1],
////        right_r.at<double>(2,0), right_r.at<double>(2,1), right_r.at<double>(2,2), right_camera_center_data[2],
////        0, 0, 0, 1
////    };
////    Mat right_d = Mat(4,4, CV_64F, right_d_data);
//    
//    //(P = [AR|-ARC])
//
//    Mat left_p = calibration_matrix * left_r;
//    Mat left_tempAC = left_p * Mat(3, 1, CV_64F, left_camera_center_data);
//    hconcat(left_p, left_tempAC.mul(-1), left_p);
//    
//
//    Mat right_p = calibration_matrix * right_r;
//    Mat right_tempAC = right_p * Mat(3, 1, CV_64F, right_camera_center_data);
//    hconcat(right_p, right_tempAC.mul(-1), right_p);
//
//    Mat temp1 = right_p * left_camera_center; // e'
//
//    double temp4_data[] = {
//        0, -temp1.at<double>(2,0), temp1.at<double>(1,0),
//        temp1.at<double>(2,0), 0, -temp1.at<double>(0,0),
//        -temp1.at<double>(1,0), temp1.at<double>(0,0), 0,
//    };
//
//    Mat temp4 = Mat(3, 3, CV_64F, temp4_data);     //skew matrix of e'
//    Mat temp2 = calibration_matrix * right_r;
//    Mat temp3 = calibration_matrix * left_r;
//    Mat fundmental_matrix = (temp4) * (temp2 * temp3.inv());
//    Mat AR = calibration_matrix * left_r;
//    Mat AR2 = calibration_matrix * right_r;
//
//    printMat("Fundmental Matrix", fundmental_matrix);
//    printMat("A: ", calibration_matrix);
//    printMat("R: ", left_r);
//    printMat("R2: ", right_r);
//    printMat("AR: ", AR);
//    printMat("AR2: ", AR2);
//    printMat("P: ", left_p);
//    printMat("P2: ", right_p);
//    printMat("C: ", left_camera_center);
//    printMat("C2: ", right_camera_center);
    //(double focalLength, double u0, double v0, double FH, double FW, double IH, double IW, double kappa, double phi, double omega, double * cameraCenter)
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
//    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}