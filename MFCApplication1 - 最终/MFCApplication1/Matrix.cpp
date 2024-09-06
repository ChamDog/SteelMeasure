// CMatrix.cpp: implementation of the CMatrix class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>
#include "pch.h"

//using std::cout;
//using std::endl;

#include <iomanip>

using std::setw;

#include <cassert>
#include <math.h>
#include "Matrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// initialize static data member at file scope
int CMatrix::CMatrixCount = 0;	// no objects yet

// Default constructor for class CMatrix ( default size 1,1 )
CMatrix::CMatrix( int row, int col )
{
	rows = ( row > 0 ? row : 1 );
	cols = ( col > 0 ? col : 1 );
	ptr = new double[ rows * cols ];	// create space for CMatrix
	assert( ptr != 0 );		// terminate if memory nor allocated
	++CMatrixCount;			// count one more object
	
	for ( int i = 0; i < rows * cols; i++ )
		ptr[ i ] = 0;			// initialize CMatrix
}

// Copy constructor for class CMatrix ( default size 1,1 )
CMatrix::CMatrix( const CMatrix &init ) : rows( init.rows ), cols( init.cols )
{
	ptr = new double[ rows * cols ];	// create space for CMatrix
	assert( ptr != 0 );				// terminate if memory nor allocated
	++CMatrixCount;					// count one more object
	
	for ( int i = 0; i < rows * cols; i++ )
		ptr[ i ] = init.ptr[ i ];			// copy init into object
}

// Destructor for class CMatrix
CMatrix::~CMatrix()
{
	delete [] ptr;	// reclaim space for CMatrix
	--CMatrixCount;	// one fewer object
}

// copy a single pointer array in to the CMatrix
const CMatrix &CMatrix::copyArray( int r, int c, const double *array )
{
	CMatrix buffer( r, c );
	
	for ( int i = 0; i < r * c; i++)
		buffer.ptr[ i ] = array[ i ];
	
	*this = buffer;
	
	return *this;
}


// Get the size of the CMatrix
int CMatrix::getSize() const { return  rows * cols; }

// Get the number of rows
int CMatrix::rowsCount() const { return rows; }

// Get the number of coloumns
int CMatrix::colsCount() const { return cols; }

// Return true if the CMatrix is a square CMatrix
// false otherwise
bool CMatrix::isSquare() const { return ( cols == rows ); }

// Retun the max value in the CMatrix
double CMatrix::getMaxVal() const
{
	double maxVal;	// variable to keep the max Value
	
	maxVal = ptr[ 0 ];
	
	for ( int i = 1; i < cols * rows; i ++ )
		if ( ptr[ i ] > maxVal )
			maxVal = ptr[ i ];
		
		return maxVal;
}

// Retun the max value of a row of the CMatrix
double CMatrix::getMaxRowVal( const int r ) const
{
	assert( r < rows );	// check the row number
	
	double maxVal;	// variable to keep the max Value
	
	maxVal = ptr[ r * cols ];
	
	for ( int i = r * cols; i < r * cols + cols; i ++ )
		if ( ptr[ i ] > maxVal )
			maxVal = ptr[ i ];
		
		return maxVal;
}

// Retun the max value of a column of the CMatrix
double CMatrix::getMaxColVal( const int c ) const
{
	assert( c < cols );	// check the column number
	
	double maxVal;	// variable to keep the max Value
	
	maxVal = ptr[ c ];
	
	for ( int i = c; i <= ( rows - 1 ) * cols + c; i += cols )
		if ( ptr[ i ] > maxVal )
			maxVal = ptr[ i ];
		
		return maxVal;
}

// Retun the min value in the CMatrix
double CMatrix::getMinVal() const
{
	double minVal;	// variable to keep the min Value
	
	minVal = ptr[ 0 ];
	
	for ( int i = 1; i < cols * rows; i ++ )
		if ( ptr[ i ] < minVal )
			minVal = ptr[ i ];
		
		return minVal;
}

// Retun the min value of a row of the CMatrix
double CMatrix::getMinRowVal( const int r ) const
{
	assert( r < rows );	// check the row number
	
	double minVal;	// variable to keep the min Value
	
	minVal = ptr[ r * cols ];
	
	for ( int i = r * cols; i < r * cols + cols; i ++ )
		if ( ptr[ i ] < minVal )
			minVal = ptr[ i ];
		
		return minVal;
}

