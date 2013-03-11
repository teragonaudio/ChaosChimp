/*
  ==============================================================================

    ChaosMemoryLeaker.h
    Created: 5 Mar 2013 11:11:50pm
    Author:  nik

  ==============================================================================
*/

#ifndef __CHAOSMEMORYLEAKER_H_AE8FCAB4__
#define __CHAOSMEMORYLEAKER_H_AE8FCAB4__

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChaosProvider.h"

class ChaosMemoryLeaker : public ChaosProvider
{
public:
    ChaosMemoryLeaker() {}
    ~ChaosMemoryLeaker() {}

    void doChaos(float* channelData, int numSamples);
    void reset();

private:
    Array<void*> junk;
};

#endif  // __CHAOSMEMORYLEAKER_H_AE8FCAB4__
