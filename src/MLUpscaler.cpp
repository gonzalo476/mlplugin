

#include "MLUpscaler.h"

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
  copy_info();

  //int iw = format().width();
  //int ih = format().height();

  //int t = info_.r();
  //info_.r(iw - info_.x());
  //info_.x(iw - t);
}

void MLUpscalerIop::getRequests(const Box &box, const ChannelSet &channels, int count, RequestOutput &reqData) const
{
  reqData.request(input(0), box, channels, count);
}

void MLUpscalerIop::renderStripe(ImagePlane &imagePlane)
{
}

static Iop *build(Node *node) { return new MLUpscalerIop(node); }
const Iop::Description MLUpscalerIop::d("MLUpscaler", "MLUpscaler", build);
