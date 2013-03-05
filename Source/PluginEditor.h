/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  5 Mar 2013 11:28:35pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CHAOSCHIMPMAINEDITOR_PLUGINEDITOR_FF51C9F2__
#define __JUCER_HEADER_CHAOSCHIMPMAINEDITOR_PLUGINEDITOR_FF51C9F2__

//[Headers]     -- You can add your own extra header files here --
#include "PluginProcessor.h"
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ChaosChimpMainEditor  : public AudioProcessorEditor
{
public:
    //==============================================================================
    ChaosChimpMainEditor (ChaosChimpAudioProcessor* ownerFilter);
    ~ChaosChimpMainEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChaosChimpMainEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCER_HEADER_CHAOSCHIMPMAINEDITOR_PLUGINEDITOR_FF51C9F2__
