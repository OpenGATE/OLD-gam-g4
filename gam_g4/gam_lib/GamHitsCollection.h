/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamHitsCollection_h
#define GamHitsCollection_h

#include <pybind11/stl.h>
#include "G4TouchableHistory.hh"
#include "G4NtupleBookingManager.hh"
#include "GamHelpers.h"
#include "GamVHitAttribute.h"
#include "GamHit.h"


class GamHitsCollection : public G4VHitsCollection {
public:

    GamHitsCollection(std::string collName);

    virtual ~GamHitsCollection();

    bool StartInitialization();

    void InitializeHitAttribute(std::string name);

    void FinishInitialization();

    void Write();

    void Close();

    void SetFilename(std::string filename);

    std::string GetFilename() const { return fFilename; }
    std::string GetName() const { return fHitsCollectionName; }
    std::string GetTitle() const { return fHitsCollectionTitle; }

    void ProcessHits(G4Step *step, G4TouchableHistory *touchable);

    // FIXME DEBUG
    int fNHits;



    std::vector<GamVHitAttribute *> fHitAttributes;

protected:
    std::string fFilename;
    std::string fHitsCollectionName;
    std::string fHitsCollectionTitle;
    G4int fRootTupleId; // FIXME change name
    std::map<std::string, GamVHitAttribute *> fHitAttributeMap;
};

#endif // GamHitsCollection_h
