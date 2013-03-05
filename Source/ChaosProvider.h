/*
  ==============================================================================

    ChaosProvider.h
    Created: 5 Mar 2013 11:10:08pm
    Author:  nik

  ==============================================================================
*/

#ifndef __CHAOSPROVIDER_H_7D39C974__
#define __CHAOSPROVIDER_H_7D39C974__

class ChaosProvider
{
public:
    ChaosProvider() {}
    virtual ~ChaosProvider() {}

    virtual void doChaos(float *channelData, int numSamples) = 0;
};

#endif  // __CHAOSPROVIDER_H_7D39C974__
