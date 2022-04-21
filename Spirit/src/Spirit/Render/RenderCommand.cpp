#include "sppch.h"
#include "RenderCommand.h"
#include "Spirit/Platform/OpenGl/OpenGlRenderAPI.h"

Spirit::Render::RenderAPI* Spirit::Render::RenderCommand::s_RendererAPI = new OpenGlRenderAPI;