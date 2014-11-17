#include "entitylist.h"

#include "entity.h"
#include "gfx/gfx.h"

bool colliding(Entity *entOne, Entity *entTwo) {
    double distX = entOne->position().X() - entTwo->position().X();
    double distY = entOne->position().Y() - entTwo->position().Y();
    double hypt = sqrt((distX * distX) + (distY * distY));
    return (hypt < entOne->shape().Radius() + entTwo->shape().Radius());
}

EntityList::EntityList() {

}

EntityList::~EntityList() {

}

void EntityList::add(Entity *entity) {
    entities.push_back(entity);
}

void EntityList::updateAll() {
    for (int i = entities.size() - 1; i >= 0; i--) {
        if (!entities.at(i)->update()) {
            delete entities.at(i);
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityList::checkCollisions(Entity &entity, function<void(Entity *)> callback) {
    for (int i = entities.size() - 1; i >= 0; i--) {
        if (colliding(entities.at(i), &entity)) {
            callback(entities.at(i));
            break;
        }
    }
}

void EntityList::checkCollisions(EntityList &otherList, function<void(Entity *, Entity *)> callback) {
    for (int i = entities.size() - 1; i >= 0; i--) {
        if (!(entities.at(i)->shape() == Shape::NONE || entities.at(i)->position() == Position::NONE)) {
            for (int j = otherList.size() - 1; j >= 0; j--) {
                if (colliding(entities.at(i), otherList.at(j))) {
                    callback(entities.at(i), otherList.at(j));
                    break;
                }
            }
        }
    }
}

void EntityList::clear() {
    for (int i = entities.size() - 1; i >= 0; i--) {
        delete entities.at(i);
        entities.erase(entities.begin() + i);
    }
}

void EntityList::renderAll(GfxWrapper *gfx) {
    for (int i = 0; i < entities.size(); i++) {
        entities.at(i)->render(gfx);
    }
}
