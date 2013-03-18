/*
  ==============================================================================

    ChaosMemoryLeaker.cpp
    Created: 5 Mar 2013 11:11:50pm
    Author:  nik

  ==============================================================================
*/

#include "ChaosMemoryLeaker.h"

void ChaosMemoryLeaker::doChaos(float* channelData, int numSamples)
{
    void* stuff = malloc(1024 * 1024 * 10);
    junk.push_back(stuff);
}

void ChaosMemoryLeaker::reset()
{
    for (int i = 0; i < junk.size(); i++) {
        free(junk[i]);
    }
    junk.clear();
}

