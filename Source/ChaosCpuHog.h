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

#ifndef __CHAOSCPUHOG_H_AD64357B__
#define __CHAOSCPUHOG_H_AD64357B__

#include "ChaosProvider.h"

class ChaosCpuHog : public ChaosProvider {
public:
    ChaosCpuHog() {}

    ~ChaosCpuHog() {}

    void doChaos(float *channelData, int numSamples);
};

#endif  // __CHAOSCPUHOG_H_AD64357B__
