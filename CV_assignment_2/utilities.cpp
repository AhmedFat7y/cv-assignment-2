//
//  utilities.cpp
//  CV_assignment_2
//
//  Created by MacBook Air on 11/21/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include "utilities.h"

bool isZero(double x) {

    return abs(x) < 0.001;
}

void printMat(char const *msg, Mat mat) {
    cout << msg << endl << mat << endl << endl;
}