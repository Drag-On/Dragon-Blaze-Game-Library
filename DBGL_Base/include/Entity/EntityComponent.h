//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ENTITYCOMPONENT_H_
#define ENTITYCOMPONENT_H_

#include <typeindex>
#include <typeinfo>
#include <map>

namespace dbgl
{
    class Entity;

    /**
     * @brief Base class for all components
     */
    class EntityComponent
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~EntityComponent(){};
	    /**
	     * @brief Updates this component
	     * @param deltaTime Time since last update
	     */
	    virtual void update(std::map<std::type_index, EntityComponent*> const& components, double deltaTime) = 0;
	protected:
	    friend class Entity;
    };
}

#endif /* ENTITYCOMPONENT_H_ */
