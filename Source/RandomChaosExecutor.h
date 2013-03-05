/*
  ==============================================================================

    RandomChaosExecutor.h
    Created: 6 Mar 2013 12:03:46am
    Author:  nik

  ==============================================================================
*/

#ifndef __RANDOMCHAOSEXECUTOR_H_BB4F7992__
#define __RANDOMCHAOSEXECUTOR_H_BB4F7992__

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChaosProvider.h"

class RandomChaosExecutor
{
public:
    RandomChaosExecutor();
    ~RandomChaosExecutor();

    float getProbability() const { return probability; }
    void setProbability(float value) { this->probability = value; }

    void doChaos(float *channelData, int numSamples);

private:
    OwnedArray<ChaosProvider> chaosProviders;
    int currentChaosProviderIndex;
    float probability;
};

#endif  // __RANDOMCHAOSEXECUTOR_H_BB4F7992__
