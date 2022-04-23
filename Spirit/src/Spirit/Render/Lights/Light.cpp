#include "sppch.h"
#include "Light.h"

int Spirit::Render::Light::s_NoDirectionalLights = 0;
int Spirit::Render::Light::s_NoSpotLights = 0;
int Spirit::Render::Light::s_NoPointLights = 0;

void Spirit::Render::Light::ResetNoLights()
{
	s_NoDirectionalLights = 0;
	s_NoPointLights = 0;
	s_NoSpotLights = 0;
}
