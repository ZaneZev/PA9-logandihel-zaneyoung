#include "SVGParser.h"

SVGParser::SVGParser(string filepath) {
	this->infile.open(filepath);
	if (!infile) {
		cout << "Could not open file" << endl;
	}
}

void SVGParser::parse() {

	string buffer;
	do {
		// ignore until we hit <g
		do {
			infile >> buffer;
		} while (!infile.fail() && buffer != "<g");

		// get the id layer
		//infile >> buffer; // throw away transform
		infile >> buffer; // gives us id="THE ID WE WANT"

		string id = buffer.substr(4, buffer.size() - 3);
		G_Layer gl;
		gl.id = id;

		infile >> buffer;
		do {
			SVGData rect;

			infile >> buffer;

			if (buffer == "</svg>") {
				return;
			}

			if (buffer.substr(0, 3) != "y=\"") {
				// transform="rotate(
				if (buffer.substr(0,3) == "tra")
					rect.rotation = std::stof(buffer.substr(18, buffer.size() - 4));
				infile >> buffer; // y="###"
			}
			else {
				rect.rotation = 0.f;
			}

			rect.y = std::stof(buffer.substr(3, buffer.size() - 3));
			infile >> buffer; // x="###"
			rect.x = std::stof(buffer.substr(3, buffer.size() - 3));
			infile >> buffer; // height="###"
			rect.height = std::stof(buffer.substr(8, buffer.size() - 3));
			infile >> buffer; // width="###"
			rect.width = std::stof(buffer.substr(7, buffer.size() - 3));

			while (buffer.substr(0, 5) != "style") {
				infile >> buffer;
			}
			infile >> buffer; // closing bracket
			infile >> buffer; // for good luck

			rect.y *= 4;
			rect.width *= 4;
			rect.x *= 4;
			rect.height *= 4;

			gl.svgs.push_back(rect);

		} while (!infile.fail() && buffer != "</g>");
		glayers.push_back(gl);
	} while (!infile.fail());
}