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

#ifndef RMS_COUNTER_H
#define RMS_COUNTER_H

#include <stddef.h>
#include <array>
#include <math.h>
#include "siso.h"

/**
 * @todo write docs
 */
template<size_t width, typename input_type = unsigned int, typename storagetype = float>
class rms_counter : public siso<input_type, storagetype>
{
private:
    std::array<input_type, width> buff2;
    storagetype currMS;
    storagetype currRMS;
    typename std::array<input_type, width>::iterator i;
public:
    /**
     * @todo write docs
     */
    const storagetype& getRMS();
    const storagetype& getMS() /*const noexcept*/; //TODO fix noexcept keyword if allowable
    virtual void put(const input_type& data) /*override*/;
    virtual const storagetype& pull() /*override*/; //TODO fix override keyword
    
    rms_counter();
};

template<size_t width, typename input_type, typename storagetype>
const storagetype& rms_counter<width, input_type, storagetype>::getMS()
{
    return this->currMS;
}

template<size_t width, typename input_type, typename storagetype>
const storagetype& rms_counter<width, input_type, storagetype>::pull()
{
    
    return this->currRMS;
}

template<size_t width, typename input_type, typename storagetype>
const storagetype& rms_counter<width, input_type, storagetype>::getRMS()
{
    currRMS = storagetype(sqrt((this->currMS/width))); 
    return currRMS;
}

template<size_t width, typename input_type, typename storagetype>
void rms_counter<width, input_type, storagetype >::put(const input_type& data)
{
    this->currMS-=(*i);
    (*i)=(storagetype)data*(storagetype)data;
    currMS+=(*i);
    i++;
    if( i == buff2.end())
        i=buff2.begin();
}

template<size_t width, typename input_type, typename storagetype> rms_counter<width, input_type, storagetype>::rms_counter()
{
    currMS=0;
    buff2.fill(0);
    i=buff2.begin();
}

#endif // RMS_COUNTER_H

