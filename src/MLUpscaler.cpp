

#include "MLUpscaler.h"
#include "Utils.h"

#include <iostream>
#include <iomanip>

static const char *_scale[] = {"2x", "3x", "4x", nullptr};

MLUpscalerIop::MLUpscalerIop(Node *node) : PlanarIop(node)
{
  d_scale = 1;

  d_defaultChannels = Mask_RGB;
  d_defaultNumberOfChannels = d_defaultChannels.size();
  d_outputFormat.format(nullptr);
};

void MLUpscalerIop::knobs(Knob_Callback f)
{
  Enumeration_knob(f, &d_scale, _scale, "scale");
}

void MLUpscalerIop::_validate(bool for_real)
{
  // runs the validation method when input is connected or disconnected
  if (input(0))
  {
    input(0)->validate(for_real);
  }
  
  std::cout << "===================================================" << std::endl;
  std::cout << "Format size(): " << input0().format().size() << std::endl;
  std::cout << "Format area(): " << input0().format().area() << std::endl;
  std::cout << "Format height(): " << input0().format().height() << std::endl;
  std::cout << "Format width(): " << input0().format().width() << std::endl;
  std::cout << "Format w(): " << input0().format().w() << std::endl;
  std::cout << "Format h(): " << input0().format().h() << std::endl;
  std::cout << "Format center_x() : " << input0().format().center_x() << std::endl;
  std::cout << "Format center_y() : " << input0().format().center_y() << std::endl;
  std::cout << "Format pixel_aspect() : " << input0().format().pixel_aspect() << std::endl;
  std::cout << "Format t() : " << input0().format().t() << std::endl;
  std::cout << "Format r() : " << input0().format().r() << std::endl;
  std::cout << "Format x() : " << input0().format().x() << std::endl;
  std::cout << "Format y() : " << input0().format().y() << std::endl;

  info_.full_size_format(input0().full_size_format()); // size the default format to the project format
  info_.format(input0().format());                     // the size of the input image
  info_.channels(Mask_RGB);                            // only RGB channels are required
  info_.set(format());                                 // set the format
}

void MLUpscalerIop::getRequests(const Box &box, const ChannelSet &channels, int count, RequestOutput &reqData) const
{
  reqData.request(input(0), box, channels, count);
};

void MLUpscalerIop::renderStripe(ImagePlane &imagePlane)
{
  // input0().fetchPlane(imagePlane);

  // IOPtoCVMat(input0(), sourceMat);
  // cv::resize(sourceMat, sourceMat, cv::Size(), 2.0, 2.0, cv::INTER_LINEAR);
  // CVMatToImagePlane(sourceMat, imagePlane);

  input0().fetchPlane(imagePlane);

  imagePlane.makeUnique();
  imagePlane.makeWritable();

  Box box = imagePlane.bounds();

  foreach (z, imagePlane.channels())
  {
    for (Box::iterator it = box.begin(); it != box.end(); it++)
    {
      imagePlane.writableAt(it.x, it.y, imagePlane.chanNo(z)) *= 2;
    }
  }
}

static Iop *build(Node *node) { return new MLUpscalerIop(node); }
const Iop::Description MLUpscalerIop::d("MLUpscaler", "MLUpscaler", build);
