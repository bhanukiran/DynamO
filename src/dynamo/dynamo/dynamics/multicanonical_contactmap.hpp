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
#include <dynamo/dynamics/newtonian.hpp>
#include <dynamo/interactions/captures.hpp>
#include <tr1/unordered_map>

namespace dynamo {
  /*! \brief A Dynamics which implements Newtonian dynamics, but with
    a deformed energy landscape set controlled through an interaction
    contact map.
   */
  class DynNewtonianMCCMap: public DynNewtonian
  {
    typedef std::tr1::unordered_map<detail::CaptureMapKey, double,  detail::CaptureMapKeyHash> WType;
    WType _W;

    std::string _interaction_name;
    std::tr1::shared_ptr<ICapture> _interaction;
  public:
    DynNewtonianMCCMap(dynamo::Simulation* tmp, const magnet::xml::Node&);

    virtual PairEventData SphereWellEvent(const IntEvent&, const double&, const double&, size_t) const;
    virtual NEventData multibdyWellEvent(const IDRange&, const IDRange&, const double&, const double&, EEventType&) const;
    virtual void initialise();
    virtual void swapSystem(Dynamics& oDynamics);

    double W(const detail::CaptureMap& map) const
    {
      WType::const_iterator it = _W.find(map);
      return (it == _W.end()) ? 0 : it->second;
    }
  protected:
    virtual void outputXML(magnet::xml::XmlStream& ) const;
  };
}
