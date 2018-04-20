#pragma once
#include "Game.h"
#include "collidable.h"
#include "SVGParser.h"
#include <vector>

class map :public sf::Drawable{
public:
	map(string filePath) {
		SVGParser svgp(filePath);
		svgp.parse();
		for (G_Layer layer : svgp.glayers) {
			for (SVGData block : layer.svgs) {
				if (layer.id == "marker\">") {
					collidables.push_back(new collidable(sf::Vector2f(block.height, block.width), sf::Vector2f(block.x, block.y), block.rotation, sf::Color::Transparent, false));
				}
				else if (layer.id == "solid\">") {
					collidables.push_back(new collidable(sf::Vector2f(block.height, block.width), sf::Vector2f(block.x, block.y), block.rotation, sf::Color::Cyan, true));
				}
				else
					cout << "Nope" << endl;
			}
		}
		for (collidable * it : collidables) {
			drawables.push_back(it);
		}
	}
	vector<collidable *> collidables;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		for (Drawable * it : drawables)
			target.draw(*it, states);
	}
	~map() {
		for (collidable * it : collidables)
			it = nullptr;
		for (Drawable * it : drawables)
			delete it;
	}
private :
	vector<sf::Drawable *> drawables;

};