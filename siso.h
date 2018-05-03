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

#ifndef siso_h_included__i_like_pencakes
#define siso_h_included__i_like_pencakes

template<typename input_type, typename output_type>
class siso{
public:    
    siso() = default;
    
    virtual void put(const input_type& sample) = 0;
    virtual const output_type& pull() = 0;
    /*virtual bool outavailable() = 0; */
    
    siso& operator>>(siso& target){
        target.put(this->pull());
        return target;
    }
    
    void operator>>(output_type* result){
        *result = this->pull();
    }
    
    virtual ~siso() = default;
    //TODO delete copy constructor
};

//TODO Fix this optimization
//maybe add other types: https://gcc.gnu.org/onlinedocs/gcc/x86-Function-Attributes.html#x86-Function-Attributes
/*
#ifdef __amd64__
template<typename input_type, double> __attribute__ ((sseregparm)) void siso<input_type, double>::put(const input_type& sample) = 0;
template<typename input_type, float> __attribute__ ((sseregparm)) void siso<input_type, double>::put(const input_type& sample) = 0;
#endif //i386 detection
*/

#endif //siso_h_included__i_like_pencakes
