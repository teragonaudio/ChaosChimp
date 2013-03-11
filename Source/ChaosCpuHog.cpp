/*
  ==============================================================================

    ChaosCpuHog.cpp
    Created: 5 Mar 2013 11:11:35pm
    Author:  nik

  ==============================================================================
*/

#include <stdlib.h>
#include <math.h>
#include "ChaosCpuHog.h"

void ChaosCpuHog::doChaos(float* channelData, int numSamples)
{
    double junk = 0;
    for (int i = 0; i < numSamples * 1000; ++i) {
        for (int j = 0; j < numSamples; ++j) {
            // TODO: Need to evaluate how much CPU this actually takes up on a modern CPU
            junk += log10(exp(sin(sqrt(random() % (i * j + 1)))));
        }
    }
}
