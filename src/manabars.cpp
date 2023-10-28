#include "otpch.h"

#include "manabars.h"

#include "pugicast.h"
#include "tools.h"

bool Manabars::reload()
{
	manabars.clear();
	return loadFromXml();
}

bool Manabars::loadFromXml()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/manaBar.xml");
	if (!result) {
		printXMLError("Error - Manabars::loadFromXml", "data/XML/manabars.xml", result);
		return false;
	}

	for (auto manaBarNode : doc.child("manaBar").children()) {
		manabars.emplace_back(
			static_cast<uint8_t>(pugi::cast<uint16_t>(manaBarNode.attribute("id").value())),
			manaBarNode.attribute("name").as_string(),
			manaBarNode.attribute("premium").as_bool()
		);
	}
	manabars.shrink_to_fit();
	return true;
}

Manabar* Manabars::getManabarByID(uint8_t id)
{
	auto it = std::find_if(manabars.begin(), manabars.end(), [id](const Manabar& manaBar) {
		return manaBar.id == id;
		});

	return it != manabars.end() ? &*it : nullptr;
}

Manabar* Manabars::getManabarByName(const std::string& name) {
	auto manabarName = name.c_str();
	for (auto& it : manabars) {
		if (strcasecmp(manabarName, it.name.c_str()) == 0) {
			return &it;
		}
	}

	return nullptr;
}

