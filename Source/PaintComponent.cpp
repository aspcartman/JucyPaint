//
// Created by ASPCartman on 26/10/14.
//

#include "PaintComponent.h"
#import "juce_ListenerList.h"

void PaintComponent::paint(Graphics &g)
{
	g.fillAll(Colour(0xff383838));
	ImageComponent::paint(g);
}

PaintComponent::PaintComponent():ImageComponent()
{
	paintListeners = new ListenerList<PaintListener>;
}

void PaintComponent::mouseDrag(MouseEvent const &event)
{
	Image image = getImage();

	Point<int> position = event.getPosition();
	image.setPixelAt(position.x, position.y, Colours::red);

	repaint();

	paintListeners->call(&PaintListener::imageChanged,image);
}

void PaintComponent::addPaintListener(PaintListener *listener)
{
	paintListeners->add(listener);
}

