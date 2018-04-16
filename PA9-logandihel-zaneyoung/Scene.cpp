#include "Scene.h"

Scene::Scene(sf::Vector2f &size, string textureFilePath, std::vector<sf::Drawable *> &drawables, string name) {
	this->size = size;
	this->drawables = drawables;
	this->name = name;
	this->view = nullptr;
	this->background = new sf::RectangleShape(size);
	//this->background->setFillColor(sf::Color::Blue);
	this->texture = new sf::Texture;
	if (textureFilePath != "" && !this->texture->loadFromFile(textureFilePath)) {
		cout << "could not load scene texture" << endl;
	}
	else {
		// success
		setTexture(texture);
	}

	//drawables.push_back(background);
}

void Scene::update() {

}

void Scene::updatePhysics(float dt) {

}

void Scene::setTexture(sf::Texture * newTexture) {
	this->background->setTexture(newTexture);
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (sf::Drawable *it : drawables) {
		target.draw(*it, states);
	}
}

string Scene::getName() {
	return name;
}

sf::Vector2f Scene::getSize() {
	return size;
}

sf::View * Scene::getView() {
	return view;
}

void Scene::setName(string &name) {
	this->name = name;
}

Scene::~Scene() {
	for (sf::Drawable *it : drawables) {
		delete it;
	}
}