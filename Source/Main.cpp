/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

//==============================================================================
class JucyPaintApplication : public JUCEApplication
{
public:
	//==============================================================================
	ScopedPointer<LookAndFeel> lookAndFeel;

	JucyPaintApplication()
	{
	}

	const String getApplicationName() override
	{
		return ProjectInfo::projectName;
	}

	const String getApplicationVersion() override
	{
		return ProjectInfo::versionString;
	}

	bool moreThanOneInstanceAllowed() override
	{
		return true;
	}

	//==============================================================================
	void initialise(const String &commandLine) override
	{
		// This method is where you should put your application's initialisation code..
		lookAndFeel = new DarkTheme();
		LookAndFeel::setDefaultLookAndFeel(lookAndFeel);
		mainWindow = new MainWindow(getApplicationName());
	}

	void shutdown() override
	{
		// Add your application's shutdown code here..

		mainWindow = nullptr; // (deletes our window)
	}

	//==============================================================================
	void systemRequestedQuit() override
	{
		// This is called when the app is being asked to quit: you can ignore this
		// request and let the app carry on running, or call quit() to allow the app to close.
		quit();
	}

	void anotherInstanceStarted(const String &commandLine) override
	{
		// When another instance of the app is launched while this one is running,
		// this method is invoked, and the commandLine parameter tells you what
		// the other instance's command-line arguments were.
	}

	//==============================================================================
	/*
		This class implements the desktop window that contains an instance of
		our MainContentComponent class.
	*/
	class MainWindow : public DocumentWindow
	{
	public:
		MainWindow(String name) : DocumentWindow(name,
				Colours::lightgrey,
				DocumentWindow::allButtons)
		{
			setUsingNativeTitleBar(true);
			setContentOwned(new MainContentComponent(), true);
			setResizable(true, true);
			centreWithSize(getWidth(), getHeight());
			setVisible(true);
		}

		void closeButtonPressed() override
		{
			// This is called when the user tries to close this window. Here, we'll just
			// ask the app to quit when this happens, but you can change this to do
			// whatever you need.
			JUCEApplication::getInstance()->systemRequestedQuit();
		}

		/* Note: Be careful if you override any DocumentWindow methods - the base
		   class uses a lot of them, so by overriding you might break its functionality.
		   It's best to do all your work in your content component instead, but if
		   you really have to override any DocumentWindow methods, make sure your
		   subclass also calls the superclass's method.
		*/

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
	};

	class DarkTheme : public LookAndFeel_V3
	{
	public:
		DarkTheme()
		{
			setColour(TextEditor::backgroundColourId, Colour(0xff383838));
			setColour(TextEditor::outlineColourId, Colour(0xff404040));
			setColour(TextEditor::focusedOutlineColourId, Colour(0xff505050));
			setColour(TextEditor::textColourId, Colours::whitesmoke);
			setColour(Label::textColourId, Colours::whitesmoke);
			setColour(TextButton::textColourOffId, Colours::whitesmoke);
			setColour(TextButton::buttonColourId, Colour(0xff383838));

		};

//		virtual void drawLabel(Graphics &g, Label &l) override{
//			g.fillAll(Colours::red);
//			LookAndFeel_V3::drawLabel(g, l);
//		};

		virtual void drawButtonBackground(Graphics &g, Button &b, const Colour &c, bool isMouseOverButton, bool isButtonDown) override
		{
			if (isButtonDown)
			{
				g.fillAll(Colour(c).darker(0.2));
			}
			else if (isMouseOverButton)
			{
				g.fillAll(Colour(c).brighter(0.1));
			}
			else
			{
				g.fillAll(Colour(c));
			}

			g.setColour(Colour(0xff505050));
			g.drawRect(0, 0, b.getWidth(), b.getHeight(), 1);
		}


		virtual void fillResizableWindowBackground(Graphics &g, int w, int h, BorderSize<int> const &bs, ResizableWindow &window) override
		{
			g.fillAll(Colour(0xff333333));
		}
	};

private:
	ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (JucyPaintApplication)


