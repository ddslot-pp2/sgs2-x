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

    void leave_field() const;
   
    std::shared_ptr<server_session> get_session() const;

    void check_destroy();

protected:
    std::weak_ptr<server_session> session_;
   
};

#endif
