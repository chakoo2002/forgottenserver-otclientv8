#ifndef FS_HEALTHBARS_H
#define FS_HEALTHBARS_H

struct Healthbar
{
	Healthbar(uint8_t id, std::string name, bool premium) :
		name(std::move(name)), id(id), premium(premium) {}

	uint8_t id;
	std::string name;
	bool premium;
};

class Healthbars
{
public:
	bool reload();
	bool loadFromXml();
	Healthbar* getHealthbarByID(uint8_t id);
	Healthbar* getHealthbarByName(const std::string& name);

	const std::vector<Healthbar>& getHealthbars() const {
		return healthbars;
	}

private:
	std::vector<Healthbar> healthbars;
};

#endif
