#include "DDImage/PlanarIop.h"
#include <DDImage/Interest.h>
#include "DDImage/Row.h"
#include "DDImage/Thread.h"
#include "DDImage/Knobs.h"
#include <DDImage/Knob.h>
#include "DDImage/ToBuffer.h"

using namespace DD::Image;

static const char *const CLASS = "MLUpscaler";
static const char *const HELP = "Machine Learning Upscaler.";

class MLUpscalerIop : public PlanarIop
{
public:
  // constructor
  MLUpscalerIop(Node *node);

  PackedPreference packedPreference() const { return ePackedPreferenceUnpacked; }

  void knobs(Knob_Callback f);
  // int knob_changed(Knob *k);

  void _validate(bool);

  void getRequests(const Box &box, const ChannelSet &channels, int count, RequestOutput &reqData) const;
  virtual void renderStripe(ImagePlane &imagePlane);

  bool useStripes() const { return false; }

  bool renderFullPlanes() const { return true; }

  static const Iop::Description d;

  const char *Class() const { return d.name; }
  const char *node_help() const { return HELP; }

private:
  int d_scale;
  unsigned int d_width, d_height;

  ChannelSet d_defaultChannels;
  int d_defaultNumberOfChannels;
};