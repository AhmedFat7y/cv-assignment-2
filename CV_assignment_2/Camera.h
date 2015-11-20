//
//  Camera.h
//  CV_assignment_2
//
//  Created by MacBook Air on 11/19/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef __CV_assignment_2__Camera__
#define __CV_assignment_2__Camera__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

class Camera {
public:
    double focalLength;
    double u0;
    double v0;
    double FH;
    double FW;
    double IH;
    double IW;
    double kappa;
    double phi;
    double omega;
    double * cameraCenter;
    double alphaU;
    double alphaV;
    Mat rotationMatrix;
    Mat calibrationMatrix;
    Mat d, p;

    Camera(double focalLength, double u0, double v0, double FH, double FW, double IH, double IW, double kappa, double phi, double omega, double * cameraCenter);
    void computeAlphaU();
    void computeAlphaV();
    Mat computeRotationMatrix();
    Mat computeCalibrationMatrix();
    Mat computeAR();
    Mat computePMatrix();
    Mat computeDMatrix();
    Mat computeCameraCenterMatrix(bool isHomogenous);
    
};
#endif /* defined(__CV_assignment_2__Camera__) */
