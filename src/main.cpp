#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(MyGJBaseGameLayer, GJBaseGameLayer) {
	bool init() {
		if (!GJBaseGameLayer::init()) return false;
		if (!Mod::get()->getSettingValue<bool>("enabled")) return true;
		const auto pl = PlayLayer::get();
		const auto lel = LevelEditorLayer::get();
		if (!pl && !lel) return true;
		if (!Mod::get()->getSettingValue<bool>("playLayer") && pl == this) return true;
		if (!Mod::get()->getSettingValue<bool>("editorLayer") && lel == this) return true;
		if (!m_audioVisualizerBG || !m_audioVisualizerSFX) return true;
		MyGJBaseGameLayer::repositionMusicAndSFX();
		return true;
	}
	void repositionMusicAndSFX(FMODLevelVisualizer* fmodMusic = m_audioVisualizerBG, FMODLevelVisualizer* fmodSFX = m_audioVisualizerSFX) {
		if (!Mod::get()->getSettingValue<bool>("enabled")) return;
		if (!Mod::get()->getSettingValue<bool>("raydeeuxMode")) {
			fmodMusic->setPosition(Mod::get()->getSettingValue<int64_t>("musicPositionX"), Mod::get()->getSettingValue<int64_t>("musicPositionY"));
			fmodMusic->setRotation(Mod::get()->getSettingValue<int64_t>("musicRotation"));
			fmodMusic->setScale(Mod::get()->getSettingValue<double>("musicScale"));
			fmodSFX->setPosition(Mod::get()->getSettingValue<int64_t>("sfxPositionX"), Mod::get()->getSettingValue<int64_t>("sfxPositionY"));
			fmodSFX->setRotation(Mod::get()->getSettingValue<int64_t>("sfxRotation"));
			fmodSFX->setScale(Mod::get()->getSettingValue<double>("sfxScale"));
		} else {
			auto winSizeWidth = CCDirector::get()->getWinSize().width;
			fmodMusic->setPosition(winSizeWidth * 0.25, 15);
			fmodMusic->setRotation(270);
			fmodMusic->setScale(0.75);
			fmodSFX->setPosition(winSizeWidth * 0.75, 15);
			fmodSFX->setRotation(90);
			fmodSFX->setScale(0.75);
		}
	}
};