#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

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

        auto background = CCScale9Sprite::create("GJ_square01.png");
        background->setContentSize({ 260, 200 });
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        background->setPosition(winSize / 2);
        m_mainLayer->addChild(background);

        auto label = CCLabelBMFont::create("OLO", "bigFont.fnt");
        label->setScale(0.7f);
        label->setPosition(winSize / 2 + CCPoint{0, 65});
        m_mainLayer->addChild(label);

        auto photo = CCSprite::create("my_photo.png"_spr);
        if (photo) {
            photo->getTexture()->setAliasTexParameters();
            photo->setScale(60.0f / photo->getContentSize().width);
            photo->setPosition(winSize / 2 + CCPoint{0, 5});
            m_mainLayer->addChild(photo);
        }

        auto okButtonSprite = ButtonSprite::create("OK");
        auto okButton = CCMenuItemSpriteExtra::create(
            okButtonSprite,
            this,
            menu_selector(MyCustomPopup::onClose)
        );

        auto menu = CCMenu::create();
        menu->addChild(okButton);
        menu->setPosition(winSize / 2 + CCPoint{0, -60});
        m_mainLayer->addChild(menu);

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);

        return true;
    }

    void onClose(CCObject* sender) {
        this->keyBackClicked();
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
