#include "DDImage/PlanarIop.h"
#include <opencv2/opencv.hpp>

using namespace DD::Image;

void CVMatToImagePlane(cv::Mat &inputMat, ImagePlane &outputPlane);
void IOPtoCVMat(Iop &inputIOP, cv::Mat &outputMat);