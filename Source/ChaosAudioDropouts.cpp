/*
  ==============================================================================

    ChaosAudioDropouts.cpp
    Created: 5 Mar 2013 11:12:22pm
    Author:  nik

  ==============================================================================
*/

#include <stdlib.h>
#include "ChaosAudioDropouts.h"

void ChaosAudioDropouts::doChaos(float* channelData, int numSamples)
{
    for (int i = 0; i < numSamples; ++i) {
        if (random() % 5 == 0) {
            channelData[i] = 0.0f;
        }
    }
}
