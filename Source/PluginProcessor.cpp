/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "ChaosAudioDropouts.h"
#include "ChaosCpuHog.h"
#include "ChaosCrasher.h"
#include "ChaosFeedbackSimulator.h"
#include "ChaosMemoryLeaker.h"

ChaosChimpAudioProcessor::ChaosChimpAudioProcessor() : TeragonPluginBase(), ParameterObserver() {
    // First add parameters corresponding to the chaos providers so that the indexes match
    parameters.add(new BooleanParameter(kParamAudioDropoutsEnabled, true));
    parameters.add(new BooleanParameter(kParamCpuHogEnabled, true));
    parameters.add(new BooleanParameter(kParamCrasherEnabled, false));
    parameters.add(new BooleanParameter(kParamFeedbackEnabled, true));
    parameters.add(new BooleanParameter(kParamMemoryLeakerEnabled, true));
    parameters.add(new VoidParameter(kParamPanic));

    // Subscribe to all the above parameters
    for(size_t i = 0; i < parameters.size(); ++i) {
        parameters[i]->addObserver(this);
    }

    parameters.add(new BooleanParameter(kParamChaosActive, false));
    parameters.add(new FloatParameter(kParamProbability, 0.0, 10.0, 1.0));
    parameters[kParamProbability]->setUnit("%");
    parameters.add(new FloatParameter(kParamDuration, 0.1, 20.0, 1.0));
    parameters[kParamDuration]->setUnit("Sec");
    parameters.add(new FloatParameter(kParamCooldown, 0.1, 20.0, 1.0));
    parameters[kParamCooldown]->setUnit("Sec");

    ParameterString version = ProjectInfo::projectName;
    version.append(" version ").append(ProjectInfo::versionString);
    parameters.add(new StringParameter(kParamVersion, version));
}

void ChaosChimpAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    TeragonPluginBase::prepareToPlay(sampleRate, samplesPerBlock);
    currentChaosProvider = nullptr;
    currentStateSample = 0;
    pluginState = kStateSilence;
    rebuildEnabledChaosProviders();
}

void ChaosChimpAudioProcessor::rebuildEnabledChaosProviders() {
    enabledChaosProviders.clear();
    for(int providerIndex = 0; providerIndex < kNumChaosProviders; ++providerIndex) {
        if(parameters[providerIndex]->getValue()) {
            enabledChaosProviders.add(String(parameters[providerIndex]->getName().c_str()));
        }
    }
}

void ChaosChimpAudioProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
    TeragonPluginBase::processBlock(buffer, midiMessages);

    // If the input signal is silent, then don't do any evil things. This could, for instance,
    // cause the host to crash when the user is configuring the plugin.
    bool inputIsSilent = true;
    float *channelData = buffer.getSampleData(0);
    for(int i = 0; i < buffer.getNumSamples(); ++i) {
        if(fabs(channelData[i]) >= kSilenceThreshhold) {
            inputIsSilent = false;
            break;
        }
    }

    // Reset plugin state if playing. Note that this plugin can cause the host itself to drop audio,
    // so in kStateCausingChaos, we should ignore the silence.
    if(inputIsSilent && pluginState == kStateAudioPlaying) {
        pluginState = kStateSilence;
    }

    // Take action depending on the current state
    switch(pluginState) {
        case kStateSilence:
            if(!inputIsSilent) {
                pluginState = kStateAudioPlaying;
            }
            break;
        case kStateAudioPlaying: {
            double randomPercent = (double)random() / (double)RAND_MAX;
            if(randomPercent < parameters[kParamProbability]->getValue() / 100.0) {
                if(enabledChaosProviders.size() > 0) {
                    int randomIndex = random() % enabledChaosProviders.size();
                    currentChaosProvider = getChaosProviderForName(enabledChaosProviders[randomIndex]);
                    currentStateSample = 0;
                    // Note that the chaos will actually start *next* block. Whatever.
                    pluginState = kStateCausingChaos;
                }
            }
            break;
        }
        case kStateCausingChaos:
            parameters.set(kParamChaosActive, true);
            currentStateSample += buffer.getNumSamples();
            if(currentStateSample > parameters[kParamDuration]->getValue() * getSampleRate()) {
                stopCausingChaos();
            }
            break;
        case kStateCooldown:
            parameters.set(kParamChaosActive, false);
            currentStateSample += buffer.getNumSamples();
            if(currentStateSample > parameters[kParamCooldown]->getValue() * getSampleRate()) {
                currentStateSample = 0;
                pluginState = kStateAudioPlaying;
            }
            break;
        default:
            pluginState = kStateSilence;
            break;
    }

    if(pluginState == kStateCausingChaos && currentChaosProvider != nullptr) {
        for(int channel = 0; channel < getNumInputChannels(); ++channel) {
            channelData = buffer.getSampleData(channel);
            currentChaosProvider->doChaos(channelData, buffer.getNumSamples());
        }
    }
}

ChaosProvider *ChaosChimpAudioProcessor::getChaosProviderForName(const String &name) {
    if(name.equalsIgnoreCase(kParamAudioDropoutsEnabled)) {
        return new ChaosAudioDropouts();
    }
    else if(name.equalsIgnoreCase(kParamCpuHogEnabled)) {
        return new ChaosCpuHog();
    }
    else if(name.equalsIgnoreCase(kParamCrasherEnabled)) {
        return new ChaosCrasher();
    }
    else if(name.equalsIgnoreCase(kParamFeedbackEnabled)) {
        return new ChaosFeedbackSimulator();
    }
    else if(name.equalsIgnoreCase(kParamMemoryLeakerEnabled)) {
        return new ChaosMemoryLeaker();
    }
    else {
        return nullptr;
    }
}

void ChaosChimpAudioProcessor::releaseResources() {
    TeragonPluginBase::releaseResources();
}

void ChaosChimpAudioProcessor::stopCausingChaos() {
    if(currentChaosProvider != nullptr) {
        currentChaosProvider->reset();
        delete currentChaosProvider;
    }
    currentChaosProvider = nullptr;
    currentStateSample = 0;
    pluginState = kStateCooldown;
}

void ChaosChimpAudioProcessor::onParameterUpdated(const Parameter *parameter) {
    if(parameter->getName() == kParamPanic) {
        stopCausingChaos();
    }
    else {
        rebuildEnabledChaosProviders();
    }
}

AudioProcessorEditor *ChaosChimpAudioProcessor::createEditor() {
    return new ChaosChimpMainEditor(this, parameters, Resources::getCache());
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new ChaosChimpAudioProcessor();
}
