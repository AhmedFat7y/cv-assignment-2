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
    this->kappa = kappa;
    this->phi = phi;
    this->omega = omega;
    this->cameraCenter = cameraCenter;
    this->rotationMatrix = 0;
    this->p = 0;
    this->d = 0;
    computeAlphaU();
    computeAlphaV();
//    this->calibrationMatrix = this->computeCalibrationMatrix();
//    this->rotationMatrix = this->computeRotationMatrix();
//    this->d = this->computeDMatrix();
//    this->p = this->computePMatrix();
}

void Camera::computeAlphaU() {
    
    this->alphaU = focalLength * this->IW / this->FW;
}

void Camera::computeAlphaV() {
    
    this->alphaV = this->focalLength * this->IH / this->FH;
}

Mat Camera::computeRotationMatrix() {
    
    
    double *rkappa_data = new double[9] {
        cos(this->kappa), sin(this->kappa), 0,
        -sin(this->kappa), cos(this->kappa), 0,
        0, 0, 1};
    double *rphi_data = new double[9] {
        cos(this->phi), 0, -sin(this->phi),
        0, 1, 0,
        sin(this->phi), 0, cos(this->phi)};
    double *romega_data = new double[9] {
        1, 0, 0,
        0, cos(this->omega), sin(this->omega),
        0, -sin(this->omega), cos(this->omega)};
    
    Mat rkappa = Mat(3, 3, CV_64F, rkappa_data);
    Mat rphi = Mat(3, 3, CV_64F, rphi_data);
    Mat romega = Mat(3, 3, CV_64F, romega_data);
    Mat temp = rkappa * (rphi * romega);
    return temp;
}

Mat Camera::computeAR() {
    Mat temp = computeCalibrationMatrix() * computeRotationMatrix();
    return temp;
}

Mat Camera::computeCalibrationMatrix() {
    
    double * calibration_data = new double[9] {
        -1 * this->alphaU, 0, this->u0,
        0, this->alphaV, this->v0,
        0, 0, 1};
    
    Mat temp = Mat(3, 3, CV_64F, calibration_data);
    return temp;
}

Mat Camera::computePMatrix() {
    Mat AR = computeCalibrationMatrix() * computeRotationMatrix();
    Mat ARC = AR * computeCameraCenterMatrix(false);
    Mat p;
    hconcat(AR, ARC.mul(-1), p);
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