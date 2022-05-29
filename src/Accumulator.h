#include <chrono>
#include <iostream>

template<class c_t>
class accumulator
{
public:

    using clock_t = c_t;
    using duration_t = typename clock_t::duration;

    template<class d_t>
    explicit accumulator(d_t tick_length) :
        m_tick_length(std::chrono::duration_cast<duration_t>(tick_length)) { }

    std::size_t accumulate(duration_t delta_time) // note: returns the number of ticks of m_tick_length triggered by this call
    {
        m_accumulated_time += delta_time;

        auto ticks = std::size_t{ 0 };

        while (m_accumulated_time >= m_tick_length)
        {
            ++ticks;
            m_accumulated_time -= m_tick_length;
        }

        return ticks;
    }

    duration_t get_tick_length() const
    {
        return m_tick_length;
    }

private:

    duration_t m_tick_length;
    duration_t m_accumulated_time;
};