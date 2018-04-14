#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "testing.h"

using std::string;

// plz extend me
class Scene : public sf::Drawable {

public:
	Scene(sf::Vector2f &size = sf::Vector2f(0, 0), string textureFilePath="", std::vector<sf::Drawable *> &drawables=std::vector<sf::Drawable *>(), string name="");
	virtual ~Scene();
	virtual void update(); // update the view
	virtual void updatePhysics(float dt);
	
	string getName();
	void setName(string &name);
	sf::View * getView();
	sf::Vector2f getSize();
	void setTexture(sf::Texture * newTexture);

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	std::vector<sf::Drawable *> drawables;
	sf::View *view;
	sf::Vector2f size;
	sf::RectangleShape *background;

private:
	string name;
	sf::Texture *texture;
};