/*
  ==============================================================================

    ChaosCrasher.h
    Created: 5 Mar 2013 11:11:00pm
    Author:  nik

  ==============================================================================
*/

#ifndef __CHAOSCRASHER_H_F5E600A5__
#define __CHAOSCRASHER_H_F5E600A5__

#include "ChaosProvider.h"

class ChaosCrasher : public ChaosProvider
{
public:
    ChaosCrasher() {}
    ~ChaosCrasher() {}

    void doChaos(float* channelData, int numSamples);
};

#endif  // __CHAOSCRASHER_H_F5E600A5__
