//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef EVENT_H_
#define EVENT_H_

#include <set>
#include <functional>
#include <memory>
#include <algorithm>

namespace dbgl
{
    /**
     * @brief Implements a generic event system
     * @details DelegateType needs to be of type std::function<void(EventArgs const&)>
     */
    template <class DelegateType, typename EventArgs> class Event
    {
	public:
	    using DelegatePtr = std::shared_ptr<DelegateType>;

	    /**
	     * Default constructor
	     */
	    Event();
	    /**
	     * @brief Move-Constructor
	     * @param other
	     */
	    Event(Event&& other);
	    /**
	     * @brief Destructor
	     */
	    virtual ~Event();
	    /**
	     * @brief Invokes all connected listeners
	     * @param Parameters passed to the listeners
	     */
	    void fire(EventArgs const& args);
	    /**
	     * @brief Adds a new event listener
	     * @param listener Listener to add
	     * @return The pointer that can be used to remove it again
	     */
	    DelegatePtr addListener(DelegateType listener);
	    /**
	     * @brief Removes an event listener
	     * @param listener Listener to remove
	     * @return True in case the listener has been remove, otherwise false
	     */
	    bool removeListener(DelegatePtr listener);
	    /**
	     * @return True in case at least one listener is registered, otherwise false
	     */
	    bool hasListener();
	private:
	    std::set<DelegatePtr> m_delegates;
    };
}

#include "Event.imp"

#endif /* EVENT_H_ */
