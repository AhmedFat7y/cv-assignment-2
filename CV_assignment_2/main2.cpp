////
////  main2.cpp
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
//    Mat img_1 = imread("/Users/MacBookAir/Documents/guc-projects/cv/CV_assignment_2/left.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
//    Mat img_2 = imread("/Users/MacBookAir/Documents/guc-projects/cv/CV_assignment_2/right.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
//    
//    
//    if( !img_1.data || !img_2.data )
//    { return -1; }
//    
//    //-- Step 1: Detect the keypoints using SURF Detector
//    int minHessian = 100;
//    
//    //SurfFeatureDetector detector(minHessian);
//    Ptr<xfeatures2d::SURF> surf = xfeatures2d::SURF::create(minHessian);
//    
//    // note, that it's also far more efficient, to compute keypoints and descriptors in one go.
//    
//    std::vector<KeyPoint> keypoints_object, keypoints_scene;
//    Mat descriptors_object, descriptors_scene;
//    std::vector<KeyPoint> keypoints_1, keypoints_2;
//    
//    surf->detect(img_1, keypoints_1);
//    surf->detect(img_2, keypoints_2);
//    
//    //-- Step 2: Calculate descriptors (feature vectors)
//    Ptr<SURF> extractor = SURF::create();
//    Mat descriptors_1, descriptors_2;
//    extractor->compute( img_1, keypoints_1, descriptors_1 );
//    extractor->compute( img_2, keypoints_2, descriptors_2 );
//    
//    //-- Step 3: Matching descriptor vectors with a brute force matcher
//    BFMatcher matcher(NORM_L1, true);
//    std::vector< DMatch > matches;
//    matcher.match( descriptors_1, descriptors_2, matches );
//    
//    //-- Draw matches
//    Mat img_matches;
//    drawMatches( img_1, keypoints_1, img_2, keypoints_2, matches, img_matches );
//    //-- Show detected matches
//    namedWindow( "Matches", CV_WINDOW_NORMAL );
//    imshow("Matches", img_matches );
//    waitKey(0);
//    
//    
//    //-- Step 4: calculate Fundamental Matrix
//    vector<Point2f>imgpts1,imgpts2;
//    for( unsigned int i = 0; i<matches.size(); i++ )
//    {
//        // queryIdx is the "left" image
//        imgpts1.push_back(keypoints_1[matches[i].queryIdx].pt);
//        // trainIdx is the "right" image
//        imgpts2.push_back(keypoints_2[matches[i].trainIdx].pt);
//    }
//    Mat F =  findFundamentalMat  (imgpts1, imgpts2, CV_RANSAC);
//    Mat Ft = F.t();
//    printMat("Fundemental Matrix", F);
//    printMat("Fundemental Matrix T", Ft);
//    //-- Step 5: calculate Essential Matrix
//    
//    double data[] = {1189.46 , 0.0, 805.49,
//        0.0, 1191.78, 597.44,
//        0.0, 0.0, 1.0};//Camera Matrix
//    Mat K(3, 3, CV_64F, data);
//    Mat_<double> E = K.t() * F * K; //according to HZ (9.12)
//    
//    //-- Step 6: calculate Rotation Matrix and Translation Vector
//    Matx34d P;
//    Matx34d P1;
//    //decompose E to P' , HZ (9.19)
//    SVD svd(E,SVD::MODIFY_A);
//    Mat svd_u = svd.u;
//    Mat svd_vt = svd.vt;
//    Mat svd_w = svd.w;
//    Matx33d W(0,-1,0,1,0,0,0,0,1);//HZ 9.13
//    Mat_<double> R = svd_u * Mat(W) * svd_vt; //HZ 9.19
//    Mat_<double> t = svd_u.col(2); //u3
//    
////    if (!CheckCoherentRotation (R)) {
////        std::cout<<"resulting rotation is not coherent\n";
////        P1 = 0;
////        return 0;
////    }
//    
//    P1 = Matx34d(R(0,0),R(0,1),R(0,2),t(0),
//                 R(1,0),R(1,1),R(1,2),t(1),
//                 R(2,0),R(2,1),R(2,2),t(2));
//    
//    //-- Step 7: Reprojection Matrix and rectification data
//    Mat R1, R2, P1_, P2_, Q;
//    Rect validRoi[2];
//    double dist[] = { -0.03432, 0.05332, -0.00347, 0.00106, 0.00000};
//    Mat D(1, 5, CV_64F, dist);
//    
//    stereoRectify(K, D, K, D, img_1.size(), R, t, R1, R2, P1_, P2_, Q, CV_CALIB_ZERO_DISPARITY, 1, img_1.size(),  &validRoi[0], &validRoi[1] );
//}