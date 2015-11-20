//
//  ProjectiveGeometry.cpp
//  CV_assignment_2
//
//  Created by MacBook Air on 11/19/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include "ProjectiveGeometry.h"

ProjectiveGeometry::ProjectiveGeometry(Camera * c1, Camera * c2) {
    camera1 = c1;
    camera2 = c2;
    fundamentalMatrix = computeFundmentalMatrix();
}

Mat ProjectiveGeometry::computeFundmentalMatrix() {
    Mat e = camera2->computePMatrix() * camera1->computeCameraCenterMatrix(true); // e'
    Mat AR2 = camera2->computeAR();
    Mat AR = camera1->computeAR();
    Mat ex = getSkewMatrix(e); //skew matrix of e'
    return (ex) * (AR2 * AR.inv());
}

Mat ProjectiveGeometry::getSkewMatrix(Mat mat) {
    double * temp_data = new double[9]{
        0, -mat.at<double>(2,0), mat.at<double>(1,0),
        mat.at<double>(2,0), 0, -mat.at<double>(0,0),
        -mat.at<double>(1,0), mat.at<double>(0,0), 0,
    };
    
    return Mat(3, 3, CV_64F, temp_data);;
}