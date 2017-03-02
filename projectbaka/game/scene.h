#pragma once
#include<string>
#include <map>

class Scene {
private:
	 unsigned int m_scene_id;
	 std::string m_scene_name;
public:
};
//not yet been used.
class SceneManager {
	std::map<std::string, Scene*> scene_map;
public:
	Scene* get_scene(std::string name);

	void set_scene(std::string name, Scene *scene);

	void new_scene(std::string, Scene *scene);
	
	void new_scene(std::string name);
	bool remove_scene(std::string);

};


