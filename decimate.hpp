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

#ifndef DECIMATE_HPP
#define DECIMATE_HPP

#include <stddef.h>
#include <array>
#include "siso.h"

/**
 * @todo write docs
 */
template<unsigned int decimate_factor, typename input_type = unsigned int, typename storagetype = float>
class decimate : public siso<input_type, storagetype>
{
private:
    storagetype sum;
    size_t samples;
public:
    /**
     * @todo write docs
     */
    virtual storagetype pull() /*noexcept*/ override;
    virtual void put(input_type sample) override;
    
    /*virtual*/ bool outavailable();
    
    decimate();
    
    void reset() noexcept;
};

//TODO what if I write all the code in the class declaration?

template<unsigned int decimate_factor, typename input_type, typename storagetype> storagetype decimate<decimate_factor, input_type, storagetype>::pull()
{
    ///TODO finish
    /*if(samples!=decimate_factor-1)
        throw ...;*/
    this->reset();
    return this->sum/this->samples;
}

template<unsigned int decimate_factor, typename input_type, typename storagetype> decimate<decimate_factor, input_type, storagetype>::decimate()
{
    this->sum=0;
    this->samples=0;
}

template<unsigned int decimate_factor, typename input_type, typename storagetype> void decimate<decimate_factor, input_type, storagetype>::put(input_type data)
{
    this->sum+=data;
    samples++;
}

template<unsigned int decimate_factor, typename input_type, typename storagetype> void decimate<decimate_factor, input_type, storagetype>::reset() noexcept
{
    this->sum=0;
    this->samples=0;
}

template<unsigned int decimate_factor, typename input_type, typename storagetype> bool decimate<decimate_factor, input_type, storagetype>::outavailable()
{
    return samples==decimate_factor-1;
}


#endif // DECIMATE_HPP
