#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <vector>

namespace Spirit {
	template<class T>
	class AssetRegistry {
	public:
		AssetRegistry() = default;
		AssetRegistry(std::function<std::shared_ptr<T>(std::vector<std::string>)> addFunc)
			: m_AddFunc(addFunc) {}
		void AddMember(const std::vector<std::string>& name) {
			if (MemberExists(name.at(0)))
				return;
			std::shared_ptr<T> member = m_AddFunc(name);
			m_Members[name.at(0)] = { member, false };
		}
		void AddMember(const std::string& name, const std::shared_ptr<T>& member) {
			if (MemberExists(name))
				return;
			m_Members[name] = {member, false};
		}
		std::shared_ptr<T> GetMember(const std::vector<std::string>& name) {
			if (!MemberExists(name.at(0)))
				AddMember(name);
			m_Members[name.at(0)].second = true;
			return m_Members[name.at(0)].first;
		}

		void Update() {
			std::vector<std::string> removeMembers;
			for (auto& it : m_Members) {
				if (it.second.second == false) {
					removeMembers.push_back(it.first);
				}
			}
			for (auto& it : removeMembers) {
				m_Members.erase(it);
			}
			
		}
	private:
		bool MemberExists(const std::string& name) {
			return m_Members.find(name) != m_Members.end();
		}
	private:
		std::function<std::shared_ptr<T>(std::vector<std::string>)> m_AddFunc;
		std::unordered_map<std::string, std::pair<std::shared_ptr<T>, bool>> m_Members;
		
	};
}