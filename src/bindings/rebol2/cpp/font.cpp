/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "bindings/rebol2/cpp/font.h"

bool operator ==(FaceFont const& rOp1P, FaceFont const& rOp2P)
{
    return isFontEqual(&rOp1P, &rOp2P);
}

bool operator !=(FaceFont const& rOp1P, FaceFont const& rOp2P)
{ return !(rOp1P == rOp2P); }
