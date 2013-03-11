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
    ChaosFeedbackSimulator() : x1(0x67452301), x2(0xefcdab89) {}
    ~ChaosFeedbackSimulator() {}
    
    void doChaos(float* channelData, int numSamples);

private:
    int x1;
    int x2;
};

#endif  // __CHAOSFEEDBACKSIMULATOR_H_8B321C90__
