#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

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
        auto alert = FLAlertLayer::create("OLO", " ", "OK");
        alert->show();

        auto mainLayer = alert->m_mainLayer;
        if (mainLayer) {
            auto photo = CCSprite::create("my_photo.png"_spr);
            if (photo) {
                photo->getTexture()->setAliasTexParameters();
                photo->setScale(95.0f / photo->getContentSize().width);
                
                auto winSize = CCDirector::sharedDirector()->getWinSize();
                photo->setPosition(winSize / 2 + CCPoint{0, 15});
                
                mainLayer->addChild(photo);
            }
        }
    }
};
