/*
  ==============================================================================

    ChaosAudioDropouts.h
    Created: 5 Mar 2013 11:12:22pm
    Author:  nik

  ==============================================================================
*/

#ifndef __CHAOSAUDIODROPOUTS_H_5A7DFF9B__
#define __CHAOSAUDIODROPOUTS_H_5A7DFF9B__
#include "ChaosProvider.h"

class ChaosAudioDropouts : public ChaosProvider
{
public:
    ChaosAudioDropouts() {}
    virtual ~ChaosAudioDropouts() {}

    void doChaos(float* channelData, int numSamples);
};

#endif  // __CHAOSAUDIODROPOUTS_H_5A7DFF9B__
