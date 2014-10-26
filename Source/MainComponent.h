/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PaintComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent : public Component,
							 public TextEditor::Listener,
							 public PaintListener,
							 public TextButton::Listener
{
public:
	//==============================================================================
	MainContentComponent();
	~MainContentComponent();

	void paint(Graphics &)
	{
	};
	void                          resized();

private:
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
	ScopedPointer<Label>          sizeLabel;
	ScopedPointer<Label>          xLabel;
	ScopedPointer<TextEditor>     widthField;
	ScopedPointer<TextEditor>     heightField;
	ScopedPointer<TextButton>     applyButton;
	ScopedPointer<TextEditor>     textField;
	ScopedPointer<PaintComponent> paintComponent;
	ScopedPointer<uint8>          syncID;
	ScopedPointer<OwnedArray<TextButton>> colorButtons;
public:
	virtual void textEditorTextChanged(TextEditor &param) override;
protected:
	void syncTextToImage(const String &text);
	void syncImageToText(const Image &image);
public:
	virtual void imageChanged(const Image &image) override;
	virtual void buttonClicked(Button *button) override;
};

#endif  // MAINCOMPONENT_H_INCLUDED
