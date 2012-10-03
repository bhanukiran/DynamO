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

#include <vector>
#include <dynamo/outputplugins/tickerproperty/ticker.hpp>
#include <magnet/math/vector.hpp>
#include <magnet/math/histogram.hpp>

namespace dynamo {
  class OPVelDist: public OPTicker
  {
  public:
    OPVelDist(const dynamo::Simulation*, const magnet::xml::Node&);

    virtual void initialise();

    virtual void stream(double) {}

    virtual void ticker();
  
    virtual void output(magnet::xml::XmlStream&);

    void operator<<(const magnet::xml::Node&);

  protected:
    double binWidth;
    std::vector<magnet::math::Histogram<> > data[NDIM];
  };
}
