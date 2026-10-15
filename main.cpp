#include <iostream>
#include <fstream>
#include <stdexcept>

import Utils;
import UJImage;
import Transformer;
import HorizontalTransformer;
import VerticalTransformer;
import TransformerManager;

using namespace std;

//Read Text File and create UJImage Object
UJImage readTXTFile(string strFileName);
//Write Binary File from UJImage Object
void writeBINFile(string strFileName, const UJImage& objImage);

int main(){
	
	//My try block
	try{
		string strTXTFileName = "data/UJ_20_large.txt"; // UJ_20_small
		string strBINFileName = "data/UJ_20_large.dat";
		UJImage objImage = readTXTFile(strTXTFileName); //Uses copy constructor
		int intHalfWay = 2;
	
		//Pass as parameter, transformer type TRUE for HorizontalTransformer and FALSE for VerticalTransformer
		TransformerManager objTransformerManager(false, intHalfWay);	
		
		//Delegation and Polymorphic call on transform function
		objTransformerManager.transform(objImage);
		
		//Write Transformed Image to Binary File
		writeBINFile(strBINFileName, objImage);	
	
		//Test Overloaded Operators
		UJImage objCopy = objImage;
		objCopy++;
		UJImage objNewCopy = objCopy + objImage;
		cout << objImage << endl;	// Output transformed Image
	}
	catch(...){
		
		cout << "Caught a generic error" << endl;
	};
	
	return 0;
}

//Read Text File and create UJImage Object
UJImage readTXTFile(string strFileName){
	
	//Open read connection
	std::ifstream in_stream(strFileName);
	
	//Checking if file is open
	if(!in_stream)
		throw std::runtime_error("Could not open text file");
	
	//Create variables to read onto
	std::string magicNumber;
	int intRows;
	int intCols;
	int intensity;
	
	//Reading onto the variables
	in_stream >> magicNumber >> intCols >> intRows >> intensity;
	
	//Creating an object
	UJImage tempObject(magicNumber, intRows, intCols, intensity);
	
	//Loop and set colour
	for(int r = 0; r < intRows; r++){
		
		for(int c = 0; c < intCols; c++){
		
			//temporary colour
			RGBColour tempColour;
			
			//Read onto temp colour
			in_stream >> tempColour.intRed >> tempColour.intGreen >> tempColour.intBlue;
			
			//Set pixel
			tempObject.setPixel(r,c,tempColour);
		};
	};
	
	//Close connecttion
	in_stream.close();
	
	return tempObject;
};

//Write Binary File from UJImage Object
void writeBINFile(string strFileName, const UJImage& objImage){
	
	//Open write connection
	std::ofstream out_stream(strFileName, ios::binary);
	
	//check if file is open 
	if(!out_stream)
		throw std::runtime_error("Could not open bin file");
	
	//Writing
	for(int r = 0; r < objImage.getRows(); r++){
		
		for(int c = 0; c < objImage.getCols(); c++){
		
			//temporary colour
			RGBColour tempColour;
			
			//Write onto tempColour
			tempColour = objImage.getPixel(r,c);
			
			//Write colour tto binary
			out_stream.write(reinterpret_cast<const char*>(&tempColour), sizeof(RGBColour));
		};
	};
	
	//Close connection
	out_stream.close();
};