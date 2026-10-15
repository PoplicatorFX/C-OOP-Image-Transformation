module;

#include <iostream>

import Utils;
import UJImage;
import Transformer;

export module HorizontalTransformer;

//My child class
export class HorizontalTransformer : public Transformer{
	
	public:
		
		//My constructor
		explicit HorizontalTransformer(int point){
			
			_transformPoint = point;
		};
		
		//My main function
		void transform(UJImage& image) override;
	
	private:
	
		int _transformPoint;
};

//My main function
void HorizontalTransformer::transform(UJImage& image){
	
	for(int r = 0; r < image.getRows()/_transformPoint; r++){
		
		for(int c = 0; c < image.getCols(); c++){
			
			//Save opposite pixels
			RGBColour oppositePixel;
			oppositePixel = image.getPixel(image.getRows() - 1 -r, c);
			
			//Making lower substitution
			image.setPixel(image.getRows() - 1 - r,c, image.getPixel(r,c));
			//Making upper substitution
			image.setPixel(r,c, oppositePixel);
		};
	};
};