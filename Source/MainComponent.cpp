#include "MainComponent.h"


juce_ImplementSingleton(MainComponent);

//==============================================================================
MainComponent::MainComponent() 
{
	// Make sure you set the size of the component after
	// you add any child components.
	setSize(800, 600);

	//initialize the openGL context
	context.setRenderer(this);

	//attach the context to this component
	context.attachTo(*this);
	context.setComponentPaintingEnabled(true);
	context.setContinuousRepainting(true);

	// create a framebuffer object
}

MainComponent::~MainComponent()
{
	// This shuts down the GL system and stops the rendering calls.

	// delete the framebuffer and texture
	context.detach();
	frameBuffer.release();
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	// You can add your component specific drawing code here!
	// This will draw over the top of the openGL background.

	// bind the framebuffer

}

void MainComponent::resized()
{
	// This is called when the MainComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}

void MainComponent::newOpenGLContextCreated()
{
	frameBuffer.initialise(context, getWidth(), getHeight());
}

void MainComponent::openGLContextClosing()
{
}

void MainComponent::renderOpenGL()
{
	// clear the context with a black background
	OpenGLHelpers::clear(Colours::black);

	// draw a rotating triangle
	const float rotation = std::fmod(Time::getMillisecondCounterHiRes() / 1000.0f, 1.0f);
	const float alpha = 1.0f;
	const float size = 0.6f;
	const float halfSize = size * 0.5f;


	const Colour colour(Colour::fromHSV(Time::getMillisecondCounter() / 4000.0, .6, .7, 1.0f));



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 
    frameBuffer.makeCurrentAndClear();
	Init2DMatrix(getWidth(), getHeight());
    glBegin(GL_TRIANGLES);
    glColor4f(colour.getFloatRed(), colour.getFloatGreen(), colour.getFloatBlue(), colour.getFloatAlpha());
    glVertex2f(0, 0);
    glVertex2f(getWidth()*.2f, getHeight()*.6f);
    glVertex2f(getWidth() * .7f, getHeight()*.3f);
    glEnd();

	frameBuffer.releaseAsRenderingTarget();

	Init2DMatrix(getWidth(), getHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor4f(1.0f, 1.0f, 1.0f, .2f);
    //use framebuffer as texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, frameBuffer.getTextureID());
	DrawQuad(0, 0, getWidth()/2, getHeight()/2);

	//draw another quad with the same texture
	DrawQuad(getWidth() / 2, getHeight() / 2, getWidth() / 2, getHeight() / 2);

	// unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}
