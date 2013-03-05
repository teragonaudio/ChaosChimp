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
    virtual ~ChaosCrasher() {}

    void startChaos();
    void stopChaos();
};

#endif  // __CHAOSCRASHER_H_F5E600A5__
