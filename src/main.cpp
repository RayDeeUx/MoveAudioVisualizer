#include <Geode/modify/UILayer.hpp>

using namespace geode::prelude;

class $modify(MyUILayer, UILayer) {
	// bool init(GJBaseGameLayer*)
	bool init(GJBaseGameLayer* p0) {
		if (!UILayer::init(p0)) return false;
		if (!Mod::get()->getSettingValue<bool>("enabled")) return true;
		const auto pl = PlayLayer::get();
		const auto lel = LevelEditorLayer::get();
		if (!pl && !lel) return true;
		log::info("foo");
		if (!Mod::get()->getSettingValue<bool>("playLayer") && pl == p0) return true;
		if (!Mod::get()->getSettingValue<bool>("editorLayer") && lel == p0) return true;
		log::info("bar");
		auto fmodMusic = this->getChildByType<FMODLevelVisualizer>(0);
		auto fmodSFX = this->getChildByType<FMODLevelVisualizer>(1);
		if (!fmodMusic || !fmodSFX) return true;
		log::info("baz");
		MyUILayer::repositionMusicAndSFX(fmodMusic, fmodSFX);
		return true;
	}
	void repositionMusicAndSFX(FMODLevelVisualizer* fmodMusic, FMODLevelVisualizer* fmodSFX) {
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