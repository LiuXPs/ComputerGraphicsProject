/*
========================================================================================================================

* This file is part of Draw3D
*
* Copyright (C) 2018-2024 Xupeng Liu.
*
* Draw3D is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
* Draw3D is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
* the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with Draw3D.
* If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================
*/


#ifndef _MYVECTOR3D_H_
#define _MYVECTOR3D_H_

class MyVector3D
{
public:
	double vx = 0.0;
	double vy = 0.0;
	double vz = 0.0;
	double vs = 1.0;

	MyVector3D& operator=(const MyVector3D& vector)
	{
		this->vx = vector.vx;
		this->vy = vector.vy;
		this->vz = vector.vz;
		this->vs = vector.vs;

		return *this;
	}

	bool operator==(const MyVector3D& vector)
	{
		if (this == &vector)
		{
			return true;
		}
		else if ((this->vx == vector.vx) && (this->vy == vector.vy) && (this->vz == vector.vz) && (this->vs == vector.vs))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:

};

#endif // !_MYVECTOR3D_H_