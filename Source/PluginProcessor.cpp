/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChaosChimpAudioProcessor::ChaosChimpAudioProcessor()
{
    parameters.add(new FloatParameter("Probability", 0.0, 100.0, 0.0));
    parameters.add(new BooleanParameter("Crash", false));
}

ChaosChimpAudioProcessor::~ChaosChimpAudioProcessor()
{
}

//==============================================================================

void ChaosChimpAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void ChaosChimpAudioProcessor::releaseResources()
{
}

void ChaosChimpAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);
        chaosExecutor.doChaos(channelData, buffer.getNumSamples());
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
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
