module;

#include <iostream>

import Utils;
import UJImage;

export module Transformer;

//Abstract class, only promises
export class Transformer{
	
	public:
		
		//My virtual function
		virtual void transform(UJImage& image) = 0;
		
		//My virtual destructor
		~Transformer() = default;
};