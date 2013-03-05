/*
  ==============================================================================

    ChaosFeedbackSimulator.h
    Created: 5 Mar 2013 11:12:47pm
    Author:  nik

  ==============================================================================
*/

#ifndef __CHAOSFEEDBACKSIMULATOR_H_8B321C90__
#define __CHAOSFEEDBACKSIMULATOR_H_8B321C90__
#include "ChaosProvider.h"

class ChaosFeedbackSimulator : public ChaosProvider
{
public:
    ChaosFeedbackSimulator() {}
    ~ChaosFeedbackSimulator() {}
    
    void doChaos(float* channelData, int numSamples);
};

#endif  // __CHAOSFEEDBACKSIMULATOR_H_8B321C90__
