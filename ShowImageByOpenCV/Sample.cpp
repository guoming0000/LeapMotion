/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <string.h>
#include "Leap.h"
#include "opencv2/opencv.hpp"

using namespace Leap;
using namespace cv;
class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
  private:
};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  ImageList images = frame.images();
  Mat leftMat;
  Mat rightMat;
  if (images.count() >= 2)
  {
	  leftMat = Mat(images[0].height(), images[0].width(), CV_8UC1, (void *)images[0].data());
	  rightMat = Mat(images[1].height(), images[1].width(), CV_8UC1, (void *)images[0].data());
	  imshow("leftMat", leftMat);
	  imshow("rightMat", rightMat);
	  waitKey(1);
  }

}
#include <windows.h>
int main(int argc, char** argv) {
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  // Have the sample listener receive events from the controller
  controller.addListener(listener);
  controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
  controller.setPolicy(Leap::Controller::POLICY_IMAGES);
  Sleep(1000);
  std::cout << "is background policy set success : " << controller.isPolicySet(Leap::Controller::POLICY_BACKGROUND_FRAMES)<<std::endl;
  std::cout << "is image policy set success : " << controller.isPolicySet(Leap::Controller::POLICY_IMAGES)<<std::endl;

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
