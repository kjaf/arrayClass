
#include "Array.h"
#include <iostream>
const int DEFAULT_SIZE = 100;




//default constructor
//done
Array::Array(void) :
	data_(nullptr),
	cur_size_(0),
	max_size_(0)
{
	this->data_ = new char[this->max_size_];
	this->max_size_ = DEFAULT_SIZE;

}


//initalizing constructor without a fill
//done
Array::Array(size_t length) :
	data_(nullptr),
	cur_size_(0),
	max_size_(0)
{
	//if length is greater than default size then max_size_ is the length
	if (length > DEFAULT_SIZE) {
		this->max_size_ = length;
	}
	else {
		this->max_size_ = DEFAULT_SIZE;
	}
	std::cout << length << std::endl;
	this->cur_size_ = length;
	this->data_ = new char[this->max_size_];
}


//initializing constructor with a fill
//done
Array::Array(size_t length, char fill) :
	data_(nullptr),
	cur_size_(0),
	max_size_(0)
{
	//if length is great than the default size that we set then max_size_ is equal to length 
	if (length > DEFAULT_SIZE) {
		this->max_size_ = length;
	}
	else {
		this->max_size_ = DEFAULT_SIZE;
	}

	this->cur_size_ = length;
	this->data_ = new char[this->max_size_];

	this->fill(fill);




}



//copy constructor
//done
Array::Array(const Array & array) :
	data_(nullptr),
	cur_size_(0),
	max_size_(0)

{
	//check to see if the current size of the array being passed in the constructor is larger than our default size
	if (array.cur_size_ > DEFAULT_SIZE) {
		this->max_size_ = array.cur_size_;
	}
	else {
		this->max_size_ = DEFAULT_SIZE;
	}


	this->data_ = new char[max_size_];
	this->cur_size_ = array.cur_size_;


	for (size_t x = 0; x < array.cur_size_; x++) {
		this->data_[x] = array.data_[x];
	}

}




//done
Array::~Array(void)
{
	//release allocated memory of data_
	delete[] data_;

}


//operator overloading
//done
const Array & Array::operator = (const Array & rhs)
{

	if (this == &rhs) {
		std::cout << "assignment to ourselves is not allowed" << std::endl;
		return *this;
	}

	//if max_size_ is < rhs current size (test later)
	if (this->max_size_ < rhs.cur_size_) {
		size_t length = rhs.cur_size_ + DEFAULT_SIZE;
		Array temp(length);
		std::swap(this->data_, temp.data_);
		this->max_size_ = temp.max_size_;
	}


	this->cur_size_ = rhs.cur_size_;

	for (size_t x = 0; x < rhs.cur_size_; x++) {
		this->data_[x] = rhs.data_[x];
	}

	return *this;
}


//operator overloading
//done
char & Array::operator [] (size_t index)
{

	if (index > this->cur_size_) {
		throw std::out_of_range("index out of bounds");
	}

	return this->data_[index];



}


//operator overloading
//done
const char & Array::operator [] (size_t index) const
{
	if (index > this->cur_size_) {
		throw std::out_of_range("index out of bounds");
	}

	return this->data_[index];


}


//get the value at index
//done
char Array::get(size_t index) const
{

	if (index > this->cur_size_) {
		throw std::out_of_range("index out of bounds");
	}

	std::cout << this->data_[index] << std::endl;
	return this->data_[index];

}


//set value at index
//done
void Array::set(size_t index, char value)
{

	std::cout << value << std::endl;

	if (index >= this->cur_size_) {
		throw std::out_of_range("index out of bounds");
	}

	this->data_[index] = value;

}



//resize array
void Array::resize(size_t new_size)
{

	/*Set a new size for the array.If \a new_size is less than the current
	* size, then the array is truncated.If \a new_size if greater then the
	* current size, then the array is made larger and the new elements are
	* not initialized to anything.If \a new_size is the same as the current
	* size, then nothing happens.
	*
	* The array's original contents are preserved regardless of whether the
	* array's size is either increased or decreased.*/

	if (new_size < this->cur_size_) {
		this->cur_size_ = new_size;
	}
	else if (new_size > this->cur_size_) {
		size_t length = new_size;
		Array temp(length);
		std::swap(temp.data_, this->data_);
		this->max_size_ = temp.max_size_;
		this->cur_size_ = temp.cur_size_;
	}
}



/**
* Locate the specified character in the array. The index of the first
* occurrence of the character is returned. If the character is not
* found in the array, then -1 is returned.
*
* @param[in]        ch        Character to search for
* @return           Index value of the character
* @retval           -1        Character not found
*/
int Array::find(char ch) const
{
	int notFound = -1;

	for (size_t x = 0; x < this->cur_size_; x++) {
		if (data_[x] == ch) {
			std::cout << "found index at " << x << std::endl;
			return x;
		}
	}

	std::cout << "character not found" << std::endl;
	return notFound;


}


/**
* @overload
*
* This version allows you to specify the start index of the search. If
* the start index is not within the range of the array, then the
* std::out_of_range exception is thrown.
*
* @param[in]       ch                   Character to search for
* @param[in]       start                Index to begin search
* @return          Index value of first occurrence
* @retval          -1                   Character not found
* @exception       std::out_of_range    Invalid index
*/

int Array::find(char ch, size_t start) const
{
	int notFound = -1;

	if (start > this->cur_size_) {
		throw std::out_of_range("index out of bounds");
	}

	for (size_t x = start; x < this->cur_size_; x++) {
		if (this->data_[x] == ch) {
			std::cout << "found character at index " << x << std::endl;
			return x;
		}
	}

	return notFound;

}

/**
* Test the array for equality.
*
* @param[in]       rhs                  Right hand side of equal to sign
* @retval          true                 Left side is equal to right side
* @retval          false                Left side is not equal to right side
*/
bool Array::operator == (const Array & rhs) const
{
	if (this == &rhs) {
		return true;
	}

	if (this->cur_size_ != rhs.cur_size_) {
		return false;
	}
	else {
		for (size_t x = 0; x < this->cur_size_; x++) {
			if (this->data_[x] != rhs.data_[x]) {
				return false;
			}
		}
	}

	return true;



}


/**
* Test the array for inequality.
*
* @param[in]       rhs                  Right-hand size of not equal to sign
* @retval          true                 Left side is not equal to right side
* @retval          false                Left size is equal to right side
*/
bool Array::operator != (const Array & rhs) const
{
	return !(*this == rhs);


}


/**
* Fill the contents of the array.
*
* @param[in]       ch                   Fill character
*/
void Array::fill(char ch)
{

	for (size_t x = 0; x < this->cur_size_; x++) {
		this->data_[x] = ch;
	}


}

size_t Array::size(void) const
{
	std::cout << this->cur_size_ << std::endl;
	return this->cur_size_;
}

inline


size_t Array::max_size(void) const
{
	return this->max_size_;
}

