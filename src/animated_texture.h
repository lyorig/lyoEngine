#pragma once

#include <vector>
#include <unordered_map>
#include "types.h"
#include "texture.h"
#include "utility/timer.h"

enum class Animation
{
	Idle,
	Run,
	Attack,
	Hurt
};

BEGIN_LYO_NAMESPACE
class AnimatedTexture final : public Texture
{
	using FrameVector	= std::vector<lyo::Area::Texture>;
	using AnimationMap	= std::unordered_map<Animation, FrameVector>;

	lyo::u8			m_currentFrame;
	AnimationMap	m_animations;

	lyo::Timer m_timeToUpdate;

public:

	using InitPair = std::pair<Animation, lyo::SizeType::Texture>;
	using InitList = std::initializer_list<InitPair>;

	AnimatedTexture(lyo::Window& window, lyo::cstring file_name, const InitList& animations, const lyo::Size::Texture& frame_size) noexcept;

	void update() noexcept;
};
END_LYO_NAMESPACE