#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
	This component lives inside our window, and this is where you should put all
	your controls and content.
*/


class ChildComp : public juce::Component
{
public:
	ChildComp(juce::StringRef n) : juce::Component(n) {}
	~ChildComp() {}

	void paint(juce::Graphics&) override;

	void mouseDown(const juce::MouseEvent& event) override;
};

class ParentComp : public juce::Component
{
public:
	ParentComp();
	~ParentComp() {}

	ChildComp childA;
	ChildComp childB;

	void paint(juce::Graphics&) override;
	void resized() override;

	void mouseDown(const juce::MouseEvent& event) override;
};

class MainComponent : public juce::Component
{
public:
	//==============================================================================
	MainComponent();
	~MainComponent() override;

	ParentComp pComp;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

	void mouseDown(const juce::MouseEvent& event) override;

private:
	//==============================================================================
	// Your private member variables go here...


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
