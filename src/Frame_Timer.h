#include <chrono>
#include <iostream>


template<class c_t>
class frame_timer
{
public:

    using clock_t = c_t;
    using duration_t = typename clock_t::duration;
    using time_point_t = typename clock_t::time_point;

    template<class d_t>
    explicit frame_timer(d_t initial_last_frame_time) :
        m_last_frame_time(std::chrono::duration_cast<duration_t>(initial_last_frame_time)),
        m_last_tick(clock_t::now()) { }

    void tick()
    {
        auto now = clock_t::now();
        m_last_frame_time = now - m_last_tick;
        m_last_tick = now;
    }

    duration_t get_last_frame_time() const
    {
        return m_last_frame_time;
    }

private:

    duration_t m_last_frame_time;
    time_point_t m_last_tick;
};
