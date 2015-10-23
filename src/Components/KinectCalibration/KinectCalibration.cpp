/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "KinectCalibration.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace KinectCalibration {

KinectCalibration::KinectCalibration(const std::string & name) :
		Base::Component(name) ,
		chessboard_height("chessboard_height", 5),
		chessboard_width("chessboard_width", 6),
		square_width("square_width", 0.04),
		square_height("square_height", 0.04) {
	registerProperty(chessboard_height);
	registerProperty(chessboard_width);
	registerProperty(square_width);
	registerProperty(square_height);

}

KinectCalibration::~KinectCalibration() {
}

void KinectCalibration::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_depth", &in_depth);
	registerStream("in_homogMatrix", &in_homogMatrix);
	registerStream("in_chessboard", &in_chessboard);
	registerStream("out_img", &out_img);
	// Register handlers
	registerHandler("KinectCalibration_Processor", boost::bind(&KinectCalibration::KinectCalibration_Processor, this));
	addDependency("KinectCalibration_Processor", &in_homogMatrix);
	addDependency("KinectCalibration_Processor", &in_img);
	addDependency("KinectCalibration_Processor", &in_depth);
	addDependency("KinectCalibration_Processor", &in_chessboard);

}

bool KinectCalibration::onInit() {

	return true;
}

bool KinectCalibration::onFinish() {
	return true;
}

bool KinectCalibration::onStop() {
	return true;
}

bool KinectCalibration::onStart() {
	return true;
}

void KinectCalibration::KinectCalibration_Processor() {

    Types::Objects3D::Chessboard chessboard = in_chessboard.read();
    cv::Mat img = in_img.read().clone();
    cv::Mat depth = in_depth.read().clone();
    cv::Mat image(img.rows, img.cols, CV_8UC3, cv::Scalar::all(0));
    std::vector <cv::Point2f> imageCorners = chessboard.getImagePoints();
    std::vector <cv::Point3f> modelCorners = chessboard.getModelPoints();

    Types::HomogMatrix in_matrix = in_homogMatrix.read();
    cv::Mat_<double> matrix;
    matrix.create(4,4);
    for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
                matrix(i,j)=in_matrix(i, j);
			}
		}




    /*for (int i = 0; i < imageCorners.size(); ++i) {
        std::cout << imageCorners[i] << std::endl;
        cv::circle(image, imageCorners[i], 1, cv::Scalar(0,255,0), -1, 8, 0);
    }*/


    for(int i = 0; i < chessboard_height; ++i )
        for(int j = 0; j < chessboard_width; ++j) {
            cv::circle(image, imageCorners[i*chessboard_width+j],1,cv::Scalar(0,255,0),-1,8,0);
            if((i == 0 && j == 0) || (i == chessboard_height-1 && j == chessboard_width-1) || (i == chessboard_height-1 && j == 0) || (i == 0 && j == chessboard_width-1)) {
                cv::Mat point = (cv::Mat_<double>(4,1) << modelCorners[i*chessboard_width+j].x, modelCorners[i*chessboard_width+j].y, modelCorners[i*chessboard_width+j].z, 1);
                cv::Mat_<double> chess_point = matrix * point;
                std::ostringstream ss;
                ss << (int)(chess_point(2,0)*1000);
                std::string s(ss.str());
                std::ostringstream ss2;

                //cv::Mat_<cv::Vec3b> dpth = depth.clone();
                std::cout<< depth.at<unsigned short>(imageCorners[i*chessboard_width+j].y,imageCorners[i*chessboard_width+j].x) << std::endl;
                //std::cout<<dpth(imageCorners[i*chessboard_width+j].x,imageCorners[i*chessboard_width+j].y)<<std::endl;

                ss2 << depth.at<unsigned short>(imageCorners[i*chessboard_width+j].y,imageCorners[i*chessboard_width+j].x);
                std::string s2(ss2.str());
                cv::putText(image,s,imageCorners[i*chessboard_width+j], cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar::all(255), 1, 8, false);
                cv::putText(image,s2,cv::Point(imageCorners[i*chessboard_width+j].x,imageCorners[i*chessboard_width+j].y+30), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255,0,255), 1, 8, false);
            }

        }

    out_img.write(image);

}



} //: namespace KinectCalibration
} //: namespace Processors
