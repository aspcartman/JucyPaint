//
// Created by ASPCartman on 26/10/14.
//

#include "PaintComponent.h"


PaintComponent::PaintComponent() : ImageComponent()
{
	paintListeners = new ListenerList<PaintListener>;
	currentDrawColour = new Colour(0xFFFFFFFF);
}


void PaintComponent::paint(Graphics &g)
{
	g.fillAll(Colour(0xff383838));
	ImageComponent::paint(g);
}

void PaintComponent::mouseDown(MouseEvent const &event)
{
	Point<int> position = event.getPosition();
	drawPixel(position.x, position.y);
	previousPointOfDrag = new Point<int>(position);
	repaint();
}


void PaintComponent::mouseDrag(MouseEvent const &event)
{
	Point<int> currentPoint = event.getPosition();
	if (previousPointOfDrag == nullptr)
	{
		drawPixel(currentPoint.x, currentPoint.y);
		previousPointOfDrag = new Point<int>(currentPoint);
	}
	else
	{
		Point<int> previusPoint = *previousPointOfDrag;
		drawLine(previusPoint.x, previusPoint.y, currentPoint.x, currentPoint.y);
		previousPointOfDrag = new Point<int>(currentPoint);
	}

	repaint();
}


void PaintComponent::mouseUp(MouseEvent const &event)
{
	previousPointOfDrag = nullptr;
	paintListeners->call(&PaintListener::imageChanged, image);
}

void PaintComponent::drawPixel(int const x, int const y)
{
	image.setPixelAt(x, y, *currentDrawColour);
}

void PaintComponent::drawLine(float x1, float y1, float x2, float y2)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float     error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int      y     = (int) y1;

	const int maxX = (int) x2;

	for (int x = (int) x1; x < maxX; x++)
	{
		if (steep)
		{
			drawPixel(y, x);
		}
		else
		{
			drawPixel(x, y);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void PaintComponent::addPaintListener(PaintListener *listener)
{
	paintListeners->add(listener);
}

void PaintComponent::setDrawColour(Colour &color)
{
	currentDrawColour = new Colour(color);
}
