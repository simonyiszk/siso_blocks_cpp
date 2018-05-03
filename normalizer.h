
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

#ifndef NORMALIZER_H
#define NORMALIZER_H

#include <stddef.h>
#include <array>
#include "siso.h"
#include <limits>

/**
 * @todo write docs
 */
template<typename input_type = unsigned int, typename storagetype = float>
class normalizer : public siso<input_type, storagetype>
{
private:
    storagetype min, max;
    
    storagetype out;
public:
    /**
     * @todo write docs
     */
    virtual const storagetype& pull() /*noexcept*/ override;
    virtual void put(const input_type& sample) override;
    
    const storagetype& getMin();
    const storagetype& getMax();
    
    normalizer();
    
    void reset() noexcept;
};

template<typename input_type, typename storagetype> const storagetype & normalizer<input_type, storagetype>::getMax()
{
    return max;
}

template<typename input_type, typename storagetype> const storagetype & normalizer<input_type, storagetype>::getMin()
{
    return min;
}



template<typename input_type, typename storagetype> const storagetype& normalizer<input_type, storagetype>::pull()
{
    return out;
}

template<typename input_type, typename storagetype> normalizer<input_type, storagetype>::normalizer()
{
    min  = std::numeric_limits<storagetype>::max();
    max  = std::numeric_limits<storagetype>::min();
    
    out  = 0;
}

template <typename input_type, typename storagetype>
void normalizer<input_type, storagetype>::put(const input_type& sample)
{
    if(max<sample)
        max=sample;
    
    if(min>sample)
        min=sample;
    
    out  = 100*(sample - min)/(max-min);
}

template<typename input_type, typename storagetype> void normalizer<input_type, storagetype>::reset() noexcept
{
    min  = std::numeric_limits<storagetype>::max();
    max  = std::numeric_limits<storagetype>::min();
}


#endif // NORMALIZER_H
