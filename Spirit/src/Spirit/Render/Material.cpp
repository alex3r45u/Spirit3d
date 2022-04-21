#include "sppch.h"
#include "Material.h"

const std::shared_ptr<Spirit::Render::Texture2d> Spirit::Render::UserMaterial::GetAmbientTexture()
{
    return std::shared_ptr<Texture2d>();
}

const std::shared_ptr<Spirit::Render::Texture2d> Spirit::Render::UserMaterial::GetDeffuseTexture()
{
    return std::shared_ptr<Texture2d>();
}

const std::shared_ptr<Spirit::Render::Texture2d> Spirit::Render::UserMaterial::GetSpecularTexture()
{
    return std::shared_ptr<Texture2d>();
}

const std::shared_ptr<Spirit::Render::Texture2d> Spirit::Render::GeneratedMaterial::GetAmbientTexture()
{
    return std::shared_ptr<Texture2d>();
}

const std::shared_ptr<Spirit::Render::Texture2d> Spirit::Render::GeneratedMaterial::GetDeffuseTexture()
{
    return std::shared_ptr<Texture2d>();
}

const std::shared_ptr<Spirit::Render::Texture2d> Spirit::Render::GeneratedMaterial::GetSpecularTexture()
{
    return std::shared_ptr<Texture2d>();
}


void Spirit::Render::Material::SetUniforms(const std::shared_ptr<Shader>& shader)
{
    glm::vec3 ambient = GetAmbient();
    glm::vec3 deffuse = GetDeffuse();
    glm::vec3 specular = GetSpecular();
    shader->SetFloat3("material.ambient", ambient.x, ambient.y, ambient.z);
    shader->SetFloat3("material.deffuse", deffuse.x, deffuse.y, deffuse.z);
    shader->SetFloat3("material.specular", specular.x, specular.y, specular.z);

    //TODO textures
}
