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

#include "ChaosMemoryLeaker.h"

void ChaosMemoryLeaker::doChaos(float *channelData, int numSamples) {
    void *stuff = malloc(1024 * 1024 * 10);
    junk.push_back(stuff);
}

void ChaosMemoryLeaker::reset() {
    for(int i = 0; i < junk.size(); i++) {
        free(junk[i]);
    }
    junk.clear();
}