// Retun the min value of a column of the CMatrix
double CMatrix::getMinColVal( const int c ) const
{
	assert( c < cols );	// check the column number
	
	double minVal;	// variable to keep the min Value
	
	minVal = ptr[ c ];
	
	for ( int i = c; i <= ( rows - 1 ) * cols + c; i += cols )
		if ( ptr[ i ] < minVal )
			minVal = ptr[ i ];
		
		return minVal;
}


// Retun the mean of the values in the CMatrix
double CMatrix::getMean() const
{
	double total = 0;	// variable to keep the total Value
	
	for ( int i = 1; i < cols * rows; i ++ )
		total += ptr[ i ];
	
	return ( total / ( cols * rows ) );
}

// Retun the mean value of a row of the CMatrix
double CMatrix::getRowMean( const int r ) const
{
	assert( r < rows );	// check the row number
	
	double total = 0;	// variable to keep the total Value
	
	for ( int i = r * cols; i < r * cols + cols; i ++ )
		total += ptr[ i ];
	
	return ( total / cols );
}

// Retun the mean value of a column of the CMatrix
double CMatrix::getColMean( const int c ) const
{
	assert( c < cols );	// check the column number
	
	double total = 0;	// variable to keep the total Value
	
	for ( int i = c; i <= ( rows - 1 ) * cols + c; i += cols )
		total += ptr[ i ];
	
	return ( total / rows );
}

// find the value in the CMatrix and return as a nx2 CMatrix
const CMatrix CMatrix::findVal( const double v ) const
{
	CMatrix buffer( 1, 2 );
	CMatrix temp( 1, 2 );
	
	for ( int i = 0; i < cols * rows; i++)
	{
		if ( ptr[ i ] == v )
		{
			temp(0, 0 ) = i / cols;
			temp(0, 1 ) = i % cols;
			buffer.insertRow( buffer.rows - 1, temp );
		}
	}
	
	buffer.deleteRow( buffer.rows - 1 ); // delete the last row 0 0.
	
	return buffer;	// return as nx2 CMatrix
}


// Return the number of value in the CMatrix
int CMatrix::getValCount( const double v ) const
{
	int count = 0;
	
	for ( int i = 0; i < cols * rows; i++ )
		if ( ptr[ i ] == v )
			count++;
		
		return count;
}

// Overloaded Operators .........................................................

// Overloaded assignment operator
// const return avoids ( a1 = a2 ) = a3
const CMatrix &CMatrix::operator =( const CMatrix &right )
{
	if ( &right != this ) {	//check for self assignment
		// for arrays of different sizes, deallocate original
		// left side array, then allocate new left side array.
		if ( cols != right.cols  || rows != right.rows ) {
			delete [] ptr;					// reclaim space;
			rows = right.rows;				// resize the object
			cols = right.cols;				// resize the object
			ptr = new double[ rows * cols ];	// create space for CMatrix copy
			assert( ptr != 0 );				// terminate if not allocated
		}
		
		for ( int i = 0; i < rows * cols; i++ )
			ptr[ i ] = right.ptr[ i ];		// copy array into object
	}
	return *this;	// enables x = y = z;
}

// Overloaded assignment operator
// const return avoids ( a1 = a2 ) = a3
const CMatrix &CMatrix::operator =( const char ch )
{
	assert( ch == 'I' && isSquare() );
	
	if ( ch == 'I' )
		for ( int i = 0; i < rows * cols; i++ )
			if ( i / cols == i % cols )	
				ptr[ i ] = 1;		// put 1's in the diagonals
			else
				ptr[ i ] = 0;		// put 0's in the other cells
			
			return *this;	// enables x = y = z;
}

// Determine if two arrays are equal and
// return true, otherwise return false.
bool CMatrix::operator ==( const CMatrix &right ) const
{
	if ( cols != right.cols  || rows != right.rows )
		return false;			// CMatrix's of different sizes
	
	for ( int i = 0; i < rows * cols; i++ )
		if ( ptr[ i ] != right.ptr[ i ] )
			return false;		// arrays are not equal
		
		return true;				// arrays are equal
}

// Overloaded addition operator
// add a fixed value to the CMatrix
CMatrix CMatrix::operator +( const double value )
{
	CMatrix buffer( rows, cols ); // create a temp CMatrix object not to change this
	
	for ( int i = 0; i < rows * cols; i++ )
		buffer.ptr[ i ] = ptr[ i ] + value;	// add value to all member of the CMatrix
	
	// return temporary object not to change this
	return buffer;			// value return; not a reference return
}

