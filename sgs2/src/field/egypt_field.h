#ifndef __EGYPT_FIELD_H
#define __EGYPT_FIELD_H

#include "field.h"

class egypt_field : public field
{
public:
    explicit egypt_field(unsigned int field_id);
    virtual ~egypt_field();

    void initialize() override;
    void update(float delta) override;
    void destroy() override;

    void sync_field(std::shared_ptr<server_session> session) const override;
    void respawn_character(object_id id) override;

protected:
    //virtual void process_task() override;
};

#endif
