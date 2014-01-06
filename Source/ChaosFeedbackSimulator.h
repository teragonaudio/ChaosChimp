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

#ifndef __CHAOSFEEDBACKSIMULATOR_H_8B321C90__
#define __CHAOSFEEDBACKSIMULATOR_H_8B321C90__

#include "ChaosProvider.h"

class ChaosFeedbackSimulator : public ChaosProvider {
public:
    ChaosFeedbackSimulator() : x1(0x67452301), x2(0xefcdab89) {}

    ~ChaosFeedbackSimulator() {}

    void doChaos(float *channelData, int numSamples);

private:
    int x1;
    int x2;
};

#endif  // __CHAOSFEEDBACKSIMULATOR_H_8B321C90__
