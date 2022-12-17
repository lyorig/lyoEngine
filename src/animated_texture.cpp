#include "animated_texture.h"

lyo::AnimatedTexture::AnimatedTexture(lyo::Window& window, lyo::cstring file_name, const InitList& animations, const lyo::Size::Texture& frame_size) noexcept :
	Texture{ window, file_name },
	m_currentFrame{ 0 },
	m_animations{}
{
	using namespace lyo;

	FrameVector				frame_vector;
	const InitPair*			init_list_begin	{ animations.begin() };
	
	const SizeType::Texture width{ this->width() }, height{ this->height() };

	for (u16 y{ 0 }; y < animations.size(); y++)
	{
		using Type = lyo::SizeType::Texture;

		/* std::initializer_list doesn't have a subscript operator. Sorry! */
		const InitPair& anim{ *(init_list_begin + y) };

		/* If the frame count is NULL, deduce it. */
		const u16 framecount{ anim.second ? anim.second : SC<u16>(width / frame_size.x) };

		frame_vector.resize(framecount);
		for (u16 x{ 0 }; x < framecount; x++)
			frame_vector[x] = { SC<Type>(x * width), SC<Type>(y * height), width, height };

		m_animations.insert({ anim.first, frame_vector });
		frame_vector.clear();
	}
}



void lyo::AnimatedTexture::update() noexcept
{

}