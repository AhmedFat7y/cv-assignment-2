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

Mat ProjectiveGeometry::getSkewMatrix(Mat mat) {
    double * temp_data = new double[9]{
        0, -mat.at<double>(2,0), mat.at<double>(1,0),
        mat.at<double>(2,0), 0, -mat.at<double>(0,0),
        -mat.at<double>(1,0), mat.at<double>(0,0), 0,
    };
    
    return Mat(3, 3, CV_64F, temp_data);;
}