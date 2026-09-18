#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class SecretPopup : public FLAlertLayer {
public:
    static SecretPopup* create() {
        auto ret = new SecretPopup();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() {
        if (!FLAlertLayer::init(150)) return false;

        auto background = CCScale9Sprite::create("GJ_square01.png");
        background->setContentSize({ 280, 220 });
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        background->setPosition(winSize / 2);
        m_mainLayer->addChild(background);

        auto label = CCLabelBMFont::create("Hamburgaa", "bigFont.fnt");
        label->setScale(0.7f);
        label->setPosition(winSize / 2 + CCPoint{0, 75});
        m_mainLayer->addChild(label);

        auto photo = CCSprite::create("ballon.png"_spr);
        if (photo) {
            photo->getTexture()->setAliasTexParameters();
            photo->setScale(100.0f / photo->getContentSize().width);
            photo->setPosition(winSize / 2 + CCPoint{0, 10});
            m_mainLayer->addChild(photo);
        }

        auto okButtonSprite = ButtonSprite::create("OK");
        auto okButton = CCMenuItemSpriteExtra::create(
            okButtonSprite, this, menu_selector(SecretPopup::onClose)
        );
        auto menu = CCMenu::create();
        menu->addChild(okButton);
        menu->setPosition(winSize / 2 + CCPoint{0, -70});
        m_mainLayer->addChild(menu);

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);
        return true;
    }

    void onClose(CCObject* sender) {
        this->keyBackClicked();
    }
};

class MyCustomPopup : public FLAlertLayer {
public:
    static MyCustomPopup* create() {
        auto ret = new MyCustomPopup();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() {
        if (!FLAlertLayer::init(150)) return false;

        auto background = CCScale9Sprite::create("GJ_square02.png");
        background->setContentSize({ 300, 240 });
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        background->setPosition(winSize / 2);
        m_mainLayer->addChild(background);

        auto label = CCLabelBMFont::create("OLO", "bigFont.fnt");
        label->setScale(0.7f);
        label->setPosition(winSize / 2 + CCPoint{0, 85});
        m_mainLayer->addChild(label);

        auto frame = CCScale9Sprite::create("square02b_001.png");
        frame->setContentSize({ 140, 110 });
        frame->setPosition(winSize / 2 + CCPoint{0, 15});
        m_mainLayer->addChild(frame);

        auto photo = CCSprite::create("my_photo.png"_spr);
        if (photo) {
            photo->getTexture()->setAliasTexParameters();
            photo->setScale(120.0f / photo->getContentSize().width);
            photo->setPosition(frame->getContentSize() / 2);
            
            auto photoButton = CCMenuItemSpriteExtra::create(
                photo, this, menu_selector(MyCustomPopup::onPhotoClick)
            );
            auto photoMenu = CCMenu::create();
            photoMenu->addChild(photoButton);
            photoMenu->setPosition(winSize / 2 + CCPoint{0, 15});
            m_mainLayer->addChild(photoMenu);
        }

        auto okButtonSprite = ButtonSprite::create("OK");
        auto okButton = CCMenuItemSpriteExtra::create(
            okButtonSprite, this, menu_selector(MyCustomPopup::onClose)
        );
        auto menu = CCMenu::create();
        menu->addChild(okButton);
        menu->setPosition(winSize / 2 + CCPoint{0, -80});
        m_mainLayer->addChild(menu);

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);
        return true;
    }

    void onPhotoClick(CCObject* sender) {
        this->keyBackClicked();

        if (!Mod::get()->getSettingValue<bool>("secret-active")) {
            Mod::get()->setSettingValue("secret-active", true);
            FLAlertLayer::create("SECRET", "Secret Mode Activated!", "OK")->show();
        } else {
            auto secretPopup = SecretPopup::create();
            if (secretPopup) secretPopup->show();
        }
    }

    void onClose(CCObject* sender) {
        this->keyBackClicked();
    }
};

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        
        if (auto targetMenu = this->getChildByIDContainer("bottom-menu")) {
            if (!targetMenu->getChildByID("lol-button"_spr)) {
                bool isSecret = Mod::get()->getSettingValue<bool>("secret-active");
                auto buttonSprite = ButtonSprite::create(isSecret ? "OLO" : "LOL");
                auto myButton = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(MyMenuLayer::onLolClick));
                myButton->setID("lol-button"_spr);
                targetMenu->addChild(myButton);
                targetMenu->updateLayout();
            }
        }
        return true;
    }
    void onLolClick(CCObject* s) {
        auto p = MyCustomPopup::create();
        if (p) p->show();
    }
};

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {
    bool init(GJSearchObject* p0) {
        if (!LevelBrowserLayer::init(p0)) return false;

        if (auto targetMenu = this->getChildByIDContainer("back-menu")) {
            if (!targetMenu->getChildByID("lol-button"_spr)) {
                bool isSecret = Mod::get()->getSettingValue<bool>("secret-active");
                auto buttonSprite = ButtonSprite::create(isSecret ? "OLO" : "LOL");
                auto myButton = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(MyLevelBrowserLayer::onLolClick));
                myButton->setID("lol-button"_spr);
                targetMenu->addChild(myButton);
                targetMenu->updateLayout();
            }
        }
        return true;
    }
    void onLolClick(CCObject* s) {
        auto p = MyCustomPopup::create();
        if (p) p->show();
    }
};

class $modify(MyPauseLayer, PauseLayer) {
    bool init() {
        if (!PauseLayer::init()) return false;

        if (auto targetMenu = this->getChildByIDContainer("bottom-menu")) {
            if (!targetMenu->getChildByID("lol-button"_spr)) {
                bool isSecret = Mod::get()->getSettingValue<bool>("secret-active");
                auto buttonSprite = ButtonSprite::create(isSecret ? "OLO" : "LOL");
                auto myButton = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(MyPauseLayer::onLolClick));
                myButton->setID("lol-button"_spr);
                targetMenu->addChild(myButton);
                targetMenu->updateLayout();
            }
        }
        return true;
    }
    void onLolClick(CCObject* s) {
        auto p = MyCustomPopup::create();
        if (p) p->show();
    }
};
