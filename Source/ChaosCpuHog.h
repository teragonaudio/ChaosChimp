/*
  ==============================================================================

    ChaosCpuHog.h
    Created: 5 Mar 2013 11:11:35pm
    Author:  nik

  ==============================================================================
*/

#ifndef __CHAOSCPUHOG_H_AD64357B__
#define __CHAOSCPUHOG_H_AD64357B__
#include "ChaosProvider.h"

class ChaosCpuHog : public ChaosProvider
{
public:
    ChaosCpuHog() {}
    ~ChaosCpuHog() {}

    void doChaos(float* channelData, int numSamples);
};

#endif  // __CHAOSCPUHOG_H_AD64357B__
