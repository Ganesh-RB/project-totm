#include "stdafx.h"
#include "asset_holder.h"

asset_holder::asset_holder()
{
}

asset_holder::~asset_holder()
{
}

void asset_holder::add_texture(group_member_name _name, int id, const std::string & filepath,bool setrepeated)
{
	auto temp_texture = std::make_unique<sf::Texture>();
	if (temp_texture->loadFromFile(filepath)) {
		temp_texture->setRepeated(setrepeated);
		m_textures[std::make_pair(_name, id)] = std::move(temp_texture);
	}
	else {
		std::cout << "ERROR::ASSET_HOLDER::ADD_TEXTURE " << filepath << " is a invalid path" << std::endl;
	}
}

void asset_holder::add_font(int id, const std::string & filepath)
{
	auto temp_font = std::make_unique<sf::Font>();
	if (temp_font->loadFromFile(filepath)) {
		m_fonts[id] = std::move(temp_font);
	}
	else {
		std::cout << "ERROR::ASSET_HOLDER::ADD_FONT " << filepath << " is a invalid path" << std::endl;
	}
}

void asset_holder::add_sound_buffer(group_member_name _name, int id, const std::string & filepath)
{
	auto temp_soundbuffer = std::make_unique<sf::SoundBuffer>();
	if (temp_soundbuffer->loadFromFile(filepath)) {
		m_soundbuffers[std::make_pair(_name, id)] = std::move(temp_soundbuffer);
	}
	else {
		std::cout << "ERROR::ASSET_HOLDER::ADD_SOUND_BUFFER " << filepath << " is a invalid path" << std::endl;
	}
}

void asset_holder::clear_sounds()
{
	m_sounds.remove_if(is_finished());
}

void asset_holder::play_sound(group_member_name _name, int id)
{
	assert(m_soundbuffers.find(std::make_pair(_name, id)) != m_soundbuffers.end());
	m_sounds.emplace_back(sf::Sound::Sound(*(m_soundbuffers[std::make_pair(_name, id)].get())));
	m_sounds.back().play();
}

 sf::Texture& asset_holder::get_texture(group_member_name _name, int id) 
{
	assert(m_textures.find(std::make_pair(_name, id))!=m_textures.end());
	return *((m_textures[std::make_pair(_name, id)]).get());
}

 sf::Font& asset_holder::get_font(int id) 
{
	assert(m_fonts.find(id) != m_fonts.end());
	return *(m_fonts[id].get());
}

 sf::SoundBuffer& asset_holder::get_soundbuffer(group_member_name _name, int id)
 {
	 assert(m_soundbuffers.find(std::make_pair(_name, id)) != m_soundbuffers.end());
	 return *((m_soundbuffers[std::make_pair(_name, id)]).get());
 }
