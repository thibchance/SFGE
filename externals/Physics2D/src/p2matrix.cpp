/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <p2matrix.h>
#include <cmath>

p2Mat22::p2Mat22()
{
}

p2Mat22::p2Mat22(p2Vec2 r1, p2Vec2 r2): r1(r1), r2(r2)
{
}

p2Mat22 p2Mat22::operator+(p2Mat22 m1)
{
	return p2Mat22(r1 + m1.r1, r2 + m1.r2);
}

p2Mat22 p2Mat22::operator-(p2Mat22 m1)
{
	return p2Mat22(r1 - m1.r1, r2 - m1.r2);
}

p2Mat22 p2Mat22::operator*(p2Mat22 m1)
{
	return p2Mat22(p2Vec2(r1.x*m1.r1.x + r2.x*m1.r1.y, r1.y*m1.r1.x + r2.y * m1.r1.y),
		p2Vec2(r1.x*m1.r1.x + r2.x*m1.r1.y, r1.y*m1.r1.x + r2.y * m1.r1.y));
}

p2Vec2 p2Mat22::operator*(p2Vec2 v)
{
	return p2Vec2(r1.x*v.x + r2.x*v.y, r1.y*v.x + r2.y * v.y);
}

p2Mat22 p2Mat22::operator*(float f)
{
	return p2Mat22(r1*f,r2*f);
}

p2Mat22 p2Mat22::operator/(float f)
{
	return p2Mat22(r1/f,r2/f);
}

p2Mat22 p2Mat22::RotationMatix(float angle)
{
	return p2Mat22(p2Vec2(cos(angle), sin(angle)),
		p2Vec2(-sin(angle), cos(angle)));
}

p2Mat22 p2Mat22::Invert()
{
	if (GetDeterminant() != 0)
	{
		return p2Mat22(p2Vec2((1 / GetDeterminant())*r2.y, (1 / GetDeterminant())*-r2.x),
			p2Vec2((1 / GetDeterminant())*-r1.y, (1 / GetDeterminant())*r1.x));
	}
	
}

float p2Mat22::GetDeterminant()
{
	float Determinant = (r1.x*r2.y) - (r2.x*r1.y);
	return Determinant;
}

p2Mat33::p2Mat33()
{
}

p2Mat33::p2Mat33(p2Vec3 r1, p2Vec3 r2, p2Vec3 r3): r1(r1),r2(r2),r3(r3)
{
}

p2Mat33 p2Mat33::operator+(p2Mat33 m1)
{
	return p2Mat33(r1 + m1.r1, r2 + m1.r2, r3+m1.r3);
}

p2Mat33 p2Mat33::operator-(p2Mat33 m1)
{
	return p2Mat33(r1 - m1.r1, r2 - m1.r2, r3 - m1.r3);
}

p2Mat33 p2Mat33::operator*(p2Mat33 m1)
{
	return p2Mat33(p2Vec3(r1.x*m1.r1.x + r2.x*m1.r1.y + r3.x*m1.r1.z,
		r1.y*m1.r1.x + r2.y * m1.r1.y + r3.y*m1.r1.z,
		r1.z*m1.r1.x + r2.z*m1.r1.y + r3.z*m1.r1.z),
		p2Vec3(r1.x*m1.r1.x + r2.x*m1.r1.y + r3.x*m1.r1.z, r1.y*m1.r1.x + r2.y * m1.r1.y + r3.y*m1.r1.z,
			r1.z*m1.r1.x + r2.z*m1.r1.y + r3.z*m1.r1.z),
		p2Vec3(r1.x*m1.r1.x + r2.x*m1.r1.y + r3.x*m1.r1.z, r1.y*m1.r1.x + r2.y * m1.r1.y + r3.y*m1.r1.z,
				r1.z*m1.r1.x + r2.z*m1.r1.y + r3.z*m1.r1.z));
}

p2Vec3 p2Mat33::operator*(p2Vec3 v)
{
	return p2Vec3(r1.x*v.x + r2.x*v.y +r3.x*v.z, r1.y*v.x + r2.y * v.y+ r3.y*v.z, 
		r1.z*v.x+r2.z*v.y+r3.z*v.z);
}

p2Mat33 p2Mat33::operator*(float f)
{
	return p2Mat33(r1*f,r2*f,r3*f);
}

p2Mat33 p2Mat33::operator/(float f)
{
	return p2Mat33(r1/f, r2/f, r3/f);
}

p2Mat33 p2Mat33::Invert()
{
	if (GetDeterminant() != 0)
	{
		return p2Mat33();
	}
	
}

float p2Mat33::GetDeterminant()
{
	//methode de sarrus
	float Determinant = (r1.x*r2.y*r3.z+r1.y*r2.z*r3.x+r1.z*r2.x*r3.y)-
		(r3.x*r2.y*r1.z+r3.y*r2.z*r1.x+r3.z*r2.x*r1.y);
	return Determinant;
}