// Overloaded addition operator
// add two CMatrixs's
CMatrix CMatrix::operator +( const CMatrix &right )
{
	CMatrix buffer( rows, cols );	// create a temp CMatrix object not to change this
	
	// terminate if matrices are not in the same size
	assert( cols == right.cols && rows == right.rows );
	
	for ( int i = 0; i < rows * cols; i++ )
		buffer.ptr[ i ] = ptr[ i ] + right.ptr[ i ];
	
	// return temporary object not to change this
	return buffer;			// value return; not a reference return
}

// Overloaded addition operator
// add a fixed value to the CMatrix modify CMatrix
void CMatrix::operator +=( const double value )
{
	for ( int i = 0; i < rows * cols; i++ )
		ptr[ i ] = ptr[ i ] + value;	// add value to all member of the CMatrix
	
}

// Overloaded addition operator
// add two CMatrixs's modify this CMatrix
void CMatrix::operator +=( const CMatrix &right )
{
	// terminate if matrices are not in the same size
	assert( cols == right.cols && rows == right.rows );
	
	for ( int i = 0; i < rows * cols; i++ )
		ptr[ i ] = ptr[ i ] + right.ptr[ i ];
	
}


// Overloaded substraction operator
// substract a fixed value from a CMatrix
CMatrix CMatrix::operator -( const double value )
{
	CMatrix buffer( rows, cols ); // create a temp CMatrix object not to change this
	
	for ( int i = 0; i < rows * cols; i++ )
		buffer.ptr[ i ] = ptr[ i ] - value;	// substract a value from all member of the CMatrix
	
	// return temporary object not to change this
	return buffer;			// value return; not a reference return
}

// Overloaded substraction operator
// substract a CMatrix right from this
CMatrix CMatrix::operator -( const CMatrix &right )
{
	CMatrix buffer( rows, cols );	// create a temp CMatrix object not to change this
	
	// terminate if matrices are not in the same size
	assert( cols == right.cols && rows == right.rows );
	
	for ( int i = 0; i < rows * cols; i++ )
		buffer.ptr[ i ] = ptr[ i ] - right.ptr[ i ];
	
	// return temporary object not to change this
	return buffer;			// value return; not a reference return
}

// Overloaded substraction operator
// substract a fixed value from a CMatrix modify this CMatrix
void CMatrix::operator -=( const double value )
{
	for ( int i = 0; i < rows * cols; i++ )
		ptr[ i ] = ptr[ i ] - value;	// substract a value from all member of the CMatrix
	
}

// Overloaded substraction operator
// substract a CMatrix right from this modify this CMatrix
void CMatrix::operator -=( const CMatrix &right )
{
	// terminate if matrices are not in the same size
	assert( cols == right.cols && rows == right.rows );
	
	for ( int i = 0; i < rows * cols; i++ )
		ptr[ i ] = ptr[ i ] - right.ptr[ i ];
	
}

// Overloaded multiplication operator
// Multiply a CMatrix with a value
CMatrix CMatrix::operator *( const double value )
{
	CMatrix buffer( rows, cols );	// create a temp CMatrix object not to change this
	
	for ( int i = 0; i < rows * cols; i++ )
		buffer.ptr[ i ] = ptr[ i ] * value;
	
	// return temporary object not to change this
	return buffer;			// value return; not a reference return
}

// Overloaded multiplicatipn operator
// Multiply two matrices 
CMatrix CMatrix::operator *( const CMatrix &right )
{
	CMatrix buffer( rows, right.cols );  // a CMatrix of (m x k)
	double temp;
	
	// terminate if matrices are not in the format: (m x n), (n x k)
	assert( cols == right.rows );
	
	for ( int i = 0; i < rows; i++ ) {
		for ( int k = 0; k < right.cols; k++ ) {
			temp = 0;
			for ( int j = 0; j < cols; j++ ) {
				temp += ptr[ i * cols + j ] * right.ptr[ j * right.cols + k ];
			}
			buffer.ptr[ i * right.cols + k ] = temp; 
		}
	}
	
	return buffer;
}

// Overloaded multiplication operator
// Multiply a CMatrix with a value modify this CMatrix
void CMatrix::operator *=( const double value )
{
	for ( int i = 0; i < rows * cols; i++ )
		ptr[ i ] = ptr[ i ] * value;
	
}

