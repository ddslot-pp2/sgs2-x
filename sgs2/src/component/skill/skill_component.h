#ifndef __SKILL_COMPONENT_H
#define __SKILL_COMPONENT_H

#include "../component.h"
#include <map>
#include "../../../../core/src/util/vector3.h"
#include "bullet/bullet.h"

class skill_component : public component
{
public:
    explicit skill_component(object* obj);
    virtual ~skill_component();

    void update(float delta) override;
    void destroy() override;

    void reset() override;


    void fire(bullet::type type, const vector3& pos, const vector3& dir, const vector3& bullet_dir);
    void noti_fire(bullet::type type, object_id obj_id, bullet_id bullet_obj_id, const vector3& pos, const vector3& bullet_dir, const vector3& dir, const vector3& size, float speed, float distance) const;

    void volley_fire(bullet::type type, const vector3& pos, const vector3& dir, int count, const std::array<vector3, max_volley_count>& dirs);
    void noti_volley_fire(bullet::type type, object_id obj_id, std::array<bullet_id, max_volley_count> bullet_obj_ids, const vector3& pos, const vector3& dirs, int count, const std::array<vector3, max_volley_count>& bullet_dirs, const std::array<vector3, max_volley_count>& sizes, float speed, float distance) const;

private:
    std::map<bullet_id, std::unique_ptr<bullet>> bullets_;
};

#endif
