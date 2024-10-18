

#include "MLUpscaler.h"

#include <iostream>
#include <iomanip>

static const char *_scale[] = {"2x", "3x", "4x", nullptr};

MLUpscalerIop::MLUpscalerIop(Node *node) : PlanarIop(node)
{
  d_scale = 1;

  d_defaultChannels = Mask_RGB;
  d_defaultNumberOfChannels = d_defaultChannels.size();
};

void MLUpscalerIop::knobs(Knob_Callback f)
{
  Enumeration_knob(f, &d_scale, _scale, "scale");
}

void MLUpscalerIop::_validate(bool for_real)
{
  copy_info();
}

void MLUpscalerIop::getRequests(const Box &box, const ChannelSet &channels, int count, RequestOutput &reqData) const
{
  const ChannelSet readChannels = input(0)->info().channels();
  input(0)->request(readChannels, count);
}

void MLUpscalerIop::renderStripe(ImagePlane &imagePlane)
{
  input0().fetchPlane(imagePlane);

  Box box = imagePlane.bounds();

  imagePlane.makeWritable();

      foreach (z, imagePlane.channels())
  {
    for (Box::iterator it = box.begin(); it != box.end(); it++)
    {
      imagePlane.writableAt(it.x, it.y, imagePlane.chanNo(z)) = 0.5;
    }
  }
}

static Iop *build(Node *node) { return new MLUpscalerIop(node); }
const Iop::Description MLUpscalerIop::d("MLUpscaler", "MLUpscaler", build);
