#pragma once
#include"AudioEngine.h"
#include"CCUserDefault.h"
USING_NS_CC;
//��ʼ���������ݣ�����������+��Ч��Ϊ��
static void init_sound() {
	UserDefault::getInstance()->setIntegerForKey("sound_effect", 1);
	UserDefault::getInstance()->setIntegerForKey("bg_music", 1);
}
//���Ű�ť��Ч
static void button_sound_effect() {
	//����Ч�򿪣��򲥷Ű�ť��Ч
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		AudioEngine::play2d("/sound/button.mp3", false, 0.5f);
	}
}
//���ŷ�ҳ��Ч
static void page_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷ŷ�ҳ��Ч
		AudioEngine::play2d("/sound/page.mp3", false, 0.2f);
	}
}