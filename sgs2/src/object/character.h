#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "object.h"

#include "../component/movement/move_component.h"
#include "../component/skill/skill_component.h"

class server_session;

class character : public object
{
public:

    explicit character(field_id id, std::shared_ptr<server_session> session);
    ~character();

    void initialize() override;
    void update(float delta) override;

    void destroy() override;

    void leave_field() const;
    void respawn(const vector3& spawn_pos);

    //void set_type(
   
    std::shared_ptr<server_session> get_session() const;

protected:
    std::weak_ptr<server_session> session_;
    
};

#endif
