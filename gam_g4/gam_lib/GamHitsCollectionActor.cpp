/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */


#include <iostream>
#include "GamHitsCollectionActor.h"
#include "GamDictHelpers.h"
#include "GamHitsCollectionManager.h"


G4Mutex GamHitsCollectionActorMutex = G4MUTEX_INITIALIZER;

GamHitsCollectionActor::GamHitsCollectionActor(py::dict &user_info)
    : GamVActor(user_info) {
    fActions.insert("StartSimulationAction");
    fActions.insert("EndSimulationAction");
    fActions.insert("BeginOfRunAction");
    fActions.insert("EndOfRunAction");
    fActions.insert("SteppingAction");
    fOutputFilename = DictStr(user_info, "output");
    fHitsCollectionName = DictStr(user_info, "name");
    fUserHitAttributeNames = DictVecStr(user_info, "attributes");
    fHits = nullptr;
}

GamHitsCollectionActor::~GamHitsCollectionActor() {
}

// Called when the simulation start
void GamHitsCollectionActor::StartSimulationAction() {
    DDD("StartSimulationAction");
    fHits = GamHitsCollectionManager::GetInstance()->NewHitsCollection(fHitsCollectionName);
    fHits->SetFilename(fOutputFilename);
    fHits->InitializeHitAttributes(fUserHitAttributeNames);
    fHits->CreateRootTupleForMaster();
    DDD(fHits->GetTupleId());
}

// Called when the simulation end
void GamHitsCollectionActor::EndSimulationAction() {
    fHits->Write(); // FIXME option to not write to disk
    fHits->Close();
}

// Called every time a Run starts
void GamHitsCollectionActor::BeginOfRunAction(const G4Run *) {
    DDD("BeginOfRunAction");
    fHits->CreateRootTupleForWorker();
    DDD("BeginOfRunAction DONE ");
}

// Called every time a Run ends
void GamHitsCollectionActor::EndOfRunAction(const G4Run *) {
    G4AutoLock mutex(&GamHitsCollectionActorMutex);
    DDD("EndOfRunAction");
    fHits->FillToRoot();
    // Only required when MT
    DDD("Write"); // PROBABLY ONLY AFTER ALL FILL OF ALL THREADS ?!!
    if (G4Threading::IsMultithreadedApplication())
        fHits->Write();
}

void GamHitsCollectionActor::BeginOfEventAction(const G4Event *) {
    //DDD("GamHitsCollectionActor::BeginOfEventAction");
}

void GamHitsCollectionActor::EndOfEventAction(const G4Event *) {
    // Cannot manage to Write to Root at EndOfEventAction in MT mode
}

// Called every time a Track starts
void GamHitsCollectionActor::PreUserTrackingAction(const G4Track *) {
}

// Called every time a batch of step must be processed
void GamHitsCollectionActor::SteppingAction(G4Step *step, G4TouchableHistory *touchable) {
    fHits->ProcessHits(step, touchable);
}
