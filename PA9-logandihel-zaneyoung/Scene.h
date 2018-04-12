#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using std::string;

// plz extend me
class Scene : public sf::Drawable {

public:
	Scene(std::vector<sf::Drawable *> &drawables=std::vector<sf::Drawable *>(), string name="");
	virtual ~Scene();
	virtual void update();
	virtual void updatePhysics(float dt);
	
	string getName();
	void setName(string &name);

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	std::vector<sf::Drawable *> drawables;
private:
	string name;
};