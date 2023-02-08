#include "sppch.h"
#include "FileExplorerPanel.h"
#include <imgui/imgui.h>

#include <iostream>
#include <filesystem>
#include "Spirit/ImGui/DragDropSystem.h"
#include "Spirit/Core/File.h"
#include "../Core/ScriptSolution.h"
#include "Spirit/Application.h"
#include "Spirit/Core/File.h"
#include "Spirit/Core/AssetLibrary.h"

#define ADD_ITEM(N, C) if (ImGui::MenuItem(std::string(#N).substr(10).c_str())) { m_SelectedFileType = N; m_FileContent = C; }

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
	AddFile();
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
			std::filesystem::rename(p, File::Merge2Paths(m_CurrentDirectory.parent_path(), p.filename()));
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
				std::filesystem::rename(p, File::Merge2Paths(entry.path(), p.filename()));
				});

		}
		else {
			if (ImGui::Button(fileName.c_str())) {
				m_SelectedFile = entry.path();
			}
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{
				switch (Spirit::File::GetType(entry.path().extension().string()))	
				{
				case FileType::Script: {
					Spirit::ScriptSolution::Open(PROJECT);
					break;
				}
				default:
					break;
				}
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
				Rename
			};
			Mode mode = Mode::None;
			if (ImGui::BeginPopup(entry.path().string().c_str())) {
				if (ImGui::Selectable("Delete")) {
					mode = Mode::Delete;
				}
				if (ImGui::Selectable("Rename")) {
					m_RenameStorage = entry.path().filename().string();
					mode = Mode::Rename;
				}
				ImGui::EndPopup();
			}
			switch (mode)
			{
			case Delete:
				ImGui::OpenPopup((entry.path().string() + " Delete").c_str(), ImGuiPopupFlags_AnyPopupId);
				break;
			case Rename:
				ImGui::OpenPopup((entry.path().string() + " Rename").c_str(), ImGuiPopupFlags_AnyPopupId);
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
			if (ImGui::BeginPopupModal((entry.path().string() + " Rename").c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove)) {


				ImGui::Text(entry.path().filename().string().c_str());
				ImGui::Separator();
				

				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy(buffer, m_RenameStorage.c_str());

				if (ImGui::InputText("Name", buffer, sizeof(buffer))) {
					m_RenameStorage = std::string(buffer);
				}
				if (ImGui::Button("Rename")) {
					std::filesystem::rename(entry.path(), File::Merge2Paths(entry.path().parent_path(), m_RenameStorage));
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel")) {
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		
		
		DragDropSystem::SetSource("FILE_EXPLORER" , entry.path().string().c_str());
		switch (Spirit::File::GetType(entry.path().extension().string()))	
		{
		case FileType::Script:
			DragDropSystem::SetSource("COMPONENT", (PROJECT->GetSettings().ProjectName + ".assets." + entry.path().stem().string()).c_str());
			break;
		case FileType::Mesh:
			DragDropSystem::SetSource<const char*>("MESH", entry.path().string().c_str());
		default:
			break;
		}
		
		
		
	}
		
}

void Spirit::FileExplorerPanel::AddFile()
{
	if (ImGui::Button("+")) {
		ImGui::OpenPopup("ADD_FILE");
	}
	if (ImGui::BeginPopup("ADD_FILE")) {
		ImGui::Text("Select Filetype");
		ImGui::Separator();
		ADD_ITEM(FileType::Material, "")
		ImGui::EndPopup();
	}
	if (m_SelectedFileType != FileType::None) { ImGui::OpenPopup("CHOOSE_NAME"); }
	if (ImGui::BeginPopupModal("CHOOSE_NAME", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove)) {
		ImGui::Text("Choose your filename");
		ImGui::Separator();
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy(buffer, m_NameStorage.c_str());

		if (ImGui::InputText("Name", buffer, sizeof(buffer))) {
			m_NameStorage = std::string(buffer);
		}
		if (ImGui::BeginCombo("Choose file extension", m_SelectedFileExtension.c_str())) {
			for (auto s : File::GetExtensionsOutFileType(m_SelectedFileType)) {
				if (ImGui::Selectable(s.c_str())) { m_SelectedFileExtension = s; }
			}
			ImGui::EndCombo();
		}
		if (ImGui::Button("Create")) {
			std::ofstream stream(File::Merge2Paths(m_CurrentDirectory, m_NameStorage + m_SelectedFileExtension));
			stream << m_FileContent;
			stream.close();
			m_SelectedFileType = FileType::None;
			m_SelectedFileExtension = "";
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			m_SelectedFileType = FileType::None;
			m_SelectedFileExtension = "";
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
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
	m_SelectedFileType = FileType::None;
	m_SelectedFileExtension = "";
}