// Overloaded multiplicatipn operator
// Multiply two matrices modify this CMatrix	  ( ! SLOWER THAN * ! )
void CMatrix::operator *=( const CMatrix &right )
{
	CMatrix buffer( rows, right.cols );  // a CMatrix of (m x k)
	double temp;
	
	// terminate if matrices are not in the format: (m x n), (n x k)
	assert( cols == right.rows );
	
	for ( int i = 0; i < rows; i++ ) {
		for ( int k = 0; k < right.cols; k++ ) {
			temp = 0;
			for ( int j = 0; j < cols; j++ ) {
				temp += ptr[ i * cols + j ] * right.ptr[ j * right.cols + k ];
			}
			buffer.ptr[ i * right.cols + k ] = temp; 
		}
	}
	
	*this = buffer;	// using a buffer to calculate the result
	//then copy buffer to this
}


// Overloaded power operator
// Take the value th power of the CMatrix
CMatrix CMatrix::operator ^( const int value )
{
	assert( isSquare() && value > 0 );
	
	CMatrix buffer( rows, cols );	// a CMatrix( rows, cols )
	
	buffer = *this;
	
	for ( int i = 1; i < value; i++ )
		buffer = buffer * *this;
		
	return buffer;
}

// Overloaded division operator
// Divide the CMatrix by value
CMatrix CMatrix::operator /( const double value )
{
	assert( value != 0 );
	
	CMatrix buffer( rows, cols );	// a CMatrix( rows, cols )
	
	for ( int i = 0; i < rows * cols; i++ )
		buffer.ptr[ i ] = ptr[ i ] / value;
	
	// return temporary object not to change this
	return buffer;			// value return; not a reference return
}

// Overloaded division operator
// Divide the CMatrix by value
void CMatrix::operator /=( const double value )
{
	assert( value != 0 );
	
	for ( int i = 0; i < rows * cols; i++ )
		ptr[ i ] = ptr[ i ] / value;
	
}

// Overloaded subscript operator for non-const CMatrix
// reference return creates an lvalue
double &CMatrix::operator ()( int r, int c )
{
	// check for subscript out of range error
	assert( 0 <= r && r < rows && 0 <= c && c < cols );
	
	return ptr[ r * cols + c ];	// reference return
}

// Overloaded subscript operator for const CMatrix
// const reference return creates an rvalue
const double &CMatrix::operator ()( int r, int c ) const
{
	// check for subscript out of range error
	assert( 0 <= r && r <= rows && 0 <= c && c <= cols );
	
	return ptr[ r  * cols + c ];	// const reference return
}

// Return the number of CMatrix objects instantiated
// static functions can not be const
int CMatrix::getCMatrixCount() { return CMatrixCount; }


// methods of the class CMatrix

// convert CMatrix to identity CMatrix of the same size
const CMatrix &CMatrix::convToIdentity()
{
	assert( isSquare() );
	
	for ( int i = 0; i < rows * cols; i++ )
		if ( i / cols == i % cols )	
			ptr[ i ] = 1;		// put 1's in the diagonals
		else
			ptr[ i ] = 0;		// put 0's in the other cells
		
		return *this;	// enables x = y = z;
}

// convert CMatrix to inverse diagonal
const CMatrix &CMatrix::convToInvDiagonal()
{
	assert( isSquare() );
	
	for ( int i = 0; i < rows * cols; i++ )
		if ( ( i / cols ) + ( i % cols ) + 1 == cols )	
			ptr[ i ] = 1;		// put 1's in the inv diagonals
		else
			ptr[ i ] = 0;		// put 0's in the other cells
		
		return *this;	// enables x = y = z;
}

// Return the transpose of a CMatrix
// modifying the original CMatrix
CMatrix &CMatrix::getTranspose() 
{
	CMatrix buffer( cols, rows );	// create the buffer CMatrix
	
	for(int i=0; i<cols; i++)
		for(int j=0; j<rows; j++)
		{
			buffer.ptr[i*rows+j] = ptr[j*cols+i];
		}

	*this = buffer;

	return *this;
}

