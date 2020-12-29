/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamTest1Source_h
#define GamTest1Source_h

#include <pybind11/stl.h>
#include "G4ParticleGun.hh"
#include "GamVSource.h"

namespace py = pybind11;

class GamTest1Source : public GamVSource {

public:

    virtual void initialize(py::dict &user_info);

    virtual double PrepareNextTime(double current_simulation_time);

    virtual void GeneratePrimaries(G4Event *event, double time);

    int n;

protected:
    G4ParticleGun *m_particle_gun;
    int max_n;
    double diameter;
    double radius;
    double activity;
    G4ThreeVector position;
    G4ThreeVector translation;
};

#endif // GamTest1Source_h