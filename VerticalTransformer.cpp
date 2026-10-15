module;

#include <iostream>

import Utils;
import UJImage;
import Transformer;

export module VerticalTransformer;

//My child class
export class VerticalTransformer : public Transformer{
	
	public:
		
		//My constructor
		explicit VerticalTransformer(int point){
			
			_transformPoint = point;
		};
		
		//My main function
		void transform(UJImage& image) override;
	
	private:
	
		int _transformPoint;
};

//My main function
void VerticalTransformer::transform(UJImage& image){
	
	for(int r = 0; r < image.getRows(); r++){
		
		for(int c = 0; c < image.getCols()/_transformPoint; c++){
			
			//Save opposite pixels
			RGBColour oppositePixel;
			oppositePixel = image.getPixel(r,image.getCols() - 1 - c);
			
			//Making lower substitution
			image.setPixel(r,image.getCols() - 1 - c, image.getPixel(r,c));
			//Making upper substitution
			image.setPixel(r,c, oppositePixel);
		};
	};
	
};