// calculate the LUD of the CMatrix
int CMatrix::LUD( int phy_size, int *outvect, int output )
{
	int	    i, j, k, imax; 
    double  *VV, aamax, sum, dnum; 
	double SMALL = 1.0e-20;

	// allocate space for VV; and check if space allocated
    if ( ( VV = (double *) malloc ( 1000 * sizeof(double) ) ) == NULL )
	{
		exit( 1 );
    }
	
	
    output = 1; 	     /* No row interchanges yet*/
    
    for ( i = 0; i < rows; i++ ) {
		aamax = 0.0;
		for ( j = 0; j < rows; j++ ) {
			if( fabs( ptr[ i * cols + j ] ) > aamax )
				aamax = fabs( ptr[ i * cols + j ] );
		}
		if ( aamax == 0. ) {
			return 1; /* LUD_ERR flag Singular CMatrix */
		}
		VV[ i ] = 1.0 / aamax;
    }
    
    for ( j = 0; j < rows; j++ ) {
		if ( j > 0 ) {
			for ( i = 0; i < j; i++ ) {
				sum = ptr[ i * cols + j ];
				if ( i > 0 ) {
					for ( k = 0; k < i; k++ )
						sum = sum - ( ptr[ i * cols + k ] * ptr[ k * cols + j ] );
					ptr[ i * cols + j ] = sum;
				}
			}
		}

		aamax = 0.;

		for ( i = j; i < rows; i++ ) {
			sum = ptr[ i * cols + j ];
			if ( j > 0 ) {
				for ( k = 0; k < j; k++ )
					sum = sum - ( ptr[ i * cols + k ] * ptr[ k * cols + j ] );
				ptr[ i * cols + j ] = sum;
			}
			dnum = VV[ i ] * fabs( sum );
			if( dnum >= aamax ) {
				imax = i;
				aamax = dnum;
			}
		}
		if ( j != imax ) {
			for ( k = 0; k < rows; k++ ) {
				dnum = ptr[ imax * cols + k ];
				ptr[ imax * cols + k ] = ptr[ j * cols + k ];
				ptr[ j * cols + k ] = dnum;
			}
			output = -output;
			VV[ imax ] = VV[ j ];
		}
		outvect[ j ] = imax;
		if ( j != ( rows - 1 ) ) {
			if ( ptr[ j * cols + j ] == 0. )
				ptr[ j * cols + j ] = SMALL;
			dnum = 1.0 / ptr[ j * cols + j ];
			for ( i = ( j + 1 ); i < rows; i++ )
				ptr[ i * cols + j ] = ptr[ i * cols + j ] * dnum;
		}
    }
    if ( ptr[ ( rows - 1 ) * cols + ( rows - 1 ) ] == 0. )
		ptr[ ( rows - 1 ) * cols + ( rows - 1 ) ] = SMALL;
    free( VV );

    return 0; /* normal return */
}

// calculate the LUD of the CMatrix
void CMatrix::LUBKS( int phy_size, int *outvect, double *output )
{
	int	i, j, ii, ll;
    double	sum;
	
    ii = -1;  /*when ii is set to a value >= 0 it is an index to
	the first nonvanishing element of the output*/

    for ( i = 0; i < rows; i++ ) {
		ll = outvect[ i ];
		sum = output[ ll ];
		output[ ll ] = output[ i ];
		if ( ii != -1 ) {
			for ( j = ii; j < i; j++ )
				sum = sum - ( ptr[ i * cols + j ] * output[ j ] );
		}
		else if ( sum != 0. ) {
			ii = i ; 
		}
		output[ i ] = sum;
    }
    for ( i = ( rows - 1 ); i > -1; i-- ) {
		sum = output[ i ];
		if ( i < ( rows - 1 ) ) {
			for ( j = ( i + 1 ); j < rows; j++ )
				sum = sum - ( ptr[ i * cols + j ] * output[ j ] );
		}
		output[ i ] = sum / ptr[ i * cols + i ];
    }
	
}

// get the inverse of the CMatrix
CMatrix &CMatrix::getInverse()
{
	// check if the CMatrix is a square CMatrix
	assert( isSquare() );

	double *temp;
    int    *IND, D = 0, i, j;

		// check if space allocated for temp.
	if ( (temp = (double *) malloc(rows * sizeof(double))) == NULL )
	{
		exit(1);
	}
	// check if space allocated for IND.
	if ( (IND = (int *) malloc(rows * sizeof(int))) == NULL )
	{
		exit(1);
	}

	// create the buffer CMatrix
	CMatrix buffer( rows, cols );
	CMatrix result( rows, cols );

	buffer = *this;

	if ( buffer.LUD( rows, IND, D ) == 1 )
	{
		free(temp);
		free(IND);
		assert( !buffer.LUD( rows, IND, D ) );
	}
    for ( j = 0; j < buffer.rows; j++ )//bakiniz
	{
		for ( i = 0; i < buffer.rows; i++ )
			temp[i] = 0.0;
		temp[j] = 1.0;

		buffer.LUBKS( rows, IND, temp);

		for ( i = 0; i < buffer.rows; i++ )
			result.ptr[ i * cols + j ] = temp[ i ];
    }

    free( temp );
	free( IND );

	*this = result;

	return *this;
}


