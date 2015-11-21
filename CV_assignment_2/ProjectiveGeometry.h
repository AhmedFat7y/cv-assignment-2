//
//  ProjectiveGeometry.h
//  CV_assignment_2
//
//  Created by MacBook Air on 11/19/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef __CV_assignment_2__ProjectiveGeometry__
#define __CV_assignment_2__ProjectiveGeometry__


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include "Camera.h"
#include "utilities.h"

using namespace cv;
using namespace std;

class ProjectiveGeometry {
public:
    Mat fundamentalMatrix;
    Camera * camera1;
    Camera * camera2;
    ProjectiveGeometry(Camera * c1, Camera * c2);
    Mat computeFundmentalMatrix();
    Mat computeProjectedImage(Mat img);
    vector<Mat> reconstruct3DPoints(vector<Mat> left_mats, vector<Mat> right_mats);
    static Mat getSkewMatrix(Mat mat);
};

#endif /* defined(__CV_assignment_2__ProjectiveGeometry__) */
