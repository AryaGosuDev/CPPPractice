#ifndef __VEC3_INCLUDED__
#define __VEC3_INCLUDED__

#define Epsilon 1e-6

struct Vec3 {
	inline Vec3()                               { x = 0; y = 0; z = 0; }
	inline Vec3( double a, double b, double c ) { x = a; y = b; z = c; }
	double x;
	double y;
	double z;
};


inline double LengthSquared( const Vec3 &A ){
	return A.x * A.x + A.y * A.y + A.z * A.z;
}

inline double Length( const Vec3 &A ){
	return sqrt( LengthSquared( A ) );
}

inline Vec3 operator+( const Vec3 &A, const Vec3 &B ){
	return Vec3( A.x + B.x, A.y + B.y, A.z + B.z );
}

inline Vec3 operator-( const Vec3 &A, const Vec3 &B ){
	return Vec3( A.x - B.x, A.y - B.y, A.z - B.z );
}

inline Vec3 operator-( const Vec3 &A ) {  // Unary minus.
	return Vec3( -A.x, -A.y, -A.z );
}

inline Vec3 operator*( double a, const Vec3 &A ){
	return Vec3( a * A.x, a * A.y, a * A.z );
}

inline Vec3 operator*( const Vec3 &A, double a ){
	return Vec3( a * A.x, a * A.y, a * A.z );
}

inline double operator*( const Vec3 &A, const Vec3 &B )  // Inner product.
	{
	return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
	}

inline Vec3 operator/( const Vec3 &A, double c )
	{
	return Vec3( A.x / c, A.y / c, A.z / c );
	}

inline Vec3 operator^( const Vec3 &A, const Vec3 &B ) // Cross product.
	{
	return Vec3( 
		A.y * B.z - A.z * B.y,
		A.z * B.x - A.x * B.z,
		A.x * B.y - A.y * B.x
		);
	}

inline Vec3& operator+=( Vec3 &A, const Vec3 &B )
	{
	A.x += B.x;
	A.y += B.y;
	A.z += B.z;
	return A;
	}

inline Vec3& operator-=( Vec3 &A, const Vec3 &B )
	{
	A.x -= B.x;
	A.y -= B.y;
	A.z -= B.z;
	return A;
	}

inline Vec3 &operator*=( Vec3 &A, double a )
	{
	A.x *= a;
	A.y *= a;
	A.z *= a;
	return A;
	}

inline Vec3& operator/=( Vec3 &A, double a )
	{
	A.x /= a;
	A.y /= a;
	A.z /= a;
	return A;
	}

inline Vec3 operator/( const Vec3 &A, const Vec3 &B )  // Remove component parallel to B.
	{
	double x = LengthSquared( B );
	if( x > 0.0 ) return A - (( A * B ) / x) * B;
	return A;
	}

inline std::ostream &operator<<( std::ostream &out, const Vec3 &A )
{
	out << "( " << A.x << ", " << A.y << ", " << A.z << " ) ";
	return out;
}

inline bool operator ==( const Vec3 & _a , const Vec3 & _b ) {
	//return ( _a.x == _b.x && _a.y == _b.y && _a.z == _b.z ) ;
	//return ( abs(_a.x - _b.x) <= Epsilon && abs (_a.y - _b.y ) <= Epsilon && abs(_a.z - _b.z) <= Epsilon ) ;
	bool here = ( abs(_a.x - _b.x) <= Epsilon && abs (_a.y - _b.y ) <= Epsilon && abs(_a.z - _b.z) <= Epsilon ) ;
	return here ;
}

inline bool operator !=( const Vec3 & _a, const Vec3 & _b ) {
	return ( _a.x != _b.x && _a.y != _b.y && _a.z != _b.z ) ;
}

inline bool relativeClose ( const Vec3 & _a , const Vec3 & _b, double threshhold = Epsilon ) {
	return ( abs( _a.x - _b.x ) <= threshhold && abs( _a.y - _b.y ) <= threshhold && abs( _a.z - _b.z ) <= threshhold ) ;
}

inline Vec3 Unit( const Vec3 &A )
	{
	double d = LengthSquared( A );
	return d > 0.0 ? A / sqrt(d) : Vec3(0,0,0);
	}

inline Vec3 Unit( double x, double y, double z )
	{
	double d = (x * x) + (y * y) + (z * z);
	return d > 0.0 ? Vec3(x,y,z) / sqrt(d) : Vec3(0,0,0);
	}

inline Vec3 OrthogonalTo( const Vec3 &A )  // Return a non-zero vector orthogonal to A.
	{
	if( A.x == 0 ) return Vec3( 1, 0, 0 );
	return Vec3( A.y, -A.x, 0 );
	}

// Euclidean distance from A to B.
inline double dist( const Vec3 &A, const Vec3 &B ) 
	{ 
	return Length( A - B ); 
	}

// find the area of a triangle given the 3 vertices of the triangle
inline double Area ( const Vec3 &A, const Vec3 &B, const Vec3 &C ) {
	return (Length ( ( B - A ) ^ ( C - A ) ) / 2.0);  
} 

inline bool operator<( const Vec3 & _A, const Vec3 & _B ) {
	return (Length ( _A ) < Length ( _B )) && (_A != _B)  ;
}

inline double coTangent ( const Vec3 &A, const Vec3 &B, const Vec3 &C ) {
	return ((( A - B ) * ( C - B )) / (Length ( (A - B ) ^ ( C - B ) ))) ;
}

#endif


