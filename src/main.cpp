#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

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

class $modify(MyPlayLayer, PlayLayer) {
	bool init(GJGameLevel* p0, bool p1, bool p2) {
		if (!PlayLayer::init(p0, p1, p2)) return false;
		if (!Mod::get()->getSettingValue<bool>("enabled")) return true;
		if (!Mod::get()->getSettingValue<bool>("playLayer")) return true;
		auto uiLayer = getChildByID("UILayer");
		if (!uiLayer) return true;
		auto fmodMusic = uiLayer->getChildByType<FMODLevelVisualizer>(0);
		auto fmodSFX = uiLayer->getChildByType<FMODLevelVisualizer>(1);
		if (!fmodMusic || !fmodSFX) return true;
		repositionMusicAndSFX(fmodMusic, fmodSFX);
		return true;
	}
};

class $modify(MyLevelEditorLayer, LevelEditorLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelEditorLayer::init(p0, p1)) return false;
		if (!Mod::get()->getSettingValue<bool>("enabled")) return true;
		if (!Mod::get()->getSettingValue<bool>("editorLayer")) return true;
		auto uiLayer = getChildByID("UILayer");
		if (!uiLayer) return true;
		auto fmodMusic = uiLayer->getChildByType<FMODLevelVisualizer>(0);
		auto fmodSFX = uiLayer->getChildByType<FMODLevelVisualizer>(1);
		if (!fmodMusic || !fmodSFX) return true;
		repositionMusicAndSFX(fmodMusic, fmodSFX);
		return true;
	}
};