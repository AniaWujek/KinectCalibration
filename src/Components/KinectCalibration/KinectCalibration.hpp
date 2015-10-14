/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef KINECTCALIBRATION_HPP_
#define KINECTCALIBRATION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"
#include "Types/Objects3D/Chessboard.hpp"
#include "Types/HomogMatrix.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace KinectCalibration {

/*!
 * \class KinectCalibration
 * \brief KinectCalibration processor class.
 *
 *
 */
class KinectCalibration: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	KinectCalibration(const std::string & name = "KinectCalibration");

	/*!
	 * Destructor
	 */
	virtual ~KinectCalibration();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	// Input data streams
	Base::DataStreamIn<cv::Mat> in_img;
	Base::DataStreamIn<Types::HomogMatrix> in_homogMatrix;
	Base::DataStreamIn<Types::Objects3D::Chessboard> in_chessboard;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers

	// Properties
	Base::Property<int> chessboard_height;
	Base::Property<int> chessboard_width;


	// Handlers
	void KinectCalibration_Processor();

};

} //: namespace KinectCalibration
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("KinectCalibration", Processors::KinectCalibration::KinectCalibration)

#endif /* KINECTCALIBRATION_HPP_ */
