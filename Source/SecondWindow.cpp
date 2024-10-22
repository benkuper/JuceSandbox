/*
  ==============================================================================

    SecondWindow.cpp
    Created: 20 Oct 2024 10:41:36am
    Author:  bkupe

  ==============================================================================
*/

#include "SecondWindow.h"
#include "MainComponent.h"

using namespace gl;

SecondWindow::SecondWindow()
{
	// Make sure you set the size of the component after
	// you add any child components.

	Displays ds = Desktop::getInstance().getDisplays();

	Rectangle<int> r = ds.displays[ds.displays.size() - 1].userArea;
	addToDesktop(0);
	setBounds(0,0,100,100);
	setAlwaysOnTop(true);
	setVisible(true);
	setOpaque(true);


	context.setRenderer(this);
	context.setContinuousRepainting(true);

	//Calling here is creating random chance success, but if you keep pressing "space" in this window, it will eventually work
	context.setNativeSharedContext(MainComponent::getInstance()->context.getRawContext());

	context.attachTo(*this);
}

SecondWindow::~SecondWindow()
{
	context.detach();
}


void SecondWindow::newOpenGLContextCreated()
{
}

void SecondWindow::openGLContextClosing()
{
}

void SecondWindow::renderOpenGL()
{
	// clear the context with a black background
	OpenGLHelpers::clear(Colours::black);

	Init2DMatrix(getWidth(), getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f(1.0f, 1.0f, 1.0f, .2f);
	//use framebuffer as texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, MainComponent::getInstance()->frameBuffer.getTextureID());
	DrawQuad(0, 0, getWidth() / 2, getHeight() / 2);

	//draw another quad with the same texture
	DrawQuad(getWidth() / 2, getHeight() / 2, getWidth() / 2, getHeight() / 2);

	// unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SecondWindow::paint(Graphics& g)
{
	//g.fillAll(Colours::purple);
}

bool SecondWindow::keyPressed(const KeyPress& key)
{
	if (key.getKeyCode() == key.spaceKey)
	{
		//here, calling attachTo has "some" chance of success, but it's random
		context.detach();
		context.attachTo(*this);
		DBG("Reattach");
	}
	return false;
}
