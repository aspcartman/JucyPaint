/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "xdispatch/dispatch.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
	syncID = new uint8(0);

	sizeLabel = new Label(String::empty, CharPointer_UTF8("Размер поля"));
	sizeLabel->setFont(Font(15, Font::plain));
	sizeLabel->setBounds(17, 20, 100, 15);
	addAndMakeVisible(sizeLabel);

	widthField = new TextEditor("w");
	widthField->setBounds(20, 40, 40, 25);
	widthField->setText("200", false);
	addAndMakeVisible(widthField);

	xLabel = new Label(String::empty, "X");
	xLabel->setBounds(60, 40, 20, 25);
	addAndMakeVisible(xLabel);

	heightField = new TextEditor();
	heightField->setBounds(80, 40, 40, 25);
	heightField->setText("200", false);
	addAndMakeVisible(heightField);

	applyButton = new TextButton(String(CharPointer_UTF8("Применить")));
	applyButton->setBounds(130, 40, 80, 25);
	applyButton->addListener(this);
	addAndMakeVisible(applyButton);

	colorButtons = new OwnedArray<TextButton>();
	Colour      colors[] = {
			Colours::white,
			Colours::black,
			Colours::red,
			Colours::green,
			Colours::blue
	};
	for (Colour &color : colors)
	{
		TextButton *button = new TextButton(String(" "));
		button->setColour(TextButton::buttonColourId, color);
		button->addListener(this);
		addAndMakeVisible(button);
		colorButtons->add(button);
	}

	textField = new TextEditor(String::empty);
	textField->setBounds(20, 80, 200, 200);
	textField->setFont(Font(Font::getDefaultMonospacedFontName(), 10, 0));
	textField->setMultiLine(true, false);
	textField->setScrollbarsShown(true);
	textField->setReturnKeyStartsNewLine(true);
	textField->addListener(this);
	addAndMakeVisible(textField);

	ScopedPointer<Image> image = new Image(Image::PixelFormat::ARGB, 200, 200, true);
	paintComponent = new PaintComponent();
	paintComponent->setBounds(240, 40, 200, 200);
	paintComponent->setImage(*image);
	paintComponent->addMouseListener(this, false);
	paintComponent->addPaintListener(this);
	addAndMakeVisible(paintComponent);

	syncImageToText(*image);

	setSize(500, 400);
}

MainContentComponent::~MainContentComponent()
{
	sizeLabel      = nullptr;
	xLabel         = nullptr;
	widthField     = nullptr;
	heightField    = nullptr;
	applyButton    = nullptr;
	textField      = nullptr;
	paintComponent = nullptr;
	colorButtons   = nullptr;
}


void MainContentComponent::buttonClicked(Button *button)
{
	if (applyButton == button)
	{
		Image image = Image(Image::PixelFormat::ARGB, widthField->getText().getIntValue(), heightField->getText().getIntValue(), true);
		paintComponent->setImage(image);
		syncImageToText(image);
		resized();
	}
	else
	{
		Colour color = ((TextButton*)button)->findColour(TextButton::buttonColourId, false);
		paintComponent->setDrawColour(color);
	}
}

void MainContentComponent::resized()
{
	Rectangle<int> imageBounds = paintComponent->getImage().getBounds();
	paintComponent->setBounds(getWidth() - imageBounds.getWidth() - 20, 80,
			imageBounds.getWidth(), jmin<int>(imageBounds.getHeight(), getHeight() - 20 - 80));
	textField->setBounds(20, 80,
			getWidth() - imageBounds.getWidth() - 20 - 20 - 20, getHeight() - 80 - 20);

	int buttonSize = 20;
	int carret = paintComponent->getX();
	for (TextButton *button : *colorButtons)
	{
		button->setBounds(carret, 40, buttonSize, buttonSize);
		carret += buttonSize + 10;
	}
}

void MainContentComponent::textEditorTextChanged(TextEditor &editor)
{
	syncTextToImage(editor.getText());
}

void MainContentComponent::syncTextToImage(const String &text)
{
	++(*syncID);
	const uint8 myID = *syncID;

	xdispatch::global_queue(xdispatch::queue_priority::DEFAULT).async([ this, text, myID ]() {
		if (myID != *syncID)
		{
			return;
		}
		Image *image = new Image(Image::PixelFormat::ARGB, paintComponent->getWidth(), paintComponent->getHeight(), true);

		auto line    = 0;
		auto row     = 0;
		auto *string = text.toWideCharPointer();
		auto len     = text.length();

		for (int i = 0; i < len; ++i)
		{
			if (myID != *syncID)
			{
				return;
			}

			Colour color;
			switch (string[i])
			{
				case L'.':
				case L'W':
				case L'w':
					color = Colours::white;
					break;

				case L'R':
				case L'r':
					color = Colours::red;
					break;
				case L'G':
				case L'g':
					color = Colours::green;
					break;
				case L'B':
				case L'b':
					color = Colours::blue;
					break;

				case L'\n':
					++line;
					row = 0;
					continue;

				default:
					color = Colours::transparentBlack;
			}
			image->setPixelAt(row, line, color);
			++row;
		}

		xdispatch::main_queue().async([ this, image, myID ]() {
			if (myID != *syncID)
			{
				return;
			}
			paintComponent->setImage(*image);
		});
	});
}


void MainContentComponent::imageChanged(const Image &image)
{
	syncImageToText(image);
}

void MainContentComponent::syncImageToText(const Image &image)
{
	++(*syncID);
	const uint8 myID = *syncID;
	xdispatch::global_queue(xdispatch::queue_priority::DEFAULT).async([ this, image, myID ]() {
		if (myID != *syncID)
		{
			return;
		}

		int height = image.getHeight();
		int width  = image.getWidth() + 1;

		juce_wchar *buf = new juce_wchar[(width + 1) * height + 1];

		for (uint y         = 0; y < height; ++y)
		{
			for (uint x              = 0; x < width - 1; ++x)
			{
				if (myID != *syncID)
				{
					return;
				}

				uint position = y * width + x;

				Colour color = image.getPixelAt(x, y);
				if (color.getAlpha() == 0x00)
				{
					buf[position] = ' ';
				}
				else if (color == Colours::white)
				{
					buf[position] = 'W';
				}
				else if (color == Colours::black)
				{
					buf[position] = '.';
				}
				else if (color == Colours::red)
				{
					buf[position] = 'R';
				}
				else if (color == Colours::green)
				{
					buf[position] = 'G';
				}
				else if (color == Colours::blue)
				{
					buf[position] = 'B';
				}
				else
				{
					buf[position] = ' ';
				}
			}
			buf[(y + 1) * width - 1] = '\n';
		}
		buf[width * height] = '\0';
		xdispatch::main_queue().async([ this, buf, myID ]() {
			if (myID != *syncID)
			{
				return;
			}
			textField->setText(String(buf), false);
			delete buf;
		});
	});
}


