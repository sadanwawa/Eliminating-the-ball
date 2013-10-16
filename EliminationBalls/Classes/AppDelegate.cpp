#include "AppDelegate.h"
#include "MainScene.h"
#include "ResourceManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* director = Director::getInstance();
    EGLView* eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);
    
    eglView->setDesignResolutionSize(designResolutionSize.height, designResolutionSize.width, ResolutionPolicy::SHOW_ALL);
    
    director->setContentScaleFactor(iphone4HDResource.size.height/designResolutionSize.height);
    
    
	
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / (60));
    //随机 种子 设置
    srand((unsigned)(time(NULL)));
    UIManager::Instance()->initialize();
    
    // create a scene. it's an autorelease object
    Scene *scene = MainScene::scene();
    // run
    director->runWithScene(scene);    
    
    // init main scene
//    MainScene *pScene = MainScene::create();
//    ccColor3B transitionColor;
//    transitionColor.r = 0;
//    transitionColor.g = 0;
//    transitionColor.b = 0;
//        
//    Director::getInstance()->runWithScene(TransitionFade::create(0.5f, pScene,transitionColor));
//    
//    pScene->release();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
