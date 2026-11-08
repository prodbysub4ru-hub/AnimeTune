#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

class AnimeTuneAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    AnimeTuneAudioProcessorEditor(AnimeTuneAudioProcessor&);
    ~AnimeTuneAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    AnimeTuneAudioProcessor& audioProcessor;

    juce::Slider retuneSlider;
    juce::Slider formantSlider;
    juce::Slider strengthSlider;
    juce::Slider pitchSlider;

    juce::Label titleLabel;
    juce::Label retuneLabel;
    juce::Label formantLabel;
    juce::Label strengthLabel;
    juce::Label pitchLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> retuneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> formantAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> strengthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnimeTuneAudioProcessorEditor)
};
