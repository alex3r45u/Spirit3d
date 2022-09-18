#pragma once
#include <functional>
#include <typeinfo>

namespace Spirit {
	class DragDropSystem {
	public:

		

		template<typename T>
		static void SetTarget(const char* targetName, std::function<void(T)> func) {
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(targetName)) {
					func(*(T*)payload->Data);
					ImGui::EndDragDropTarget();
				}

			}
		}

		template<typename T>
		static void SetSource(const char* sourceName, T data) {
			if (ImGui::BeginDragDropSource()) {

				ImGui::SetDragDropPayload(sourceName, &data,sizeof(T));
				ImGui::EndDragDropSource();
			}
		}

		template<>
		static void SetTarget(const char* targetName, std::function<void(const char*)> func) {
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(targetName)) {
					func((const char*)payload->Data);
					ImGui::EndDragDropTarget();
				}

			}
		}

		template<>
		static void SetSource(const char* sourceName, const char* data) {
			if (ImGui::BeginDragDropSource()) {

				ImGui::SetDragDropPayload(sourceName, data, (strlen(data) + 1) * sizeof(const char*));
				ImGui::EndDragDropSource();
			}
		}
	};
	
}