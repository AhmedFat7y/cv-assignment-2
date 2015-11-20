////
////  main3.cpp
////  CV_assignment_2
////
////  Created by MacBook Air on 11/18/15.
////  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
////
//#include <iostream>
//
//#include "opencv2/core.hpp"
//#include "opencv2/features2d.hpp"
//#include <opencv2/features2d/features2d.hpp>
//#include "opencv2/highgui.hpp"
//#include "opencv2/calib3d.hpp"
//#include "opencv2/xfeatures2d.hpp"
//#include "opencv2/xfeatures2d/nonfree.hpp"
//#include <vector>
//
//using namespace std;
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//void printMat(char const *msg, Mat &mat) {
//    cout << msg << endl << mat << endl << endl;
//}
//
//int main() {
//    vector<KeyPoint> kps1;
//    vector<KeyPoint> kps2;
//    Mat img_1 = imread("/Users/MacBookAir/Documents/guc-projects/cv/CV_assignment_2/left.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
//    Mat img_2 = imread("/Users/MacBookAir/Documents/guc-projects/cv/CV_assignment_2/right.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
//
//
//    if( !img_1.data || !img_2.data )
//    { return -1; }
//
//    //-- Step 1: Detect the keypoints using SURF Detector
//    cv::Mat descriptors1, descriptors2;
//    // pointer to the feature point detector object
//    cv::Ptr<cv::FeatureDetector> fd;
//    // pointer to the feature descriptor extractor object
//    cv::Ptr<cv::DescriptorExtractor> de;
//    fd = new surf::SurfFeatureDetector();
//    de = new SurfDescriptorExtractor();
//    
//    fd.detect(img_1, kps1);
//    fd.detect(img_2, kps2);
//    de.compute(img_1, kps1, descriptors1);
//    de.compute(img_2, kps2, descriptors2);
//    
//        Mat F =  findFundamentalMat  (descriptors1, descriptors2, CV_FM_RANSAC);
//        Mat Ft = F.t();
//        printMat("Fundemental Matrix", F);
//        printMat("Fundemental Matrix T", Ft);
//    
//}