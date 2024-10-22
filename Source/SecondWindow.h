/*
  ==============================================================================

    SecondWindow.h
    Created: 20 Oct 2024 10:41:36am
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

class SecondWindow : public Component, public OpenGLRenderer
{
public:
    SecondWindow();
	~SecondWindow();
    void newOpenGLContextCreated() override;
    void openGLContextClosing() override;
    void renderOpenGL() override;

	void paint(Graphics& g) override;

    OpenGLContext context;

	bool keyPressed(const KeyPress& key) override;
};