// Return a sub CMatrix of a CMatrix
// without modifying the original CMatrix
CMatrix CMatrix::getSubCMatrix( const int startRow, const int startCol,
							const int rowSize, const int colSize ) const
{
	// check if really the subCMatrix is in the CMatrix
	assert( 0 <= startRow && startRow + rowSize < rows
		&& 0 <= startCol && startCol + colSize < cols );
	
	CMatrix buffer( rowSize + 1, colSize + 1 );	// create the empty subCMatrix
	
	for ( int i = startRow;	i <= startRow + rowSize; i++ )
		for ( int j = startCol; j <=startCol + colSize; j++)
			buffer.ptr[ ( i - startRow ) * ( colSize + 1 ) + j - startCol ] =
			ptr [ i * cols + j ];
		
		return buffer;
}

// Delete a row from the CMatrix
CMatrix &CMatrix::deleteRow( const int r )
{
	// check if r is a valid row number
	assert( 0 <= r && r < rows );
	
	int i;
	
	CMatrix buffer( rows - 1, cols );	// create the buffer CMatrix
	
	for ( i = 0; i / cols < r ; i++ )
		buffer.ptr[ i ] = ptr[ i ];
	for ( i = ( r + 1 ) * cols; i < rows * cols; i++ )
		buffer.ptr[ i - cols ] = ptr[ i ];
	
	*this = buffer;  // copy the buffer to this
	
	return *this;  // reference return; enables cascading.
}

// Delete a coloumn from the CMatrix
CMatrix &CMatrix::deleteCol( const int c )
{
	// check if c is a valid coloumn number
	assert( 0 <= c && c < cols );
	
	int i, j;
	
	CMatrix buffer( rows, cols - 1 );	// create the buffer CMatrix
	
	for ( j = 0; j < c; j++ ) {
		for ( i = 0; i / cols < rows; i += cols )
			buffer.ptr[ ( i / cols ) * ( cols - 1 ) + j ] = 
			ptr[ i + j ];
	}
	
	for ( j = c + 1; j < cols; j++ ) {
		for (i = 0; i / cols < rows; i += cols )
			buffer.ptr[ ( i / cols ) * ( cols - 1) + j - 1 ] = 
			ptr [ i + j ];  
	}
	
	*this = buffer;  // copy the buffer to this
	
	return *this;  // reference return; enables cascading.
}

// inserts the row CMatrix to the given row shifting other rows down
CMatrix &CMatrix::insertRow( const int r, const CMatrix &rVector ) 
{
	// check if rVector is a 1xn CMatrix
	assert( rVector.rows == 1 && rVector.cols == cols && r < rows );
	
	CMatrix buffer( rows + 1, cols );	// create the buffer CMatrix
	
	int i;
	
	// first copying the rows till r...	
	for ( i = 0; i / cols < r ; i++ )
		buffer.ptr[ i ] = ptr[ i ];
	
	// now copying the rVector into the rth row..
	for ( i = 0; i < cols; i ++)
		buffer.ptr[ r * cols + i ] = rVector.ptr[ i ];
	
	// copying the rows after r...
	for ( i = r * cols; i < rows * cols; i++ )
		buffer.ptr[ i + cols ] = ptr[ i ];
	
	*this = buffer;  // copy the buffer to this
	
	return *this;  // reference return; enables cascading.
}

// inserts the column CMatrix to the given column shifting other columns right
CMatrix &CMatrix::insertCol( const int c, const CMatrix &cVector )
{
	// check if cVector is a nx1 CMatrix
	assert( cVector.cols == 1 && cVector.rows == rows && c < cols );
	
	CMatrix buffer( rows, cols + 1 );	// create the buffer CMatrix
	int i, j;
	
	for ( i = 0; i < c; i++ ) {
		for ( j = 0; j < rows; j++ )
			buffer.ptr[ j * ( cols + 1 ) + i ] = ptr[ j * cols + i ];
	}
	
	for ( j = 0; j < rows; j++ )
		buffer.ptr[ j * ( cols + 1 ) + c ] = cVector.ptr[ j ];
	
	for ( i = c + 1; i < cols + 1; i++ ) {
		for ( j = 0; j < rows; j++ )
			buffer.ptr[ j * ( cols + 1 ) + i ] = ptr [ j * cols + i - 1 ];
	}
	
	
	*this = buffer;  // copy the buffer to this
	
	return *this;  // reference return; enables cascading.
}

