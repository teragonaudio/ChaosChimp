/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ChaosAudioDropouts.h"
#include "ChaosCpuHog.h"
#include "ChaosCrasher.h"
#include "ChaosFeedbackSimulator.h"
#include "ChaosMemoryLeaker.h"

//==============================================================================
ChaosChimpAudioProcessor::ChaosChimpAudioProcessor()
{
    // First add parameters corresponding to the chaos providers so that the indexes match
    parameters.add(new BooleanParameter(kParamAudioDropoutsEnabled, true));
    parameters.add(new BooleanParameter(kParamCpuHogEnabled, true));
    parameters.add(new BooleanParameter(kParamCrasherEnabled, false));
    parameters.add(new BooleanParameter(kParamFeedbackEnabled, true));
    parameters.add(new BooleanParameter(kParamMemoryLeakerEnabled, true));

    parameters.add(new FloatParameter(kParamProbability, 0.0, 10.0, 1.0));
    parameters[kParamProbability]->setUnit("%");
    parameters.add(new FloatParameter(kParamDuration, 0.1, 20.0, 1.0));
    parameters[kParamDuration]->setUnit("sec");
    parameters.add(new FloatParameter(kParamCooldown, 0.1, 20.0, 1.0));
    parameters[kParamCooldown]->setUnit("sec");
}

ChaosChimpAudioProcessor::~ChaosChimpAudioProcessor()
{
}

//==============================================================================

void ChaosChimpAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentChaosProvider = nullptr;
    currentStateSample = 0;
    rebuildEnabledChaosProviders();
}

void ChaosChimpAudioProcessor::releaseResources()
{
}

void ChaosChimpAudioProcessor::rebuildEnabledChaosProviders()
{
    enabledChaosProviders.clear();
    for (int providerIndex = 0; providerIndex < kNumChaosProviders; ++providerIndex) {
        if (parameters[providerIndex]->getValue()) {
            enabledChaosProviders.add(String(parameters[providerIndex]->getName().c_str()));
        }
    }
}

ChaosProvider* getChaosProviderForName(const String& name)
{
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

void ChaosChimpAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // If the input signal is silent, then don't do any evil things. This could, for instance,
    // cause the host to crash when the user is configuring the plugin.
    bool inputIsSilent = true;
    float* channelData = buffer.getSampleData(0);
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        if (fabs(channelData[i]) >= kSilenceThreshhold) {
            inputIsSilent = false;
            break;
        }
    }

    // Reset plugin state if necessary
    if (inputIsSilent && pluginState != kStateSilence) {
        pluginState = kStateSilence;
    }

    // Take action depending on the current state
    switch (pluginState) {
        case kStateSilence:
            if (!inputIsSilent) {
                pluginState = kStateAudioPlaying;
            }
            break;
        case kStateAudioPlaying: {
            double randomPercent = (double)random() / (double)RAND_MAX;
            if (randomPercent < parameters[kParamProbability]->getValue() / 100.0) {
                if (enabledChaosProviders.size() > 0) {
                    int randomIndex = random() % enabledChaosProviders.size();
                    currentChaosProvider = getChaosProviderForName(enabledChaosProviders[randomIndex]);
                    currentStateSample = 0;
                    pluginState = kStateCausingChaos;
                    // Note that the chaos will actually start *next* block. Whatever.
                }
            }
            break;
        }
        case kStateCausingChaos:
            currentStateSample += buffer.getNumSamples();
            if (currentStateSample > parameters[kParamDuration]->getValue() * getSampleRate()) {
                currentChaosProvider->reset();
                delete currentChaosProvider;
                currentChaosProvider = nullptr;
                currentStateSample = 0;
                pluginState = kStateCooldown;
            }
            break;
        case kStateCooldown:
            currentStateSample += buffer.getNumSamples();
            if (currentStateSample > parameters[kParamCooldown]->getValue() * getSampleRate()) {
                currentStateSample = 0;
                pluginState = kStateAudioPlaying;
            }
            break;
        default:
            break;
    }

    if (pluginState == kStateCausingChaos && currentChaosProvider != nullptr) {
        for (int channel = 0; channel < getNumInputChannels(); ++channel) {
            channelData = buffer.getSampleData(channel);
            currentChaosProvider->doChaos(channelData, buffer.getNumSamples());
        }
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i) {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool ChaosChimpAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* ChaosChimpAudioProcessor::createEditor()
{
    return new ChaosChimpMainEditor(this);
}

//==============================================================================
void ChaosChimpAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml(getName());
    for (int i = 0; i < getNumParameters(); i++) {
        PluginParameter *parameter = parameters[i];
        xml.setAttribute(parameter->getSafeName().c_str(), parameter->getValue());
    }
}

void ChaosChimpAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != 0 && xmlState->hasTagName(getName())) {
        for (int i = 0; i < getNumParameters(); i++) {
            PluginParameter *parameter = parameters[i];
            if (xmlState->hasAttribute(parameter->getSafeName().c_str())) {
                parameter->setValue(xmlState->getDoubleAttribute(parameter->getSafeName().c_str()));
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChaosChimpAudioProcessor();
}
