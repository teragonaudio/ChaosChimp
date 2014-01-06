/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#ifndef __CHAOSMEMORYLEAKER_H_AE8FCAB4__
#define __CHAOSMEMORYLEAKER_H_AE8FCAB4__

#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "ChaosProvider.h"

class ChaosMemoryLeaker : public ChaosProvider {
public:
    ChaosMemoryLeaker() {}

    ~ChaosMemoryLeaker() {}

    void doChaos(float *channelData, int numSamples);

    void reset();

private:
    std::vector<void *> junk;
};

#endif  // __CHAOSMEMORYLEAKER_H_AE8FCAB4__