// interchange rows in the CMatrix ( r1 <-> r2 )
CMatrix &CMatrix::interchangeRows( const int r1, const int r2 )
{
	// check if r1 and r2 row numbers are valid.
	assert( 0 <= r1 && r1 < rows && 0 <= r2 && r2 < rows );
	
	int rUp, rDown, i;
	
	CMatrix buffer( rows, cols );
	
	if ( r1 != r2 ) {
		// check which value is bigger.
		if ( r1 > r2 ) {
			rUp = r1;
			rDown = r2;
		}
		else {
			rUp = r2;
			rDown = r1;
		}							   		
		for ( i = 0; i / cols < rDown; i++ )
			buffer.ptr[ i ] = ptr[ i ];
		for ( i = rUp * cols; i < rUp * cols + cols; i++ )
			buffer.ptr[ i - ( ( rUp - rDown ) * cols ) ] = ptr[ i ];
		for ( i = ( rDown + 1 ) * cols; i < rUp * cols; i ++ )
			buffer.ptr[ i ] = ptr[ i ];
		for ( i = rDown * cols; i < rDown * cols + cols; i++ )
			buffer.ptr[ i + ( ( rUp - rDown ) * cols ) ] = ptr[ i ];
		for ( i = ( rUp + 1 ) * cols; i < rows * cols; i++ )
			buffer.ptr[ i ] = ptr[ i ];
	}
	
	*this = buffer;	// copy the buffer to this
	
	return *this;
}

// interchange columns in the CMatrix ( c1 <-> c2 )
CMatrix &CMatrix::interchangeCols( const int c1, const int c2 )
{
	// check if r1 and r2 row numbers are valid.
	assert( 0 <= c1 && c1 < cols && 0 <= c2 && c2 < cols );
	
	int cUp, cDown;
	
	CMatrix buffer( rows, cols );
	
	if ( c1 != c2 ) {
		// check which value is bigger.
		if ( c1 > c2 ) {
			cUp = c1;
			cDown = c2;
		}
		else {
			cUp = c2;
			cDown = c1;
		}
		
		int i, j;
		
		for ( i = 0; i < cDown; i++ ) {
			for ( j = 0; j < rows; j++ )
				buffer.ptr[ j * cols + i ] = ptr[ j * cols + i ];
		}
		
		for ( j = 0; j < rows; j++ )
			buffer.ptr[ j * cols + cDown ] = ptr[ j * cols + cUp ];
		
		for ( i = cDown + 1; i < cUp; i++ ) {
			for ( j = 0; j < rows; j++ )
				buffer.ptr[ j * cols + i ] = ptr [ j * cols + i ];
		}

		for ( j = 0; j < rows; j++ )
			buffer.ptr[ j * cols + cUp ] = ptr[ j * cols + cDown ];

		for ( i = cUp + 1; i < cols; i++ ) {
			for ( j = 0; j < rows; j++ )
				buffer.ptr[ j * cols + i ] = ptr [ j * cols + i ];
		}
	}
	
	*this = buffer;	// copy the buffer to this
	
	return *this;
	
}


// add the right CMatrix on top of this
CMatrix &CMatrix::attachTop( const CMatrix &right )
{
	// check if both matrices have the same number of columns
	assert( right.cols == cols );
	
	// create the buffer CMatrix of needed size
	CMatrix buffer( rows + right.rows, cols );
	
	for ( int i = 0; i < right.rows * right.cols; i++ )
		buffer.ptr[ i ] = right.ptr[ i ];
	for ( int j = right.rows * right.cols; j < ( rows + right.rows ) * cols; j++ )
		buffer.ptr[ j ] = ptr[ j - ( right.rows * right.cols ) ];
	
	*this = buffer;
	
	return *this;	// enable cascading
}

// add the right CMatrix under this
CMatrix &CMatrix::attachBottom( const CMatrix &right )
{
	// check if both matrices have the same number of columns
	assert( right.cols == cols );
	
	// create the buffer CMatrix of needed size
	CMatrix buffer( rows + right.rows, cols );
	
	for ( int i = 0; i < rows * cols; i++ )
		buffer.ptr[ i ] = ptr[ i ];
	for ( int j = rows * cols ; j < ( rows + right.rows ) * cols; j++ )
		buffer.ptr[ j ] = right.ptr[ j - ( rows * cols )];
	
	*this = buffer;
	
	return *this;	// enable cascading
}

