#pragma once
#include "legofs.h"

std::string si = std::string("rom:/scripts/main.si");

void print_node(LegofsNode& node) {
	switch (node.type) {
	case LegofsType::Bitmap: {
		debugf(
			"%u Bitmap: \t%s \t %s\n",
			node.index,
			node.name,
			node.presenter
		);
		break;
	}
	case LegofsType::Wave: {
		debugf("%u Wave: \t%s \t %s\n", node.index, node.name, node.presenter);
		break;
	}
	case LegofsType::Flic:
	case LegofsType::Smacker: {
		debugf("%u Video: \t%s \t %s\n", node.index, node.name, node.presenter);
		break;
	}
	case LegofsType::Presenter: {
		debugf(
			"%u Presenter: \t%s \t %s\n",
			node.index,
			node.name,
			node.presenter
		);
		break;
	}
	case LegofsType::World: {
		debugf("%u World: \t%s \t %s\n", node.index, node.name, node.presenter);
		break;
	}
	case LegofsType::Object: {
		debugf(
			"%u Object: \t%s \t %s\n",
			node.index,
			node.name,
			node.presenter
		);
		break;
	}
	case LegofsType::Animation: {
		debugf(
			"%u Animation: \t%s \t %s\n",
			node.index,
			node.name,
			node.presenter
		);
		break;
	}
	case LegofsType::Event: {
		debugf("%u Event: \t%s \t %s\n", node.index, node.name, node.presenter);
		break;
	}
	case LegofsType::Model: {
		debugf("%u Model: \t%s \t %s\n", node.index, node.name, node.presenter);
		break;
	}
	case LegofsType::Path: {
		debugf("%u Path: \t%s \t %s\n", node.index, node.name, node.presenter);
		break;
	}
	case LegofsType::Texture: {
		debugf(
			"%u Texture: \t%s \t %s\n",
			node.index,
			node.name,
			node.presenter
		);
		break;
	}

	case LegofsType::Null:
		debugf("%u NULL\n", node.index);
		break;
	}
}