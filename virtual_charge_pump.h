
/*
 * Copyright (c) 2018 Kiss Adam <email>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef VIRTUAL_CHARGE_PUMP_H
#define VIRTUAL_CHARGE_PUMP_H

#include <stddef.h>
#include <array>
#include "siso.h"
#include <limits>

/**
 * @todo write docs
 */

//TODO changeble time constant

template<typename input_type = unsigned int, typename storagetype = float, unsigned int delay = 60> //delay: how many samples to do discharging after
class charge_pump : public siso<input_type, storagetype>
{
private:    
    storagetype out;
    unsigned int counter;
public:
    /**
     * @todo write docs
     */
    virtual const storagetype& pull() /*noexcept*/ override;
    virtual void put(const input_type& sample) override;
    
    charge_pump();
    
    void reset() noexcept;
};

template<typename input_type, typename storagetype, unsigned int delay> const storagetype& charge_pump<input_type, storagetype, delay>::pull()
{
    return out;
}

template<typename input_type, typename storagetype, unsigned int delay> charge_pump<input_type, storagetype, delay>::charge_pump()
{    
    out     = 0;
    counter = delay;
}

template <typename input_type, typename storagetype, unsigned int delay>
void charge_pump<input_type, storagetype, delay>::put(const input_type& sample)
{
    if(out<sample)
        out=sample;
    else{
        counter--;
        if(counter == 0){
            out*=0.99;
            counter = delay;
        }
    }
}

template<typename input_type, typename storagetype, unsigned int delay> void charge_pump<input_type, storagetype, delay>::reset() noexcept
{
    out  = std::numeric_limits<storagetype>::min();
    counter = delay;
}


#endif // VIRTUAL_CHARGE_PUMP_H
