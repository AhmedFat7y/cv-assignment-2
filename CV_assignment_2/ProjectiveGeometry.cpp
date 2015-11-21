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
}

Mat ProjectiveGeometry::computeFundmentalMatrix() {
    Mat e = camera2->computePMatrix() * camera1->computeCameraCenterMatrix(true); // e'
    Mat AR2 = camera2->computeAR();
    Mat AR = camera1->computeAR();
    Mat ex = getSkewMatrix(e); //skew matrix of e'
    fundamentalMatrix = (ex) * (AR2 * AR.inv());
    return fundamentalMatrix;
}
Mat ProjectiveGeometry::computeProjectedImage(Mat img) {
    Mat result = img.colRange(0, camera1->sizeX).rowRange(0, camera1->sizeY).clone();
    Mat result2 = result.clone();
    
    cout << "output image size: " << result.cols << ", " << result.rows << endl;
    Mat p = camera1->computePMatrix();
//    printMat("P: ", p);
    Mat p3x3;
    std::vector<Mat> mats = {p.colRange(0, 2), p.col(p.cols - 1)};
    hconcat(mats, p3x3);
////    printMat("P I nverse: ", pInverse);
//    Mat pInverse = p3x3.inv();
//    Mat destinationPoint = Mat(3, 1, CV_64F, Scalar(1));
//    Mat pixel = Mat(3, 1, CV_64F);
//    destinationPoint.at<double>(2, 0) = 1;
//    for (int destinationY = 0; destinationY < result.rows; destinationY++) {
//        for(int destinationX = 0; destinationX < result.cols; destinationX++) {
//            destinationPoint.at<double>(0, 0) = destinationX;
//            destinationPoint.at<double>(1, 0) = destinationY;
//            Mat sourcePoint = pInverse * destinationPoint;
//            for (int i = 0; i < sourcePoint.rows; i++) {
//                double temp = sourcePoint.at<double>(i, 0) / sourcePoint.at<double>(2,0);
//                sourcePoint.at<double>(i, 0) = isZero(temp)? 0 : temp;
//            }
//            double sourceX = sourcePoint.at<double>(0, 0), sourceY = sourcePoint.at<double>(1,0);
//            
////            printMat("Destination Point: ", destinationPoint);
////            printMat("Source Point: ", sourcePoint);
////            printMat("P Inverse: ", pInverse);
////            printMat("================", Mat());
//            if(sourceY >= 0 && sourceY < img.rows && sourceX >= 0 && sourceX < img.cols) {
//                result.at<Vec3b>(destinationY, destinationX)[0] = img.at<Vec3b>(sourceY, sourceX)[0];
//                result.at<Vec3b>(destinationY, destinationX)[1] = img.at<Vec3b>(sourceY, sourceX)[1];
//                result.at<Vec3b>(destinationY, destinationX)[2] = img.at<Vec3b>(sourceY, sourceX)[2];
//            } else  {
//                result.at<Vec3b>(destinationY, destinationX)[0] = 0;
//                result.at<Vec3b>(destinationY, destinationX)[1] = 0;
//                result.at<Vec3b>(destinationY, destinationX)[2] = 0;
//            }
//        }
//    }
    CvMat c1 = CvMat(img);
    CvMat c2 = CvMat(result2);
    CvMat c3 = CvMat(p3x3);
    cvWarpPerspective(&c1, &c2, &c3);
//    imshow("projected2", result2);
//    imshow("projected", result);
//    waitKey();
    return result2;
}
vector<Mat> ProjectiveGeometry::reconstruct3DPoints(vector<Mat> left_mats, vector<Mat> right_mats) {
    vector<Mat> results;
    Mat pInfinity1 = camera1->computeAR();
    Mat pInfinity2 = camera2->computeAR();
    Mat c1  = camera1->computeCameraCenterMatrix(false);
    Mat c2  = camera2->computeCameraCenterMatrix(false);
    Mat I = Mat::eye(3, 3, CV_64F);
    printMat("pInfinity: ", pInfinity1);
//    Mat temp;
//    normalize(Mat(3,1, CV_64F, new double[3] {5, 5, 5}), temp);
//    printMat("norm exp", temp);
    for (int i = 0 ; i < left_mats.size(); i++) {
        Mat mInfinity1 = pInfinity1.inv() * left_mats[i];
        Mat mInfinity2 = pInfinity2.inv() * right_mats[i];
        printMat("mInfinity1: ", mInfinity1);
        printMat("mInfinity2: ", mInfinity2);
        normalize(mInfinity1, mInfinity1);
        normalize(mInfinity2, mInfinity2);
        mInfinity1 = mInfinity1;
        mInfinity2 = mInfinity2;
        printMat("point left", left_mats[i]);
        printMat("point right", right_mats[i]);
        printMat("mInfinity1 norm: ", mInfinity1);
        printMat("mInfinity2 norm: ", mInfinity2);
        Mat m = (
                    (I - (mInfinity1 * mInfinity1.t()))
                    +
                    (I - (mInfinity2 * mInfinity2.t()))
                ).inv()
                *
                (
                   c1
                   +
                   c2
                   -
                   mInfinity1.mul(c1.t() * mInfinity1)
                   -
                   mInfinity2.mul(c2.t() * mInfinity2)
                );
        printMat("mat: ", m);
        results.push_back(m);
    }
    return results;
}

Mat ProjectiveGeometry::getSkewMatrix(Mat mat) {
    double * temp_data = new double[9]{
        0, -mat.at<double>(2,0), mat.at<double>(1,0),
        mat.at<double>(2,0), 0, -mat.at<double>(0,0),
        -mat.at<double>(1,0), mat.at<double>(0,0), 0,
    };
    
    return Mat(3, 3, CV_64F, temp_data);;
}