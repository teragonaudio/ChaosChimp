/*
  ==============================================================================

    RandomChaosExecutor.cpp
    Created: 6 Mar 2013 12:03:46am
    Author:  nik

  ==============================================================================
*/

#include "RandomChaosExecutor.h"
#include "ChaosAudioDropouts.h"
#include "ChaosCpuHog.h"
#include "ChaosCrasher.h"
#include "ChaosFeedbackSimulator.h"
#include "ChaosMemoryLeaker.h"

RandomChaosExecutor::RandomChaosExecutor()
{
    chaosProviders.add(new ChaosAudioDropouts());
    chaosProviders.add(new ChaosCpuHog());
    chaosProviders.add(new ChaosCrasher());
    chaosProviders.add(new ChaosFeedbackSimulator());
    chaosProviders.add(new ChaosMemoryLeaker());

    currentChaosProviderIndex = -1;
    probability = 1.0f;
}

RandomChaosExecutor::~RandomChaosExecutor()
{
    chaosProviders.clear(true);
}

void RandomChaosExecutor::doChaos(float* channelData, int numSamples)
{
    if (currentChaosProviderIndex < 0) {
        long int randomNumber = random() / RAND_MAX;
        // Trigger every 1% of the time
        if (randomNumber < RAND_MAX / (long int)(100.0f * probability)) {
            long int randomIndex = random() % chaosProviders.size();
        }
    }
    if (currentChaosProviderIndex > 0) {
        chaosProviders[currentChaosProviderIndex]->doChaos(channelData, numSamples);
    }
    // TODO: When to end the chaos?
}
