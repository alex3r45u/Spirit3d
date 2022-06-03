#include "sppch.h"
#include "FileExplorerPanel.h"
#include <imgui/imgui.h>

#include <iostream>
#include <filesystem>


void Spirit::FileExplorerPanel::ImGuiRender()
{
	ImGui::Begin("File Explorer");
	DrawDirectory(m_CurrentDirectory);
	ImGui::End();
}

void Spirit::FileExplorerPanel::SetDirectory(std::filesystem::path directory)
{
	m_RootDirectory = directory;
	m_CurrentDirectory = m_RootDirectory;
}

void Spirit::FileExplorerPanel::DrawDirectory(std::filesystem::path directory)
{
	if (m_CurrentDirectory !=  std::filesystem::path(m_RootDirectory)) {
		if(ImGui::Button("<-")) {
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}
		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_EXPLORER")) {
				const wchar_t* path = (const wchar_t*)payload->Data;
				std::filesystem::path p(path);
				std::filesystem::rename(p, m_CurrentDirectory.parent_path().string() + "\\" + p.filename().string());
				ImGui::EndDragDropTarget();
			}

		}
	}
	for (const auto& entry : std::filesystem::directory_iterator(m_CurrentDirectory)) {
		std::string fileName = entry.path().filename().string();

		if (entry.is_directory()) {
			if (ImGui::Button(fileName.c_str())) {
				m_CurrentDirectory /= fileName;
			}
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_EXPLORER")) {
					const wchar_t* path = (const wchar_t*)payload->Data;
					std::filesystem::path p(path);
					std::filesystem::rename(p, entry.path().string() + "\\" + p.filename().string());
					ImGui::EndDragDropTarget();
				}

			}
			
		}
		else {
			if (ImGui::Button(fileName.c_str())) {
				
			}
			
		}

		if (ImGui::BeginDragDropSource()) {
			const wchar_t* c = entry.path().c_str();
			ImGui::SetDragDropPayload("FILE_EXPLORER", c, (wcslen(c) + 1) * sizeof(wchar_t), ImGuiCond_Once);
			ImGui::EndDragDropSource();
		}
		
		
		
	}
		
}
