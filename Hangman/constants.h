#pragma once
#include <string>
#include <map>
#include "config.h"

using namespace std;


const char PLACEHOLDER = '_';
const char SPACE = ' ';


enum ATTR { strength, agility, inteligence, universal };

struct Hero {
	string name;
	ATTR primary;

	Hero(string name, ATTR attr) {
		this->primary = attr;
		this->name = name;
	}
};

const Hero HEROS2[] = {
	Hero("Abaddon", universal),
	Hero("Alchemist", strength)
};


const std::string HEROS[] = {
	"Abaddon",
	"Alchemist",
	"Ancient Apparition",
	"Anti Mage",
	"Arc Warden",
	"Axe",
	"Bane",
	"Batrider",
	"Beastmaster",
	"Bloodseeker",
	"Bounty Hunter",
	"Brewmaster",
	"Bristleback",
	"Broodmother",
	"Centaur Warrunner",
	"Chaos Knight",
	"Chen",
	"Clinkz",
	"Clockwerk",
	"Crystal Maiden",
	"Dark Seer",
	"Dark Willow",
	"Dazzle",
	"Death Prophet",
	"Disruptor",
	"Doom",
	"Dragon Knight",
	"Drow Ranger",
	"Earth Spirit",
	"Earthshaker",
	"Elder Titan",
	"Ember Spirit",
	"Enchantress",
	"Enigma",
	"Faceless Void",
	"Grimstroke",
	"Gyrocopter",
	"Hoodwink",
	"Huskar",
	"Invoker",
	"Io",
	"Jakiro",
	"Juggernaut",
	"Keeper of the Light",
	"Kunkka",
	"Legion Commander",
	"Leshrac",
	"Lich",
	"Lifestealer",
	"Lina",
	"Lion",
	"Lone Druid",
	"Luna",
	"Lycan",
	"Magnus",
	"Mars",
	"Medusa",
	"Meepo",
	"Mirana",
	"Monkey King",
	"Morphling",
	"Naga Siren",
	"Nature's Prophet",
	"Necrophos",
	"Night Stalker",
	"Nyx Assassin",
	"Ogre Magi",
	"Omniknight",
	"Oracle",
	"Outworld Destroyer",
	"Pangolier",
	"Phantom Assassin",
	"Phantom Lancer",
	"Phoenix",
	"Puck",
	"Pudge",
	"Pugna",
	"Queen of Pain",
	"Razor",
	"Riki",
	"Rubick",
	"Sand King",
	"Shadow Demon",
	"Shadow Fiend",
	"Shadow Shaman",
	"Silencer",
	"Skywrath Mage",
	"Slardar",
	"Slark",
	"Snapfire",
	"Sniper",
	"Spectre",
	"Spirit Breaker",
	"Storm Spirit",
	"Sven",
	"Techies",
	"Templar Assassin",
	"Terrorblade",
	"Tidehunter",
	"Timbersaw",
	"Tinker",
	"Tiny",
	"Treant Protector",
	"Troll Warlord",
	"Tusk",
	"Underlord",
	"Undying",
	"Ursa",
	"Vengeful Spirit",
	"Venomancer",
	"Viper",
	"Visage",
	"Void Spirit",
	"Warlock",
	"Weaver",
	"Windranger",
	"Winter Wyvern",
	"Witch Doctor",
	"Wraith King",
	"Zeus"
};