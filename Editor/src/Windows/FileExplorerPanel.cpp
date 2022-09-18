#include "sppch.h"
#include "FileExplorerPanel.h"
#include <imgui/imgui.h>

#include <iostream>
#include <filesystem>
#include "Spirit/ImGui/DragDropSystem.h"


Spirit::FileExplorerPanel::FileExplorerPanel()
{
	Init();
}

Spirit::FileExplorerPanel::FileExplorerPanel(const std::shared_ptr<Scene>& scene, std::filesystem::path directory)
	: Panel(scene), m_RootDirectory(directory), m_CurrentDirectory(directory)
{
	Init();
}

void Spirit::FileExplorerPanel::ImGuiRender()
{
	ImGui::Begin("File Explorer");
	DrawDirectory(m_CurrentDirectory);
	ImGui::End();

	ImGui::Begin("File Inspector");
	if (m_SelectedFile != std::filesystem::path()) {
		Inspect(m_SelectedFile);
	}
	ImGui::End();
}

void Spirit::FileExplorerPanel::SetDirectory(std::filesystem::path directory)
{
	m_RootDirectory = directory;
	m_CurrentDirectory = m_RootDirectory;
}

void Spirit::FileExplorerPanel::DrawDirectory(std::filesystem::path directory)
{
	if (m_CurrentDirectory != std::filesystem::path(m_RootDirectory)) {
		if (ImGui::Button("<-")) {
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}
		DragDropSystem::SetTarget<const char*>("FILE_EXPLORER", [&](const char* c) {
			std::filesystem::path p(c);
			std::filesystem::rename(p, m_CurrentDirectory.parent_path().string() + "\\" + p.filename().string());
			});
	}
	for (const auto& entry : std::filesystem::directory_iterator(m_CurrentDirectory)) {
		std::string fileName = entry.path().filename().string();

		if (entry.is_directory()) {
			ImGui::Button(fileName.c_str());
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{
				m_CurrentDirectory /= fileName;
			}

			DragDropSystem::SetTarget<const char*>("FILE_EXPLORER", [&](const char* c) {
				std::filesystem::path p(c);
				std::filesystem::rename(p, entry.path().string() + "\\" + p.filename().string());
				});

		}
		else {
			if (ImGui::Button(fileName.c_str())) {
				m_SelectedFile = entry.path();
			}

		}
		//Popups
		{
			if (ImGui::IsItemClicked(1)) {
				ImGui::OpenPopup(entry.path().string().c_str());
			}
			enum Mode {
				None,
				Delete,
			};
			Mode mode = Mode::None;
			if (ImGui::BeginPopup(entry.path().string().c_str())) {
				if (ImGui::Selectable("Delete")) {
					mode = Mode::Delete;
				}
				ImGui::EndPopup();
			}
			switch (mode)
			{
			case Delete:
				ImGui::OpenPopup((entry.path().string() + " Delete").c_str(), ImGuiPopupFlags_AnyPopupId);
				break;
			default:
				break;
			}
			if (ImGui::BeginPopupModal((entry.path().string() + " Delete").c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove)) {
				ImGui::Text("Are you sure?");
				ImGui::Text(fileName.c_str());
				ImGui::Separator();
				if (ImGui::Button("Delete")) {
					std::filesystem::remove(entry);
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel")) {
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		
		
		DragDropSystem::SetSource("FILE_EXPLORER" , entry.path().string().c_str());
		
		
		
		
	}
		
}

void Spirit::FileExplorerPanel::Inspect(std::filesystem::path directory)
{
	//Switch Through the file type
}

void Spirit::FileExplorerPanel::Init()
{
	m_DirectoryIcon = Spirit::Render::Texture2d::Create("resources/folder.png");
	m_FileIcon = Spirit::Render::Texture2d::Create("resources/file.png");
}