// add the right CMatrix to the left of this
CMatrix &CMatrix::attachLeft( const CMatrix &right )
{
	// check if both matrices have the same number of rows
	assert( right.rows == rows );
	
	// create the buffer CMatrix of needed size
	CMatrix buffer( rows, cols + right.cols );
	int i,j;
	
	// First copying the right CMatrix to the buffer
	for ( i = 0; i < right.cols; i++ ) {
		for ( j = 0; j < right.rows; j++ )
			buffer.ptr[ j * ( cols + right.cols ) + i ] = 
			right.ptr[ j * right.cols + i ];
	}
	
	// copying the this CMatrix to the right side of the buffer.
	for ( i = right.cols; i < cols + right.cols; i++ ) {
		for ( j = 0; j < rows; j++ )
			buffer.ptr[ j * ( cols + right.cols ) + i ] = 
			ptr[ j * cols + i - right.cols ];
	}
	
	*this = buffer;
	
	return *this;	// enable cascading
}

// add the right CMatrix to the right of this
CMatrix &CMatrix::attachRight( const CMatrix &right )
{
	// check if both matrices have the same number of rows
	assert( right.rows == rows );
	
	// create the buffer CMatrix of needed size
	CMatrix buffer( rows, cols + right.cols );
	int i,j;
	
	// First copying the this CMatrix to the left side of the buffer
	for ( i = 0; i < cols; i++ ) {
		for ( j = 0; j < rows; j++ )
			buffer.ptr[ j * ( cols + right.cols ) + i ] = 
			ptr[ j * cols + i ];
	}
	
	// copying the this CMatrix to the left side of the buffer.
	for ( i = cols; i < cols + right.cols; i++ ) {
		for ( j = 0; j < right.rows; j++ )
			buffer.ptr[ j * ( cols + right.cols ) + i ] = 
			right.ptr[ j * right.cols + i - cols ];
	}
	
	*this = buffer;
	
	return *this;	// enable cascading
}

// friend function definitions............................................

// Overloaded addition operator
// add a fixed value to the CMatrix, CMatrix as rvalue;
CMatrix operator+( const double value, const CMatrix &right )
{
	CMatrix buffer( right.rows, right.cols ); // create a temp CMatrix object not to change right
	
	for ( int i = 0; i < right.rows * right.cols; i++ )
		buffer.ptr[ i ] = right.ptr[ i ] + value;	// add value to all members of the CMatrix
	
	// return temporary object not to change right
	return buffer;			// value return; not a reference return
}
/*
// Overloaded substraction operator
// substract the CMatrix from a fixed value;

CMatrix operator-( const double value, const CMatrix &right )
{
	CMatrix buffer( right.rows, right.cols ); // create a temp CMatrix object not to change right
	
	for ( int i = 0; i < right.rows * right.cols; i++ )
		buffer.ptr[ i ] = value - right.ptr[ i ];	// substract CMatrix from the value;
	
	// return temporary object not to change right
	return buffer;			// value return; not a reference return
}
*/
// Overloaded multiplication operator
// multiply a fixed value to the CMatrix, CMatrix as rvalue;
CMatrix operator*( const double value, const CMatrix &right )
{
	CMatrix buffer( right.rows, right.cols ); // create a temp CMatrix object not to change right
	
	for ( int i = 0; i < right.rows * right.cols; i++ )
		buffer.ptr[ i ] = right.ptr[ i ] * value;	// multiply value to all members of the CMatrix
	
	// return temporary object not to change right
	return buffer;			// value return; not a reference return
}




double CMatrix::getCMatrixSum() const
{
	double sum = 0;	// variable to keep the max Value

	for ( int i = 0; i < cols * rows; i ++ )
			sum += ptr[ i ];
		
		return sum;
}

double * CMatrix::GetBuffer()
{
	return ptr;
}

CMatrix &CMatrix::DeleteBuffer()
{
	if(cols * rows == 1)
		return *this;

	rows = cols = 1;
	CMatrix buffer( rows, cols);	// create the buffer CMatrix
	buffer.ptr[0]  = 0;

	*this = buffer;  // copy the buffer to this
	
	return *this;  // reference return; enables cascading.
}
