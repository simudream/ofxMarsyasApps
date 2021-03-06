#pragma once

#include "settings.h"
#include "ofMain.h"

#ifdef USE_GUI
#include "ofxSimpleGuiToo.h"
#endif

#include "MarPanning3D.h"

class testApp
: public ofBaseApp 
{
public:
	testApp();
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	struct camera
	{
		GLdouble leftfrustum;
		GLdouble rightfrustum;
		GLdouble bottomfrustum;
		GLdouble topfrustum;
		GLfloat modeltranslation;
	} leftCam, rightCam;	
	
	MarPanning3D net;

	ofTrueTypeFont font;
	
	ofPoint &rotation, &offset;
	ofPoint manualRotation, manualOffset;

	double nearZ;	//near clipping plane
	double farZ;	//far clipping plane
	float depthZ;	//depth of the object drawing	

#ifdef USE_GUI
	ofxSimpleGuiToo gui;

	ofxSimpleGuiPage rotation_gui;
	ofxSimpleGuiPage params_gui;
#endif
};
