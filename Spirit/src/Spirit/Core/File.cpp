#include "sppch.h"
#include "File.h"
#include "Spirit/Application.h"
std::string Spirit::File::Read(const FileRegion& region, std::filesystem::path path)
{
#ifdef SP_BUILD

#endif
#ifndef SP_BUILD
	std::string str = Application::Get().GetProject()->GetSettings().AssetPath.string() + "\\" + path.string();
	SP_CORE_INFO(str);
	std::filesystem::path p = std::filesystem::path(str);
	std::string result;
	std::ifstream in(p, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	return result;

#endif
}
