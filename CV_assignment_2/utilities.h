//
//  utilities.h
//  CV_assignment_2
//
//  Created by MacBook Air on 11/21/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef CV_assignment_2_utilities_h
#define CV_assignment_2_utilities_h

#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define degToRad(c) ((c) * 3.1415926 / 180)

bool isZero(double x);

void printMat(char const *msg, Mat mat);

#endif
