#pragma once
#include "vec.hpp"

class m_Plane3
{
public:
	m_Vec3 normal; // Must be normalized
	float dist; // Distance from center

	/* For point on plane  P * normal + dist == 0
	 * For point ahead plane  P * normal + dist > 0
	 * For point behind plane  P * normal + dist < 0
	*/

public:
	m_Plane3(){}
	m_Plane3( const m_Vec3& in_normal, float in_dist );

	bool IsPointAheadPlane( const m_Vec3& point ) const;
	bool IsPointBehindPlane( const m_Vec3& point ) const;

	// TODO - add other useful methods - rotation, matrix transformations, etc.
};

inline m_Plane3::m_Plane3( const m_Vec3& in_normal, const float in_dist )
	: normal( in_normal ), dist( in_dist )
{}

inline bool m_Plane3::IsPointAheadPlane( const m_Vec3& point ) const
{
	return point * normal + dist > 0.0f;
}

inline bool m_Plane3::IsPointBehindPlane( const m_Vec3& point ) const
{
	return point * normal + dist < 0.0f;
}
