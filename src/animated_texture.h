#pragma once

#include <vector>
#include <unordered_map>

#include "types.h"
#include "texture.h"
#include "settings.h"
#include "utility/timer.h"
#include "utility/string.h"

/* animated_texture.h:
   A texture with user-defined animations. */

enum class Animation : lyo::u8
{
	Idle,
	Run,
	Attack,
	Hurt,

	MaxAmount = 255
};

BEGIN_LYO_NAMESPACE
class AnimatedTexture : public Texture
{
public:

	using InitPair = std::pair<Animation, lyo::ST::Texture>;
	using InitList = std::initializer_list<InitPair>;

	using FrameVector = std::vector<lyo::Size::Texture>;

	using AnimationMap = std::unordered_map<Animation, FrameVector>;

	AnimatedTexture(const lyo::Window& window, lyo::c_string file_name, const InitList& animations, const lyo::Size::Texture& frame_size, double scale = 1.0, double time_to_update = lyo::Settings::Animation_TTU) noexcept;

	void update() noexcept;

	void set_animation(Animation animation, lyo::ST::Animation frame = 0) noexcept;

private:

	AnimationMap m_spritesheet;	// 80b

	Animation			m_animation;	// 1b
	lyo::ST::Animation	m_frame;		// 1b

	lyo::Timer		m_animationTimer;	// 8b
	const double	m_timeToUpdate;		// 8b
};
END_LYO_NAMESPACE