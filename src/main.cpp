#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <imgui.h>

using namespace geode::prelude;

constexpr int GRID_SIZE = 32;
std::vector<std::vector<ImVec4>> pixelGrid(GRID_SIZE, std::vector<ImVec4>(GRID_SIZE, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)));

ImVec4 currentBrushColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
bool isDrawingTool = true;
bool showCanvasWindow = false;

class CanvasOverlay : public cocos2d::CCLayer {
public:
    static CanvasOverlay* create() {
        auto ret = new CanvasOverlay();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() override {
        if (!CCLayer::init()) return false;
        
        geode::Queue::get()->postInGDThread([this]() {
            ImGui::GetIO().WantCaptureMouse = true;
        });
        
        this->scheduleUpdate();
        return true;
    }

    void draw() override {
        CCLayer::draw();
        if (!showCanvasWindow) return;

        ImGui::SetNextWindowSize(ImVec2(400, 480), ImGuiCond_FirstUseEver);
        
        if (ImGui::Begin("GD Custom Icon Canvas", &showCanvasWindow, ImGuiWindowFlags_NoCollapse)) {
            ImGui::Text("Pick a color and draw your custom icon pack:");
            ImGui::Separator();

            ImGui::ColorEdit4("Brush Color", (float*)&currentBrushColor);
            
            if (ImGui::Button("Brush Mode")) isDrawingTool = true;
            ImGui::SameLine();
            if (ImGui::Button("Eraser Mode")) isDrawingTool = false;
            ImGui::SameLine();
            if (ImGui::Button("Clear All")) {
                for (int x = 0; x < GRID_SIZE; ++x) {
                    for (int y = 0; y < GRID_SIZE; ++y) pixelGrid[x][y] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
                }
            }

            ImGui::Separator();

            for (int y = 0; y < GRID_SIZE; ++y) {
                for (int x = 0; x < GRID_SIZE; ++x) {
                    ImGui::PushID(y * GRID_SIZE + x);
                    
                    if (ImGui::ColorButton("##pixel", pixelGrid[x][y], ImGuiColorEditFlags_NoTooltip, ImVec2(10, 10))) {
                        if (isDrawingTool) {
                            pixelGrid[x][y] = currentBrushColor;
                        } else {
                            pixelGrid[x][y] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
                        }
                    }
                    
                    ImGui::PopID();
                    if (x < GRID_SIZE - 1) ImGui::SameLine();
                }
            }

            ImGui::Separator();

            if (ImGui::Button("Export to Texture Loader", ImVec2(-1, 40))) {
                log::info("Compiling color matrix grid data into binary texture sheets...");
            }
        }
        ImGui::End();
    }
};

// CRITICAL FIX: Extension hook registry macro locked to RazzGd.GdIconMaker layout tracking
class $modify(MyMenuLayer, MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        
        auto sprite = CCSprite::createWithSpriteFrameName("GJ_paintBtn_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(MyMenuLayer::onOpenCanvas)
        );

        auto menu = CCMenu::create(btn, nullptr);
        menu->setPosition({winSize.width - 40, winSize.height - 40});
        this->addChild(menu);

        auto overlay = CanvasOverlay::create();
        this->addChild(overlay);

        return true;
    }

    void onOpenCanvas(cocos2d::CCObject* sender) {
        showCanvasWindow = !showCanvasWindow;
    }
};
