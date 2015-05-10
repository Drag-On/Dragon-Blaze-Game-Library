//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef DBGL_CAMERACOMPONENT_H
#define DBGL_CAMERACOMPONENT_H

#include "DBGL/Platform/Window/IWindow.h"
#include "DBGL/Core/Math/Matrix4x4.h"
#include "DBGL/Renderer/Culling/ICamera.h"
#include "IGameComponent.h"
#include "TransformComponent.h"

namespace dbgl
{
    class CameraComponent : public IGameComponent, public ICamera
    {
    public:
        /**
         * @brief Constructor
         * @param transform Pointer to the entity's transform component
         * @param fov Field of view
         * @param near Near plane
         * @param far Far plane
         * @param wnd Window (for aspect ratio)
         */
        CameraComponent(TransformComponent* transform, float fov, unsigned int near, unsigned int far, IWindow* wnd);
        /**
         * @brief Destructor
         */
        virtual ~CameraComponent() = default;
        /**
         * @copydoc IGameComponent::clone()
         */
        virtual IGameComponent* clone() const;
        /**
         * @copydoc IGameComponent::update()
         */
        virtual void update();
        /**
         * @brief Retrieves the camera's view matrix
         * @return Camera view matrix
         */
        virtual Mat4f const& getViewMatrix() const;
        /**
         * @brief Retrieves the camera's projection matrix
         * @return Camera projection matrix
         */
        virtual Mat4f const& getProjectionMatrix() const;
        /**
         * @brief Retrieves the camera position in world space
         * @return Cam position
         */
        virtual Vec3f const& getPosition() const;
        /**
         * @brief Retrieves the camera's direction vector in world space
         * @return Cam direction
         */
        virtual Vec3f const& getDirection() const;
        /**
         * @brief Retrieves the camera's up vector in world space
         * @return Cam up direction
         */
        virtual Vec3f const& getUp() const;
        /**
         * @brief Retrieves the camera's distance to the near plane
         * @return Near plane
         */
        virtual float getNear() const;
        /**
         * @brief Retrieves the camera's distance to the far plane
         * @return Far plane
         */
        virtual float getFar() const;
        /**
         * @brief Retrieves the camera's field of view
         * @return Field of view
         */
        virtual float getFieldOfView() const;
        /**
         * @brief Retrieves the camera's ratio
         * @return Ratio
         */
        virtual float getRatio() const;
    private:
        Mat4f m_view;
        Mat4f m_projection;
        Vec3f m_dir;
        Vec3f m_up;
        float m_fov;
        unsigned int m_near;
        unsigned int m_far;
        IWindow* m_pWnd;
        TransformComponent* m_pTransform;
    };
}

#endif //DBGL_CAMERACOMPONENT_H
