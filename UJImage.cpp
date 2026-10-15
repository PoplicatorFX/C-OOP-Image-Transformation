module;

#include <iostream>
#include <cassert>

import Utils;

export module UJImage;

//Aliases
using oneDimension = RGBColour*;
using twoDimension = RGBColour**;

//My class
export class UJImage{
	
	public:
	
		//My default constructor
		UJImage();
		
		//My parameterised constructor
		UJImage(std::string magicNum, int rows, int cols, int intensity);
		
		//My copy constructor
		UJImage(const UJImage& original);
		
		//My destructor
		~UJImage();
		
		//My default
		RGBColour DEF_COLOUR = {255, 255, 255};
		
		//My getters
		std::string getMagicNumber() const;
		int getRows() const;
		int getCols() const;
		int getIntensity() const;
		RGBColour getPixel(int row, int col) const;
		
		//My settters
		void setPixel(int row, int col, RGBColour colour);
		
		//My operators
		friend std::ostream& operator<<(std::ostream& COUT, const UJImage& objRhs);
	
		UJImage& operator=(const UJImage& objRhs);
		
		UJImage& operator++(int);
		
		UJImage operator+(const UJImage& objRhs);
	
	
	private:
		
		//My private attributes
		std::string _magicNumber;
		int _intRows;
		int _intCols;
		int _intensity;
		twoDimension _myImage;
		
		//My private functions
		void allocMemory();
		void deallocMemory();
		bool enforceRange(int value, int min, int max) const;
};

//My default constructor
UJImage::UJImage(){
	
	//Assigning variables
	_magicNumber = "P3";
	_intRows = 0;
	_intCols = 0;
	_intensity = 255;
	_myImage = nullptr;
};
		
//My parameterised constructor
UJImage::UJImage(std::string magicNum, int rows, int cols, int intensity){
	
	//Enforcing range
	assert(rows > 0 && cols > 0 && intensity >= 0 && intensity <= 255);
	
	//Assigning variables
	_magicNumber = magicNum;
	_intRows = rows;
	_intCols = cols;
	_intensity = intensity;
	
	//Allocating memory 
	allocMemory();
};
		
//My copy constructor
UJImage::UJImage(const UJImage& original){
	
	//Copying variables
	_magicNumber = original._magicNumber;
	_intRows = original._intRows;
	_intCols = original._intCols;
	_intensity = original._intensity;
	_myImage = nullptr;
	
	//Allocating memory using new variables
	_myImage = new oneDimension[_intRows];
	
	//Deep copying
	for(int r = 0; r < _intRows; r++){
		
		_myImage[r] = new RGBColour[_intCols];
		
		for(int c = 0; c < _intCols; c++){
		
			_myImage[r][c] = original._myImage[r][c];
		};
	};
};
		
//My destructor
UJImage::~UJImage(){
	
	deallocMemory();
};
		
//My getters
std::string UJImage::getMagicNumber() const{
	
	return _magicNumber;
};

int UJImage::getRows() const{
	
	return _intRows;
};

int UJImage::getCols() const{
	
	return _intCols;
};
int UJImage::getIntensity() const{
	
	return _intensity;
};
RGBColour UJImage::getPixel(int row, int col) const{
	
	//Enforcing range
	enforceRange(row, 0, _intRows - 1);
	enforceRange(col, 0, _intCols - 1);
	
	return _myImage[row][col];
};
		
//My settters
void UJImage::setPixel(int row, int col, RGBColour colour){
	
	//Enforcing range
	enforceRange(row, 0, _intRows - 1);
	enforceRange(col, 0, _intCols - 1);
	
	//Enforcing pixel
	assert(colour.intRed >= 0 && colour.intRed < 256 &&
		   colour.intGreen >= 0 && colour.intGreen < 256 &&										
		   colour.intBlue >= 0 && colour.intBlue < 256);
		   
	//Setting the pixel 
	_myImage[row][col] = colour;
};
		
//My operators
std::ostream& operator<<(std::ostream& COUT, const UJImage& objRhs){
	
	//Printing the variables
	COUT << objRhs._magicNumber << std::endl;
	COUT << objRhs._intCols << " " << objRhs._intRows << std::endl;
	COUT << objRhs._intensity << std::endl;
	
	//Printing my colours
	for(int r = 0; r < objRhs._intRows; r++){
		
		for(int c = 0; c < objRhs._intCols; c++){
		
			COUT << objRhs._myImage[r][c].intRed << " "
				<< objRhs._myImage[r][c].intGreen << " "
				<< objRhs._myImage[r][c].intBlue << " ";
		};
		COUT << std::endl;
	};
	
	return COUT;
};
		
		//My private functions
void UJImage::allocMemory(){
	
	_myImage = new oneDimension[_intRows];
	
	for(int r = 0; r < _intRows; r++){
		
		_myImage[r] = new RGBColour[_intCols];
		
		for(int c = 0; c < _intCols; c++){
		
			_myImage[r][c] = DEF_COLOUR;
		
		};
	};
};

//Deallocating memory
void UJImage::deallocMemory(){
	
	if(_myImage != nullptr){
		
		for(int r = 0; r < _intRows; r++){
			
			delete[] _myImage[r];
		};
		delete[] _myImage;
		_myImage = nullptr;
	};
};

//Enforcing range
bool UJImage::enforceRange(int value, int min, int max) const{
	
	if(value < min || value > max)
		throw std::runtime_error("Invalid values");
	
	return true;
};

UJImage& UJImage::operator=(const UJImage& objRhs){
	
	//Avoid self copy
	if(this == &objRhs){
		
		return *this;
	}
	
	//Deallocate memory
	deallocMemory();
	
	//Assign new variables
	_magicNumber = objRhs._magicNumber;
	_intRows = objRhs._intRows;
	_intCols = objRhs._intCols;
	_intensity = objRhs._intensity;
	
	//Allocate memory
	_myImage = new oneDimension[_intRows];
	
	//Perfom deep assignment
	for(int r = 0; r < _intRows; r++){
		
		_myImage[r] = new RGBColour[_intCols];
		
		for(int c = 0; c < _intCols; c++){
		
			_myImage[r][c] = objRhs._myImage[r][c];
		};
	};
	
	return *this;
};

UJImage& UJImage::operator++(int){
	
	for(int r = 0; r < _intRows; r++){
		
		for(int c = 0; c < _intCols; c++){
			
			//Temporary pixel
			RGBColour tempColour;
			
			tempColour.intRed = std::min(_myImage[r][c].intRed + 1, 255);
			tempColour.intGreen = std::min(_myImage[r][c].intGreen + 1, 255);
			tempColour.intBlue = std::min(_myImage[r][c].intBlue + 1, 255);
			
			_myImage[r][c] = tempColour;
		};
	};
	
	return *this;
};

UJImage UJImage::operator+(const UJImage& objRhs){
	
	//For addition, rows and colums must be the same
	
	//I have to return UJImage object, create temporary
	UJImage results(_magicNumber, _intRows, _intCols, _intensity);
	
	for(int r = 0; r < _intRows; r++){
		
		for(int c = 0; c < _intCols; c++){
			
			RGBColour tempColour;
			tempColour.intRed = (_myImage[r][c].intRed + objRhs._myImage[r][c].intRed)/2;
			tempColour.intGreen = (_myImage[r][c].intGreen + objRhs._myImage[r][c].intGreen)/2;
			tempColour.intBlue = (_myImage[r][c].intBlue + objRhs._myImage[r][c].intBlue)/2;
			
			results.setPixel(r,c, tempColour);
		};
	};
	
	return results;
};