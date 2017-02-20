#include "game/scene.h"
Scene* SceneManager::get_scene(std::string name) {
	return this->scene_map[name];
}

void SceneManager::set_scene(std::string name, Scene* scene) {
	this->scene_map[name] = scene;
}
void SceneManager::new_scene(std::string name, Scene* scene) {
	if (scene == nullptr);
		scene = new Scene();
		set_scene(name, scene);
}

void SceneManager::new_scene(std::string name) {
	new_scene(name, nullptr);
}

bool SceneManager::remove_scene(std::string name) {
	if(this->scene_map[name]) {
		this->scene_map.erase(name);
		return true;
	}
	return false;
}

