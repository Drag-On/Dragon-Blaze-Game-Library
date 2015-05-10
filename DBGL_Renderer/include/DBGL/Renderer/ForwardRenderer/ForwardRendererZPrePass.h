//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef DBGL_FORWARDRENDERERZPREPASS_H
#define DBGL_FORWARDRENDERERZPREPASS_H

#include "ForwardRenderer.h"

namespace dbgl
{
    class ForwardRendererZPrePass : public ForwardRenderer
    {
    public:
        /**
         * @brief Constructor
         */
        ForwardRendererZPrePass();
        /**
         * @brief Destructor
         */
        virtual ~ForwardRendererZPrePass();
        virtual void render(IRenderContext* rc);

    private:
        void renderWithZPrePass(IRenderContext* rc);

        IShaderProgram* m_pZPrePassShader;
        IShaderProgram::UniformHandle m_prePassMVPHandle;
    };
}

#endif //DBGL_FORWARDRENDERERZPREPASS_H
