#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {}

    // TODO: all of these:

    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow) { 
        return mViewCenterWorld + (pWindow-mWindowSize/2.f)*mWorldUnitsPerPixel; 
    };

    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld) {
        return (pWorld-mViewCenterWorld)/mWorldUnitsPerPixel +mWindowSize/2.f;
     };

    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent) { 
        sf::Vector2f world(pWindowPercent.x*mWindowSize.x, pWindowPercent.y*mWindowSize.y);
        return windowToWorld(world);
     };

    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld) {
        sf::Vector2f window = worldToWindow(pWorld);
        return {window.x/mWindowSize.x, window.y/mWindowSize.y};
     };

    void translateWorld(const sf::Vector2f& deltaWorld) {
        mViewCenterWorld += deltaWorld;
    };

    void translateWindow(const sf::Vector2f& deltaScreen) {
        translateWorld(deltaScreen*mWorldUnitsPerPixel);
    };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) {
        translateWindow({deltaScreenPercent.x*mWindowSize.x, deltaScreenPercent.y*mWindowSize.y});
    };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) {
        mViewCenterWorld = pWorld-(pWindow-mWindowSize/2.f) *mWorldUnitsPerPixel;
    };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) {
        setCamera(pWorld, {pWindowPercent.x*mWindowSize.x, pWindowPercent.y*mWindowSize.y});
    };

    void setCameraCenter(const sf::Vector2f& pWorld) {
        mViewCenterWorld = pWorld;
    };

    sf::Vector2f getCameraCenter() const { 
        return mViewCenterWorld;
    };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
