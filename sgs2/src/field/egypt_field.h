#ifndef __EGYPT_FIELD_H
#define __EGYPT_FIELD_H

#include "field.h"

class egypt_field : public field
{
public:
    explicit egypt_field(unsigned int field_id);
    virtual ~egypt_field();

    virtual void initialize() override;
    virtual void update(float delta) override;

    

protected:
    //virtual void process_task() override;
};

#endif
