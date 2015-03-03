//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_SHAPE_HYPERSPHERE_H_
#define INCLUDE_DBGL_CORE_SHAPE_HYPERSPHERE_H_

/*
 * NOTE: This includes both the declaration and the implementation of the template class. In order to resolve
 *       dependency-issues they have been split into separate files that can be included separately.
 */

#include "HyperSphere.dec"

#include "DBGL/Core/Math/Vector.h"
#include "HyperPlane.dec"
#include "HyperRectangle.dec"

#include "HyperSphere.imp"

#endif /* INCLUDE_DBGL_CORE_SHAPE_HYPERSPHERE_H_ */
