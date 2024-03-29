#pragma once
#include "Panel.h"
#include <filesystem>
#include "Spirit/Render/Texture.h"
#include "Spirit/Core/File.h"

namespace Spirit {
	class FileExplorerPanel : public Panel {
	public:
		FileExplorerPanel();
		FileExplorerPanel(const std::shared_ptr<Scene>& scene, std::filesystem::path directory);

		virtual void ImGuiRender() override;
		void SetDirectory(std::filesystem::path directory);
	private:
		void DrawDirectory(std::filesystem::path directory);
		void AddFile();
		void Inspect(std::filesystem::path directory);
		void Init();
	private:
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_RootDirectory;
		std::filesystem::path m_SelectedFile;

		std::shared_ptr<Render::Texture> m_FileIcon;
		std::shared_ptr<Render::Texture> m_DirectoryIcon;

		FileType m_SelectedFileType;
		std::string m_SelectedFileExtension;
		std::string m_FileContent;
		std::string m_NameStorage;
		std::string m_RenameStorage;
	};
}