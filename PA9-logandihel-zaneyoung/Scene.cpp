#include "Scene.h"

Scene::Scene(std::vector<sf::Drawable *> &drawables, string name) {
	this->drawables = drawables;
	this->name = name;
}

void Scene::update() {

}

void Scene::updatePhysics(float dt) {

}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (sf::Drawable *it : drawables) {
		target.draw(*it, states);
	}
}

string Scene::getName() {
	return name;
}

void Scene::setName(string &name) {
	this->name = name;
}

Scene::~Scene() {
	for (sf::Drawable *it : drawables) {
		delete it;
	}
}