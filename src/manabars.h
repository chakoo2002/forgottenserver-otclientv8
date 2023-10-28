#ifndef FS_MANABARS_H
#define FS_MANABARS_H

struct Manabar
{
	Manabar(uint8_t id, std::string name, bool premium) :
		name(std::move(name)), id(id), premium(premium) {}

	uint8_t id;
	std::string name;
	bool premium;
};

class Manabars
{
public:
	bool reload();
	bool loadFromXml();
	Manabar* getManabarByID(uint8_t id);
	Manabar* getManabarByName(const std::string& name);

	const std::vector<Manabar>& getManabars() const {
		return manabars;
	}

private:
	std::vector<Manabar> manabars;
};

#endif
