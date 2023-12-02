#include "falloutttwbsainvalidation.h"

FalloutTTWBSAInvalidation::FalloutTTWBSAInvalidation(DataArchives *dataArchives, MOBase::IPluginGame const *game) : GamebryoBSAInvalidation(dataArchives, "Fallout.ini", game)
{
}

QString FalloutTTWBSAInvalidation::invalidationBSAName() const
{
  return "Fallout - Invalidation.bsa";
}

unsigned long FalloutTTWBSAInvalidation::bsaVersion() const
{
  return 0x68;
}
