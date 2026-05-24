#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class TeksturkiRepository
{
private:
	map<string, Texture*> textures;

public:
	TeksturkiRepository() {}

	~TeksturkiRepository()
	{
		for (auto& para : this->textures)
			delete para.second;
	}

	void ladowanie(const string& nazwa, const string& sciezka)
	{
		Texture* tex = new Texture();
		try
		{
			if (!tex->loadFromFile(sciezka))
				throw runtime_error("Nie mo¿na zaladowac tekstury: " + sciezka);
			this->textures[nazwa] = tex;
		}
		catch (const runtime_error& e)
		{
			cout << "ERROR TEKSTUR :: " << e.what() << endl;
			delete tex;
		}
	}

	Texture* get(const string& nazwa)
	{
		auto it = this->textures.find(nazwa);
		if (it == this->textures.end())
			throw runtime_error("Brak tekstury o kluczu: " + nazwa);
		return it->second;
	}

	bool contains(const string& nazwa) const
	{
		return this->textures.count(nazwa) > 0;
	}
};