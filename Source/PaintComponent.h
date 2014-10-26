//
// Created by ASPCartman on 26/10/14.
//


#ifndef __PaintComponent_H_
#define __PaintComponent_H_

#include "../JuceLibraryCode/JuceHeader.h"
class PaintListener
{
public:
	virtual ~PaintListener() { };
	virtual void imageChanged(const Image &image){};
};

class PaintComponent: public ImageComponent
{
public:
	PaintComponent();
	virtual void paint(Graphics &param) override;
	virtual void mouseDrag(MouseEvent const &event) override;
	virtual void mouseDown(MouseEvent const &event) override;

	void addPaintListener(PaintListener *listener);

	void setDrawColour(Colour &color);

protected:
	ScopedPointer<Colour> currentDrawColour;
private:
	ScopedPointer<ListenerList<PaintListener>> paintListeners;
	ScopedPointer<Point<int>> previousPointOfDrag;
	void drawLine(float x1, float y1, float x2, float y2);
	void drawPixel(int const x1, int const y1);

public:
	virtual void mouseUp(MouseEvent const &event) override;
};



#endif //__PaintComponent_H_
