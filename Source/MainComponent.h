#pragma once

#include <JuceHeader.h>
using namespace juce;
using namespace gl;

#define Init2DMatrix(w, h) glMatrixMode(GL_PROJECTION);\
glLoadIdentity(); \
glOrtho(0, w, 0, h, 0, 1); \
glMatrixMode(GL_MODELVIEW); \
glLoadIdentity(); \

//with texcoords
#define DrawQuad(x, y, w, h) glBegin(GL_QUADS); \
glTexCoord2f(0, 0); glVertex2f(x, y); \
glTexCoord2f(1, 0); glVertex2f(x + w, y); \
glTexCoord2f(1, 1); glVertex2f(x + w, y + h); \
glTexCoord2f(0, 1); glVertex2f(x, y + h); \
glEnd(); \



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component,
	public juce::OpenGLRenderer
{
public:
    //==============================================================================

	juce_DeclareSingleton(MainComponent, true);
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

	void newOpenGLContextCreated() override;
	void openGLContextClosing() override;
	void renderOpenGL() override;

    OpenGLContext context;
	OpenGLFrameBuffer frameBuffer;

	//==============================================================================
	// Your public member functions go here...

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
