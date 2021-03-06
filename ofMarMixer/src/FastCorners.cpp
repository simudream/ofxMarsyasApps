#include "FastCorners.h"

#ifdef USE_CVD
#include <cvd/image_convert.h>

#include <cvd/fast_corner.h>
#include <cvd/nonmax_suppression.h>

using namespace CVD;
#endif


//--------------------------------------------------------------
FastCorners::FastCorners()
{
	bFindCorners = true;
	
	barrier = 20;
	bStrict = true;
}

//--------------------------------------------------------------
FastCorners::~FastCorners()
{
	destroy();
}

void FastCorners::setup()
{
	imBW.resize(videoSize);	
}

//--------------------------------------------------------------
void FastCorners::destroy()
{}

//--------------------------------------------------------------
void FastCorners::update()
{
	if (!getWidth() || !getHeight())
		return;
	
#ifdef USE_CVD
	BasicImage<Rgb<byte> > grabRGB((Rgb<byte>*)getPixels(), videoSize);
	//	imRGB.copy_from(grabRGB);
	convert_image(grabRGB, imBW);

	if (bFindCorners)
	{
		all_corners.clear();
		corners.clear();
		scores.clear();
		FAST_CORNER_FUNC(imBW, all_corners, barrier);
		
		// Store non-max corners with their score, in a std::pair
		if (bStrict)
			fast_nonmax(imBW, all_corners, barrier, corners);
		else
			corners.swap(all_corners);
		
		FAST_CORNER_SCORER(imBW, corners, barrier, scores);
		
		nFoundCorners = corners.size();
	}
#endif
}

//--------------------------------------------------------------
void FastCorners::draw(float x, float y)
{
	draw(x, y, getWidth(), getHeight());
}

//--------------------------------------------------------------
void FastCorners::draw(float x, float y, float w, float h)
{
#ifdef USE_CVD
	glPushMatrix();
	glTranslatef(x, y, 0.);
	glScalef(w/getWidth(), h/getHeight(), 1.);

	if (bFindCorners)
	{
		ImageRef pixel;
		int score;
		for (int c=0; c<nFoundCorners; c++)
		{
			pixel = corners[c];
			score = scores[c];
			
			ofSetLineWidth(1);
			ofSetColor(0x000000);
			/*			
			 // Printed score
			 sprintf(str_index, "%d", score);
			 ofDrawBitmapString(str_index, pixel.x-5, pixel.y-5);
			 
			 // Image patch border
			 ofNoFill();
			 ofSetLineWidth(2);
			 ofRect(pixel.x-5, pixel.y-5, 5*2, 5*2);
			 */
			ofFill();
			ofSetColor(0xaa00aa);
			ofSetLineWidth(1);
			ofCircle(pixel.x, pixel.y, 1);
		}
	}
	glPopMatrix();
#endif
}
