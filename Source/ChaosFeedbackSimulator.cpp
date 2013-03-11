/*
  ==============================================================================

    ChaosFeedbackSimulator.cpp
    Created: 5 Mar 2013 11:12:47pm
    Author:  nik

  ==============================================================================
*/

#include "ChaosFeedbackSimulator.h"

static const float kGain = 0.5f;

void ChaosFeedbackSimulator::doChaos(float* channelData, int numSamples)
{
    // Note that the name of this class implies *SIMULATOR*. Feedback sucks, and
    // my ears fear for it. So instead we replace the output channel with static
    // hissing. The goal here is to train that all-important reflect to slam the
    // "mute" button, not to blow out a nice pair of studio monitors...

    // Algorithm borrowed from MusicDSP.org:
    // http://musicdsp.org/archive.php?classid=1#216
    for (int i = 0; i < numSamples; ++i) {
        x1 ^= x2;
        channelData[i] = x2 * kGain;
        x2 += x1;
    }
}
