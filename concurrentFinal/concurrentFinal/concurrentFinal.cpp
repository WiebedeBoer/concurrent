// concurrentFinal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//To successfully complete this course you must think up a programming project that could benefit from concurrency and implement it in C++11. 
//You may work individually or in pairs.

//You will be asked to demo and explain in a 10 minute session with your lecturer

//what your program does; how it works; which concurrency facilities of C++11 you used.
//Discuss your project idea before starting to ensure that the project is of sufficient size and complexity.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <thread> //for threading
#include <complex> // if you make use of complex number facilities in C++
//#include <HDC>

template <class T> struct RGB { T r, g, b; };


//template <class T>
//class Matrix {
//public:
//	Matrix(const size_t rows, const size_t cols) : _rows(rows), _cols(cols) {
//		_matrix = new T*[rows];
//		for (size_t i = 0; i < rows; ++i) {
//			_matrix[i] = new T[cols];
//		}
//	}
//	Matrix(const Matrix &m) : _rows(m._rows), _cols(m._cols) {
//		_matrix = new T*[m._rows];
//		for (size_t i = 0; i < m._rows; ++i) {
//			_matrix[i] = new T[m._cols];
//			for (size_t j = 0; j < m._cols; ++j) {
//				_matrix[i][j] = m._matrix[i][j];
//			}
//		}
//	}
//	~Matrix() {
//		for (size_t i = 0; i < _rows; ++i) {
//			delete[] _matrix[i];
//		}
//		delete[] _matrix;
//	}
//	T *operator[] (const size_t nIndex)
//	{
//		return _matrix[nIndex];
//	}
//	size_t width() const { return _cols; }
//	size_t height() const { return _rows; }
//protected:
//	size_t _rows, _cols;
//	T **_matrix;
//};
//
//// Portable PixMap image
//class PPMImage : public Matrix<RGB<unsigned char> >
//{
//public:
//	PPMImage(const size_t height, const size_t width) : Matrix(height, width) { }
//	void save(const std::string &filename)
//	{
//		std::ofstream out(filename, std::ios_base::binary);
//		out << "P6" << std::endl << _cols << " " << _rows << std::endl << 255 << std::endl;
//		for (size_t y = 0; y < _rows; y++)
//			for (size_t x = 0; x < _cols; x++)
//				out << _matrix[y][x].r << _matrix[y][x].g << _matrix[y][x].b;
//	}
//};

Graphics(
	[in]  HDC hdc
);


int main()
{
	const unsigned width = 3885;
	const unsigned height = 4000;
	const unsigned qheight = height / 2;

	image.load("shugo_map.png");
	Graphics graphics(hdc);
	Bitmap myBitmap(L"shugo_map.png");

	//thread 1
	std::thread t1([image]() {

		for (unsigned int piX = 0; piX < width; piX++) {
			for (unsigned int piY = 0; piY < qheight; piY++) {

				// Get the value of a pixel from myBitmap.
				//Color pixelColor;
				//myBitmap.GetPixel(25, 25, &pixelColor);

				//check if pixel is red
				if (image[piY][piX].r == 255 && image[piY][piX].g == 0 && image[piY][piX].b == 0) {
					std::cout << "<Xcoord>" << piX << "</Xcoord><Ycoord>" << piY << "</Ycoord>"; 
				}

			}
		}

	}

		//thread 2
		std::thread t2([image]() {

		for (unsigned int piX = 0; piX < width; piX++) {
			for (unsigned int piY = qheight; piY < height; piY++) {

				// Get the value of a pixel from myBitmap.
				//Color pixelColor;
				//myBitmap.GetPixel(25, 25, &pixelColor);

				//check if pixel is red
				if (image[piY][piX].r == 255 && image[piY][piX].g == 0 && image[piY][piX].b == 0) {
					std::cout << "<Xcoord>" << piX << "</Xcoord><Ycoord>" << piY << "</Ycoord>";
				}

			}
		}

	}
	
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
