// CMatrix.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMatrix_H__E6551543_A986_4403_84EA_8B621BDBC795__INCLUDED_)
#define AFX_CMatrix_H__E6551543_A986_4403_84EA_8B621BDBC795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CMatrix {
		   
	friend CMatrix operator+( const double, const CMatrix & ); // CMatrix as rvalue;		
//	friend CMatrix operator-( const double, const CMatrix & ); // CMatrix as rvalue;		 
	friend CMatrix operator*( const double, const CMatrix & ); // CMatrix as rvalue;		 
																					 
public:
	CMatrix &DeleteBuffer();
	double * GetBuffer();
	double getCMatrixSum() const;
	CMatrix( int = 1, int = 1 );	// constructor
	CMatrix( const CMatrix & );	// copy constructor
	~CMatrix();					// destructor

	// copy a single pointer array in to the CMatrix
	const CMatrix &copyArray( int r, int c, const double *array );  

	int getSize() const;		// get size of the CMatrix	
	int rowsCount() const;		// get number of rows		
	int colsCount() const;		// get number of coloumns	

	double getMaxVal() const;	// return the max value of the CMatrix	
	double getMaxColVal( const int c ) const; // return the max value of the cth col.	 
    double getMaxRowVal( const int r ) const; // return the max value of the rth row.	
	
	double getMinVal() const; // return the min value of the CMatrix		
	double getMinColVal( const int c ) const; // return the min value of the cth col   
	double getMinRowVal( const int r ) const; // return the min value of the rth row   
	
	double getMean() const;		// return the mean of the values of the CMatrix	  
	double getColMean( const int c ) const; // return the mean of the values of the cth col.  
	double getRowMean( const int r ) const; // return the mean of the values of the rth row	  

	// find the value in the CMatrix and return as a nx2 CMatrix
	const CMatrix findVal( const double v ) const;				 
	int getValCount( const double v ) const;	// return the number of value in the CMatrix	   

	bool isSquare() const;		// return true if the CMatrix is square, false o/w. 

	// operator overleading.........

	const CMatrix &operator=( const CMatrix & );	// assign CMatrix's		  
	const CMatrix &operator=( const char );		// I icin				  
	
	// Overloaded comparison operators 
	bool operator==( const CMatrix & ) const;	// compare equal		  
	
	// Determine if two CMatrix's are equal and
	// return true, otherwise return false (uses operator==).
	bool operator!=( const CMatrix &right ) const					 
	{ return ! ( *this == right ); }
	
	// Overloaded subscript operators
	double &operator()( int, int );				// subscript operator		 
	const double &operator()( int, int ) const;	// subscript operator		 
	
	// Overloaded math operators
	
	CMatrix operator+( const CMatrix & );	// add two Matrices					
	CMatrix operator+( const double );	// add a value to a CMatrix			

	// add two Matrices modify this											 
	void operator+=( const CMatrix & );
	// add a value to a CMatrix modify this									 
	void operator+=( const double );  
	
	CMatrix operator-( const CMatrix & ); // substract one CMatrix from an other  
	CMatrix operator-( const double );	// substract a value from a CMatrix	   

    // substract one CMatrix from an other modify this CMatrix				  
	void operator-=( const CMatrix & ); 										  
	// substract a value from a CMatrix modify this CMatrix					  
	void operator-=( const double );  
	
	CMatrix operator*( const CMatrix & );	// multiply a CMatrix with an other	   
	CMatrix operator*( const double );										 
																			  
	// multiply a CMatrix with an other modify this CMatrix
	void operator*=( const CMatrix & );
	// multiply a CMatrix with a value modify this CMatrix					   
	void operator*=( const double );

	CMatrix operator/( const double );	// divide the CMatrix by a value;	   

	// divide the CMatrix by a value modify the this CMatrix					   
	void operator/=( const double );

	CMatrix operator^( const int );		// take a power of the CMatrix

	// methods of the CMatrix class
	
	const CMatrix &convToIdentity(); // convert CMatrix to identity CMatrix of the same size	  
	const CMatrix &convToInvDiagonal(); // convert CMatrix to inverse diagonal				  

	// get the transpose of a CMatrix
	CMatrix &getTranspose();				// 
    // calculate the LUD of the CMatrix
	void LUBKS( int phy_size, int *outvect, double *output );
	// calculate the LUD of the CMatrix
	int LUD( int phy_size, int *outvect, int output );
	// get the inverse of the CMatrix and return the CMatrix.
	CMatrix &getInverse();										 
	// extract a subCMatrix from a CMatrix
	CMatrix getSubCMatrix( const int startRow, const int startCol,
							const int rowSize, const int colSize  ) const;	   

	CMatrix &deleteRow( const int r );	// Delete a row from the CMatrix		    
	CMatrix &deleteCol( const int c );	// Delete a coloumn from the CMatrix	    
	// inserts the row CMatrix to the given row shifting other rows down
	CMatrix &insertRow( const int r, const CMatrix &rVector );  					
	// inserts the coloumn CMatrix to the given coloumn shifting other coloumns right
	CMatrix &insertCol( const int c, const CMatrix &cVector ); 				
	// interchange rows in the CMatrix ( r1 <-> r2 )
	CMatrix &interchangeRows( const int r1, const int r2 );	 				
	// interchange columns in the CMatrix ( c1 <-> c2 )
	CMatrix &interchangeCols( const int c1, const int c2 );	 					

	// add the right CMatrix on top of this
	CMatrix &attachTop( const CMatrix & );					 
	// add the right CMatrix under this
	CMatrix &attachBottom( const CMatrix & );				 
	// add the right CMatrix to Left of this
	CMatrix &attachLeft( const CMatrix & );					 
	// add the right CMatrix to Right of this
	CMatrix &attachRight( const CMatrix & );				


	static int getCMatrixCount();		// CMatrix's instantiated  
		 
public:
	int rows;	// number of rows
	int cols;	// number of coloumns
	double *ptr;		// pointer to the first element of CMatrix
	static int CMatrixCount;	// # of CMatrix's instantiated
	
};
#endif // !defined(AFX_CMatrix_H__E6551543_A986_4403_84EA_8B621BDBC795__INCLUDED_)
