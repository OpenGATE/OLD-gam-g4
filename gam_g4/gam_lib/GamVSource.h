/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamVSource_h
#define GamVSource_h

#include <pybind11/stl.h>
#include "G4Event.hh"
#include "G4Threading.hh"
#include "GamHelpers.h"

namespace py = pybind11;

class GamVSource {

public:

    virtual ~GamVSource() { }

    // Used to clear some allocated data during a thread
    // (see for example GamGenericSource)
    virtual void CleanInThread() {}

    // Called at initialisation
    virtual void InitializeUserInfo(py::dict &user_info) {
        // FIXME replace by DicStr etc (check)
        fName = py::str(user_info["name"]);
        fStartTime = py::float_(user_info["start_time"]);
        fEndTime = py::float_(user_info["end_time"]);
    }

    virtual void PrepareNextRun() {
        fEventsPerRun.push_back(0);
    }

    virtual double PrepareNextTime(double current_simulation_time) {
        Fatal("PrepareNextTime must be overloaded");
        return current_simulation_time;
    }

    virtual void GeneratePrimaries(G4Event */*event*/, double /*time*/) {
        fEventsPerRun.back()++; // FIXME not really used yet
        //Fatal("GeneratePrimaries must be overloaded");
    }

    std::vector<int> fEventsPerRun;
    std::string fName;
    double fStartTime;
    double fEndTime;
};

#endif // GamVSource_h
