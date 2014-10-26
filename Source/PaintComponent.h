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

	void addPaintListener(PaintListener *listener);
private:
	ScopedPointer<ListenerList<PaintListener>> paintListeners;
};



#endif //__PaintComponent_H_
