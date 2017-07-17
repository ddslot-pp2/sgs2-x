#ifndef __BULLET_H
#define __BULLET_H
#include "../../../../../core/src/util/vector3.h"
#include "../../../predeclare.h"

class object;
class character;

class bullet
{
public:

    enum class type : int { default_bullet = 0 };

    static auto int_to_type(int v) { return static_cast<type>(v); }


    explicit bullet(object* obj, const vector3& dir, const vector3& size, float speed, float distance, float power);
    virtual ~bullet();

    virtual void update(float delta);
    virtual void destroy() const;

    virtual void collide_with_other(std::shared_ptr<character> target_object);

    bool get_destroy() const { return destroy_; }
    void set_bullet_id(bullet_id id);

    bool over_distance() const;
    bool check_intersection(const vector3& bullet_pos, const vector3& other_pos, const vector3& bullet_size, const vector3& other_size) const;

    bool collide_with_collider();

    object* object_;
    vector3 from_;
    vector3 pos_;
    vector3 dir_;
    vector3 size_;
    float speed_;
    float distance_;
    float power_;

    bool destroy_;
    bullet_id id_;
};

#endif
