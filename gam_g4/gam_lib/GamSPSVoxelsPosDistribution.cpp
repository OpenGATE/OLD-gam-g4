/* --------------------------------------------------
   Copyright (C): OpenGate Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <Randomize.hh>
#include "GamSPSVoxelsPosDistribution.h"
#include "GamHelpers.h"

GamSPSVoxelsPosDistribution::GamSPSVoxelsPosDistribution() {
    // Create the image pointer
    // The size and allocation will be performed on the py side
    cpp_image = ImageType::New();
}


void GamSPSVoxelsPosDistribution::SetCumulativeDistributionFunction(VD vz, VD2 vy, VD3 vx) {
    // Warning : this is a COPY of all cumulative distribution functions
    fCDFZ = vz;
    fCDFY = vy;
    fCDFX = vx;
}

G4ThreeVector GamSPSVoxelsPosDistribution::VGenerateOne() {
    // Get Cumulative Distribution Function for Z
    int i = 0;
    auto p = G4UniformRand();
    while (p > fCDFZ[i]) i++;

    // Get Cumulative Distribution Function for Y, knowing Z
    int j = 0;
    p = G4UniformRand();
    while (p > fCDFY[i][j]) j++;

    // Get Cumulative Distribution Function for X, knowing X and Y
    int k = 0;
    p = G4UniformRand();
    while (p > fCDFX[i][j][k]) k++;

    // get random position within the voxel
    itk::ContinuousIndex<double, 3> index;
    index[0] = k + G4UniformRand();
    index[1] = j + G4UniformRand();
    index[2] = i + G4UniformRand();

    // convert to physical coordinate
    itk::Point<double, 3> point;
    cpp_image->TransformContinuousIndexToPhysicalPoint(index, point);
    G4ThreeVector position(point[0], point[1], point[2]);

    return position;
}

