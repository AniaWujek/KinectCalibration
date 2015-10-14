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
		chessboard_height("chessboard_height", 0),
		chessboard_width("chessboard_width", 0) {
	registerProperty(chessboard_height);
	registerProperty(chessboard_width);

}

KinectCalibration::~KinectCalibration() {
}

void KinectCalibration::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_homogMatrix", &in_homogMatrix);
	registerStream("in_chessboard", &in_chessboard);
	registerStream("out_img", &out_img);
	// Register handlers
	registerHandler("KinectCalibration_Processor", boost::bind(&KinectCalibration::KinectCalibration_Processor, this));
	addDependency("KinectCalibration_Processor", &in_homogMatrix);
	addDependency("KinectCalibration_Processor", &in_img);
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
}



} //: namespace KinectCalibration
} //: namespace Processors
