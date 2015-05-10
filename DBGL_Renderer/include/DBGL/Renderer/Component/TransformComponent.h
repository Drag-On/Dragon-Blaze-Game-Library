//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_COMPONENT_TRANSFORMCOMPONENT_H_
#define INCLUDE_DBGL_RENDERER_COMPONENT_TRANSFORMCOMPONENT_H_

#include "IGameComponent.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Math/Matrix3x3.h"
#include "DBGL/Core/Math/Quaternion.h"

namespace dbgl
{
    /**
     * @brief Component holding all the transformation data
     */
    class TransformComponent : public IGameComponent
    {
    public:
        /**
         * @brief Constructor
         */
        TransformComponent(Vec3f const& pos = {0, 0, 0}, Vec3f const& scale = {1, 1, 1}, QuatF const& rot =
        QuatF()); // TODO: Only uniform scale?
        /**
         * @copydoc IGameComponent::clone()
         */
        virtual IGameComponent* clone() const;
        /**
         * @copydoc IGameComponent::update()
         */
        virtual void update();
        /**
         * @brief World position
         * @return Reference to the world position vector
         */
        Vec3f& position();
        /**
         * @brief World position
         * @return Constant reference to the world position vector
         */
        Vec3f const& position() const;
        /**
         * @brief Scale
         * @return Reference to the scale vector
         */
        Vec3f& scale();
        /**
         * @brief Scale
         * @return Constant reference to the scale vector
         */
        Vec3f const& scale() const;
        /**
         * @brief Rotation
         * @return Reference to the rotation quaternion
         */
        QuatF& rotation();
        /**
         * @brief Rotation
         * @return Constant reference to the rotation quaternion
         */
        QuatF const& rotation() const;
        /**
         * @brief Current model matrix
         * @return Constant reference to the current model matrix
         * @note The underlying matrix will only be updated on each call of update()
         */
        Mat4f const& modelMat() const;
        /**
         * @brief Checks if the entity can be transformed
         * @return True in case the entity is static, i.e. can not be transformed. Otherwise false.
         */
        bool isStatic() const;
    private:
        Vec3f m_pos;
        Vec3f m_scale;
        QuatF m_rot;
        Mat4f m_modelMat;
    };
}

#endif /* INCLUDE_DBGL_RENDERER_COMPONENT_TRANSFORMCOMPONENT_H_ */
