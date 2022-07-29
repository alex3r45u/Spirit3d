#pragma once
#include "Panel.h"
#include <filesystem>

namespace Spirit {
	class FileExplorerPanel : public Panel {
	public:
		FileExplorerPanel() = default;
		FileExplorerPanel(const std::shared_ptr<Scene>& scene, std::filesystem::path directory) : Panel(scene), m_RootDirectory(directory), m_CurrentDirectory(directory) {}

		virtual void ImGuiRender() override;
		void SetDirectory(std::filesystem::path directory);
	private:
		void DrawDirectory(std::filesystem::path directory);
		void Inspect(std::filesystem::path directory);
	private:
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_RootDirectory;
		std::filesystem::path m_SelectedFile;
	};
}