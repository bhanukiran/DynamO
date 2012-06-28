/*  dynamo:- Event driven molecular dynamics simulator 
    http://www.dynamomd.org
    Copyright (C) 2011  Marcus N Campbell Bannerman <m.bannerman@gmail.com>

    This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 3 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

namespace dynamo {
  class ShapeFunc {
  public:
    virtual void stream(const double& dt) = 0;

    virtual double F_zeroDeriv() const = 0;

    virtual double F_firstDeriv() const = 0;

    virtual double F_firstDeriv_max() const = 0;

    virtual double F_secondDeriv() const = 0;

    virtual double F_secondDeriv_max() const = 0;

    virtual bool test_root() const = 0;
  };
}