#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
	Component("Main Component")
{	
    setSize (600, 400);
	addAndMakeVisible(pComp);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::FontOptions (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
	pComp.setBounds(50, 50, 400,300);
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
	DBG("[Main] Mouse Down " << event.eventComponent->getName() << " / " << event.originalComponent->getName());
}

void ChildComp::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::midnightblue);
}

void ChildComp::mouseDown(const juce::MouseEvent& event)
{
	DBG("[Child] Mouse Down " << event.eventComponent->getName() << " / " << event.originalComponent->getName());
}

ParentComp::ParentComp() :
	Component("Parent Component"),
	childA("Child A"),
	childB("Child B")
{
	addAndMakeVisible(childA);
	addMouseListener(this, true);
	addAndMakeVisible(childB);
}

void ParentComp::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::orange);
}

void ParentComp::resized()
{
	childA.setBounds(10, 10, 100, 100);
	childB.setBounds(120, 10, 100, 100);
}

void ParentComp::mouseDown(const juce::MouseEvent& event)
{
	DBG("[Parent] Mouse Down " << event.eventComponent->getName() << " / " << event.originalComponent->getName());
}
