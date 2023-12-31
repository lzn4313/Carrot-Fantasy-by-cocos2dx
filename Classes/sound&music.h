#pragma once
#include"AudioEngine.h"
#include"CCUserDefault.h"
USING_NS_CC;
//初始化声音数据，即背景音乐+音效均为打开
static void init_sound() {
	UserDefault::getInstance()->setIntegerForKey("sound_effect", 1);
	UserDefault::getInstance()->setIntegerForKey("bg_music", 1);
}
//播放按钮音效
static void button_sound_effect() {
	//若音效打开，则播放按钮音效
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		AudioEngine::play2d("/sound/button.mp3", false, 0.5f);
	}
}
//播放翻页音效
static void page_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放翻页音效
		AudioEngine::play2d("/sound/page.mp3", false, 0.2f);
	}
}
//播放建造音效
static void build_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放建造音效
		AudioEngine::play2d("/sound/build_tower.mp3", false, 1.0f);
	}
}
//播放出售音效
static void sell_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放出售音效
		AudioEngine::play2d("/sound/sell_tower.mp3", false, 1.0f);
	}
}
//播放升级音效
static void uplevel_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放升级音效
		AudioEngine::play2d("/sound/uplevel_tower.mp3", false, 1.0f);
	}
}
//播放星星攻击音效
static void star_atk_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放星星攻击音效
		AudioEngine::play2d("/sound/star_atk.mp3", false, 1.0f);
	}
}
//播放瓶子攻击音效
static void bottle_atk_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放瓶子攻击音效
		AudioEngine::play2d("/sound/bottle_atk.mp3", false, 1.0f);
	}
}
//播放风扇攻击音效
static void fan_atk_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放风扇攻击音效
		AudioEngine::play2d("/sound/fan_atk.mp3", false, 1.0f);
	}
}
//播放大便攻击音效
static void shit_atk_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放大便攻击音效
		AudioEngine::play2d("/sound/shit_atk.mp3", false, 1.0f);
	}
}
//播放萝卜被吃音效
static void carrot_eaten_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放萝卜被吃音效
		AudioEngine::play2d("/sound/carrot_eaten.mp3", false, 1.0f);
	}
}
//播放普通怪死亡音效
static void normal_dead_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放普通怪死亡音效
		AudioEngine::play2d("/sound/Land112.mp3", false, 1.0f);
	}
}
//播放飞行怪死亡音效
static void fly_dead_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放飞行怪死亡音效
		AudioEngine::play2d("/sound/Fly162.mp3", false, 1.0f);
	}
}
//播放boss死亡音效
static void boss_dead_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//若音效打开，则播放boss死亡音效
		AudioEngine::play2d("/sound/Fat141.mp3", false, 1.0f);
	}
}
