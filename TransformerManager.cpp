module;

#include <iostream>

import Utils;
import UJImage;
import Transformer;
import HorizontalTransformer;
import VerticalTransformer;

export module TransformerManager;

export class TransformerManager{
	
	public:
	
		//My constructor
		TransformerManager(bool type, int point);
		
		//My destructor
		~TransformerManager();
		
		//My delegated function
		void transform(UJImage& image);
		
	private:
		
		Transformer* pTransformer;
		bool _transformerType;
		int _transformPoint;
};

//My constructor
TransformerManager::TransformerManager(bool type, int point){
	
	//Assigning variables
	_transformerType = type;
	_transformPoint = point;
	
	if(_transformerType){
		
		//Choose horizontal
		pTransformer = new HorizontalTransformer(_transformPoint);
		
	}else{
		
		//Choose Vertical
		pTransformer = new VerticalTransformer(_transformPoint);
	};
};
		
//My destructor
TransformerManager::~TransformerManager(){
	
	if(pTransformer != nullptr){
		
		delete pTransformer;
		pTransformer = nullptr;
	}
};
		
//My delegated function
void TransformerManager::transform(UJImage& image){
	
	pTransformer->transform(image);
};