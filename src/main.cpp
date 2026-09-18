#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class MyCustomPopup : public geode::Popup<> {
protected:
    bool setup() override {
        this->setTitle("OLO");

        auto photo = CCSprite::create("my_photo.png"_spr);
        if (photo) {
            photo->getTexture()->setAliasTexParameters();
            photo->setScale(95.0f / photo->getContentSize().width);
            photo->setPosition(m_mainLayer->getContentSize() / 2 + CCPoint{0, 10});
            m_mainLayer->addChild(photo);
        }

        return true;
    }

public:
    static MyCustomPopup* create() {
        auto ret = new MyCustomPopup();
        if (ret && ret->initAnchored(300, 220)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto buttonSprite = ButtonSprite::create("LOL");
        auto myButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyMenuLayer::onLolButtonClick)
        );

        myButton->setID("lol-button"_spr);

        auto bottomMenu = this->getChildByID("bottom-menu");
        if (bottomMenu) {
            bottomMenu->addChild(myButton);
            bottomMenu->updateLayout();
        }

        return true;
    }

    void onLolButtonClick(CCObject* sender) {
        auto popup = MyCustomPopup::create();
        if (popup) {
            popup->show();
        }
    }
};
