/*
  ==============================================================================

	This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

using namespace juce;

//===================================================
// ===========================
class JuceSandboxApplication : public JUCEApplication
{
public:
	//==============================================================================
	JuceSandboxApplication() {}

	const String getApplicationName() override { return ProjectInfo::projectName; }
	const String getApplicationVersion() override { return ProjectInfo::versionString; }
	bool moreThanOneInstanceAllowed() override { return true; }

	JavascriptEngine engine;
	var root;


	//==============================================================================
	void initialise(const String& commandLine) override
	{

		root = var(new DynamicObject());
		root.getDynamicObject()->setProperty("name", "root");

		root.getDynamicObject()->setMethod("log", [](const var::NativeFunctionArgs& args) {
			for (int i = 0; i < args.numArguments; i++)
			{
				if (args.arguments[i].isObject())
				{
					DBG("[Object : " + args.arguments[i].getProperty("name", "noname").toString() + " : " + String((int)args.arguments[i].getDynamicObject()) + "]");
				}
				else
				{
					DBG(args.arguments[i].toString());
				}
			}
			return var::undefined();
			});


		root.getDynamicObject()->setMethod("getChild", [this](const var::NativeFunctionArgs& args) {

			auto name = args.arguments[0].toString();
			auto child = args.thisObject.getDynamicObject()->getProperty(name);
			return child;
			});

		var childA(new DynamicObject());
		childA.getDynamicObject()->setProperty("name", "childA");
		root.getDynamicObject()->setProperty("childA", childA);

		JSObject o = engine.getRootObject();
		o.setProperty("root", root);
		//engine.registerNativeObject("root", root.getDynamicObject());

		var childB(new DynamicObject());
		childB.getDynamicObject()->setProperty("name", "childB");
		o.setProperty("childB", childB);


		String s = File::getSpecialLocation(File::currentApplicationFile).getParentDirectory().getChildFile("test.js").loadFileAsString();

		Result* r = nullptr;
		DBG("Evaluate engine");
		engine.execute(s);

		if (r != nullptr) DBG("Error : " << r->getErrorMessage());

		Array<var> arr;
		var::NativeFunctionArgs args(var::undefined(), arr.getRawDataPointer(), 0);
		r = nullptr;

		DBG("Calling test function");
		r = nullptr;
		engine.callFunction("test", args, r);
		if (r != nullptr) DBG("Error : " << r->getErrorMessage());

		DBG("Adding childC");
		var childC(new DynamicObject());
		childC.getDynamicObject()->setProperty("name", "childC");
		o["root"].setProperty("childC",childC);


		DBG("Calling test function");
		r = nullptr;
		engine.callFunction("test2", args, r);
		if (r != nullptr) DBG("Error : " << r->getErrorMessage());

	}



	void shutdown() override
	{
		// Add your application's shutdown code here..

	}

	//==============================================================================
	void systemRequestedQuit() override
	{
		// This is called when the app is being asked to quit: you can ignore this
		// request and let the app carry on running, or call quit() to allow the app to close.
		quit();
	}

	void anotherInstanceStarted(const String& commandLine) override
	{
		// When another instance of the app is launched while this one is running,
		// this method is invoked, and the commandLine parameter tells you what
		// the other instance's command-line arguments were.
	}

};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(JuceSandboxApplication)
