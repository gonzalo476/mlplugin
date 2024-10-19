

#include "MLUpscaler.h"
#include "Utils.h"

#include <iostream>
#include <iomanip>

static const char *_scale[] = {"2x", "3x", "4x", nullptr};

MLUpscalerIop::MLUpscalerIop(Node *node) : PlanarIop(node)
{
  d_scale = 1;

  d_defaultChannels = Mask_RGBA;
  d_defaultNumberOfChannels = d_defaultChannels.size();
  d_outputFormat.format(nullptr);
};

void MLUpscalerIop::knobs(Knob_Callback f)
{
  Enumeration_knob(f, &d_scale, _scale, "scale");
}

void MLUpscalerIop::_validate(bool for_real)
{

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

  Format format_ = input0().format();

  // info_.full_size_format(customFormat); // size the proxy format
  info_.format(input0().format()); // the size of the image
  info_.channels();
  info_.set(format());
}

void MLUpscalerIop::getRequests(const Box &box, const ChannelSet &channels, int count, RequestOutput &reqData) const
{
  reqData.request(input(0), box, channels, count);
};

void MLUpscalerIop::renderStripe(ImagePlane &imagePlane)
{
  //input0().fetchPlane(imagePlane);

  //IOPtoCVMat(input0(), sourceMat);
  //cv::resize(sourceMat, sourceMat, cv::Size(), 2.0, 2.0, cv::INTER_LINEAR);
  //CVMatToImagePlane(sourceMat, imagePlane);

  input0().fetchPlane(imagePlane);

  imagePlane.makeUnique();
  imagePlane.makeWritable();

  Box box = imagePlane.bounds();

  foreach(z, imagePlane.channels()) {
    for (Box::iterator it = box.begin(); it != box.end(); it++) {
      imagePlane.writableAt(it.x, it.y, imagePlane.chanNo(z)) *= 2;
    }
  }

  Format in_f = input0().format();
  const int fx = in_f.x();
  const int fy = in_f.y();
  const int fr = in_f.r();
  const int ft = in_f.t();
  const int new_width = in_f.width() * 2;
  const int new_height = in_f.height() * 2;
  const double in_pa = in_f.pixel_aspect();

  Format new_format = Format(new_width, new_height, in_pa);

  //info_.format(new_format);
  //info_.set(format());
}

static Iop *build(Node *node) { return new MLUpscalerIop(node); }
const Iop::Description MLUpscalerIop::d("MLUpscaler", "MLUpscaler", build);
