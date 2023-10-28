#include "otpch.h"

#include "healthbars.h"

#include "pugicast.h"
#include "tools.h"

bool Healthbars::reload()
{
	healthbars.clear();
	return loadFromXml();
}

bool Healthbars::loadFromXml()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/healthbars.xml");
	if (!result) {
		printXMLError("Error - Healthbars::loadFromXml", "data/XML/healthbars.xml", result);
		return false;
	}

	for (auto healthbarNode : doc.child("healthbars").children()) {
		healthbars.emplace_back(
			static_cast<uint8_t>(pugi::cast<uint16_t>(healthbarNode.attribute("id").value())),
			healthbarNode.attribute("name").as_string(),
			healthbarNode.attribute("premium").as_bool()
		);
	}
	healthbars.shrink_to_fit();
	return true;
}

Healthbar* Healthbars::getHealthbarByID(uint8_t id)
{
	auto it = std::find_if(healthbars.begin(), healthbars.end(), [id](const Healthbar& healthbar) {
		return healthbar.id == id;
		});

	return it != healthbars.end() ? &*it : nullptr;
}

Healthbar* Healthbars::getHealthbarByName(const std::string& name) {
	auto healthbarName = name.c_str();
	for (auto& it : healthbars) {
		if (strcasecmp(healthbarName, it.name.c_str()) == 0) {
			return &it;
		}
	}

	return nullptr;
}

