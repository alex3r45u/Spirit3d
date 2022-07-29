#pragma once
#include <functional>
#include <typeinfo>

namespace Spirit {
	class DragDropSystem {
	public:


		static void SetTarget(const char* targetName, std::function<void(const char*)> func) {
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(targetName)) {
					func((const char*)payload->Data);
					ImGui::EndDragDropTarget();
				}

			}
		}

		static void SetSource(const char* sourceName, const char* data) {
			if (ImGui::BeginDragDropSource()) {

				ImGui::SetDragDropPayload(sourceName, data, (strlen(data) + 1) * sizeof(const char*));
				ImGui::EndDragDropSource();
			}
		}

		static void SetTargetInt(const char* targetName, std::function<void(int)> func) {
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(targetName)) {
					func(*(int*)payload->Data);
					ImGui::EndDragDropTarget();
				}

			}
		}
		static void SetSourceInt(const char* sourceName, int data) {
			if (ImGui::BeginDragDropSource()) {

				ImGui::SetDragDropPayload(sourceName, &data,sizeof(int));
				ImGui::EndDragDropSource();
			}
		}
	};
	
}