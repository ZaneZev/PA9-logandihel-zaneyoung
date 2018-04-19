#pragma once
#include "testing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::ifstream;
using std::vector;

typedef struct svgdata {
	float x;
	float y;
	float height;
	float width;
	float rotation;
} SVGData;

typedef struct g_layer {
	string id;
	vector<SVGData> svgs;
} G_Layer;

class SVGParser {
public:
	SVGParser(string filepath);
	void parse();

private:
	ifstream infile;
	vector<G_Layer> glayers;
};