#pragma once

#include "vec.hpp"

class m_Mat3;

class m_Mat4
{
public:
    m_Mat4() {}
    ~m_Mat4() {}

    m_Mat4  operator*( const m_Mat4& m ) const;
    m_Mat4& operator*=( const m_Mat4& m );
    m_Vec3  operator*( const m_Vec3& v ) const;
    void Transpose();
	void Inverse();

    float& operator[]( int i );
    float  operator[]( int i )const;

    void Identity();

    void Translate( const m_Vec3& v );
    void Scale( const m_Vec3& v );
    void Scale( float s );

    void RotateX( float a );
    void RotateY( float a );
    void RotateZ( float a );
    void PerspectiveProjection( float aspect, float fov_y, float z_near, float z_far);
    void AxonometricProjection( float scale_x, float scale_y, float z_near, float z_far );

    /*True matrix - this
    0   1   2   3
    4   5   6   7
    8   9   10  11
	12  13  14  15
    */

    /*OpenGL matrix
    0   4   8   12
    1   5   9   13
    2   6   10  14
    3   7   11  15
    */

	float value[16];
};

m_Vec3 operator*( const m_Vec3& v, const m_Mat4& m );

class m_Mat3
{
public:
    m_Mat3() {}
    ~m_Mat3() {}

    m_Mat3  operator*( const m_Mat3& m ) const;
    m_Mat3& operator*=( const m_Mat3& m );
    m_Vec3  operator*( const m_Vec3& v ) const;
    void    Transpose();

    float& operator[]( int i );
    float  operator[]( int i )const;

    void Identity();

    void Scale( const m_Vec3& v );
    void Scale( float s );

    void RotateX( float a );
    void RotateY( float a );
    void RotateZ( float a );

    /*True matrix - this
    0   1   2   3
    4   5   6   7
    8   9   10  11
	12  13  14  15
    */


	float value[12];
};

m_Vec3 operator*( const m_Vec3& v, const m_Mat3& m );
