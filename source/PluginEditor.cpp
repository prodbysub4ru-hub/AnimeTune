#include "PluginProcessor.h"
#include "PluginEditor.h"

AnimeTuneAudioProcessorEditor::AnimeTuneAudioProcessorEditor(AnimeTuneAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p) {

    setSize(500, 360);

    auto configureSlider = [this](juce::Slider& slider, juce::Label& label, const juce::String& text) {
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        addAndMakeVisible(slider);

        label.setText(text, juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        label.setFont(juce::Font(14.0f, juce::Font::bold));
        addAndMakeVisible(label);
    };

    configureSlider(retuneSlider, retuneLabel, "Retune Speed");
    configureSlider(formantSlider, formantLabel, "Formant Shift");
    configureSlider(strengthSlider, strengthLabel, "Strength");
    configureSlider(pitchSlider, pitchLabel, "Pitch Shift");

    retuneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "retune", retuneSlider);
    formantAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "formant", formantSlider);
    strengthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "strength", strengthSlider);
    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "pitch", pitchSlider);

    titleLabel.setText("ANIME TUNE // VST3", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::cyan);
    addAndMakeVisible(titleLabel);
}

AnimeTuneAudioProcessorEditor::~AnimeTuneAudioProcessorEditor() {}

void AnimeTuneAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour(0xff121212)); 
    g.setColour(juce::Colours::cyan.withAlpha(0.5f));
    g.drawRect(getLocalBounds(), 2);
}

void AnimeTuneAudioProcessorEditor::resized() {
    auto area = getLocalBounds().reduced(20);
    titleLabel.setBounds(area.removeFromTop(30));
    area.removeFromTop(10);

    auto gridArea = area;
    int w = gridArea.getWidth() / 2;
    int h = gridArea.getHeight() / 2;

    auto row1 = gridArea.removeFromTop(h);
    retuneSlider.setBounds(row1.removeFromLeft(w).reduced(15));
    retuneLabel.setBounds(retuneSlider.getX(), retuneSlider.getBottom() - 5, retuneSlider.getWidth(), 20);

    formantSlider.setBounds(row1.reduced(15));
    formantLabel.setBounds(formantSlider.getX(), formantSlider.getBottom() - 5, formantSlider.getWidth(), 20);

    auto row2 = gridArea;
    strengthSlider.setBounds(row2.removeFromLeft(w).reduced(15));
    strengthLabel.setBounds(strengthSlider.getX(), strengthSlider.getBottom() - 5, strengthSlider.getWidth(), 20);

    pitchSlider.setBounds(row2.reduced(15));
    pitchLabel.setBounds(pitchSlider.getX(), pitchSlider.getBottom() - 5, pitchSlider.getWidth(), 20);
}
