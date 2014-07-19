//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Camera.h"

namespace dbgl
{
    /**
     * @brief Holds data about the environment that are relevant to the render process.
     */
    class Environment
    {
	public:
	    /**
	     * @brief Constructor
	     * @param cam Camera to use
	     */
	    Environment(Camera& cam);
	    /**
	     * @brief Retrieve the camera
	     * @return Current camera
	     */
	    Camera* getCamera() const;
	private:
	    Camera* m_pCamera;
    };
}

#endif /* ENVIRONMENT_H_ */
