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
    int get_character_type() const { return character_type_; }
    void set_character_type(int type) { character_type_ = type; }
   
    std::shared_ptr<server_session> get_session() const;

    int get_score() const { return score_; }

    void set_rank(int rank) { rank_ = rank; }
    int  get_rank() const { return rank_; }

    void start_shield_timer();

    unsigned int get_shield_time() const;

protected:
    std::weak_ptr<server_session> session_;

private:
    void update_score();
    void update_exp() const;
  
    int character_type_;
    int score_;
    int rank_;
    
    std::atomic<bool> shield_;

    std::chrono::milliseconds start_time_;

    std::chrono::milliseconds shield_time_;
    timer_ptr shield_timer_;
};

#endif
