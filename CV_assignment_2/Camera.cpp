//
//  Camera.cpp
//  CV_assignment_2
//
//  Created by MacBook Air on 11/19/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include "Camera.h"

Camera::Camera(double focalLength, double u0, double v0, double FH, double FW, double IH, double IW, double kappa, double phi, double omega, double * cameraCenter){
    
    this->focalLength = focalLength;
    this->u0 = u0;
    this->v0 = v0;
    this->FH = FH;
    this->FW = FW;
    this->IH = IH;
    this->IW = IW;
    this->angle1 = kappa;
    this->angle2 = phi;
    this->angle3 = omega;
    this->isTiltPanSwing = false;
    this->cameraCenter = cameraCenter;
    this->p = 0;
    this->d = 0;
    this -> alphaU = -1 * computeAlphaU();
    this -> alphaV = computeAlphaV();
//    this->calibrationMatrix = this->computeCalibrationMatrix();
//    this->rotationMatrix = this->computeRotationMatrix();
//    this->d = this->computeDMatrix();
//    this->p = this->computePMatrix();
}

Camera::Camera(double u0, double v0, double alphaU, double alphaV, double tilt, double pan, double swing, int sizeX, int sizeY, double * cameraCenter) {
    this->focalLength = 0;
    this->u0 = u0;
    this->v0 = v0;
    this->alphaU = alphaU;
    this->alphaV = alphaV;
    this->isTiltPanSwing = true;
    this->angle1 = swing;
    this->angle2 = tilt;
    this->angle3 = pan;
    this->cameraCenter = cameraCenter;
    this-> sizeX = sizeX;
    this->sizeY = sizeY;
    this->rotationMatrix = 0;
    this->p = 0;
    this->d = 0;
}

double Camera::computeAlphaU() {
    
    return focalLength * this->IW / this->FW;
}

double Camera::computeAlphaV() {
    
    return this->focalLength * this->IH / this->FH;
}

Mat Camera::computeRotationMatrix() {
    
    return this->isTiltPanSwing? computePanTiltSwingRotation() : computeKappaPhiOmegaRotation();

}

Mat Camera::computeKappaPhiOmegaRotation() {
    double *rkappa_data = new double[9] {
        cos(this->angle1), sin(this->angle1), 0,
        -sin(this->angle1), cos(this->angle1), 0,
        0, 0, 1};
    double *rphi_data = new double[9] {
        cos(this->angle2), 0, -sin(this->angle2),
        0, 1, 0,
        sin(this->angle2), 0, cos(this->angle2)};
    double *romega_data = new double[9] {
        1, 0, 0,
        0, cos(this->angle3), sin(this->angle3),
        0, -sin(this->angle3), cos(this->angle3)};
    
    Mat rkappa = Mat(3, 3, CV_64F, rkappa_data);
    Mat rphi = Mat(3, 3, CV_64F, rphi_data);
    Mat romega = Mat(3, 3, CV_64F, romega_data);
    Mat temp = rkappa * (rphi * romega);
    return temp;
}


Mat Camera::computePanTiltSwingRotation() {
    double *rswing_data = new double[9] {
        cos(this->angle1), sin(this->angle1), 0,
        -sin(this->angle1), cos(this->angle1), 0,
        0, 0, 1};
    
    double *rtilt_data = new double[9] {
        1, 0, 0,
        0, cos(this->angle2), sin(this->angle2),
        0, -sin(this->angle2), cos(this->angle2)};
    
    double *rpan_data = new double[9] {
        cos(this->angle3), -sin(this->angle3), 0,
        sin(this->angle3), cos(this->angle3), 0,
        0, 0, 1};
    
    Mat rswing = Mat(3, 3, CV_64F, rswing_data);
    Mat rtilt = Mat(3, 3, CV_64F, rtilt_data);
    Mat rpan = Mat(3, 3, CV_64F, rpan_data);
    Mat temp = rswing * (rtilt * rpan);
    return temp;
}

Mat Camera::computeAR() {
    Mat temp = computeCalibrationMatrix() * computeRotationMatrix();
    return temp;
}

Mat Camera::computeCalibrationMatrix() {
    double * calibration_data = new double[9] {
        this->alphaU, 0, this->u0,
        0, this->alphaV, this->v0,
        0, 0, 1};
    
    Mat temp = Mat(3, 3, CV_64F, calibration_data);
    return temp;
}

Mat Camera::computePMatrix() {
    Mat AR = computeCalibrationMatrix() * computeRotationMatrix();
    printMat("A", computeCalibrationMatrix());
    printMat("R", computeRotationMatrix());
    Mat ARC = AR * computeCameraCenterMatrix(false);
    Mat p;
    hconcat(AR, ARC.mul(-1), p);
    printMat("P", p);
    return p;
}

Mat Camera::computeDMatrix() {
    Mat r = computeRotationMatrix();
    double * d_data = new double[16] {
        r.at<double>(0,0), r.at<double>(0,1), r.at<double>(0,2), this->cameraCenter[0],
        r.at<double>(1,0), r.at<double>(1,1), r.at<double>(1,2), this->cameraCenter[1],
        r.at<double>(2,0), r.at<double>(2,1), r.at<double>(2,2), this->cameraCenter[2],
        0, 0, 0, 1};
    Mat temp = Mat(4,4, CV_64F, d_data);
    return temp;
}

Mat Camera::computeCameraCenterMatrix(bool isHomogenous) {
    Mat temp = Mat(isHomogenous? 4: 3, 1, CV_64F, cameraCenter);
    return temp;
}