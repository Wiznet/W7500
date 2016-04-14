/*******************************************************************************************************************************************************
 * Copyright ¨Ï 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ¡°Software¡±), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED ¡°AS IS¡±, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
#define MIN(_a, _b) (_a < _b) ? _a : _b
#define MEM_FREE(mem_p) do{ if(mem_p) { free(mem_p); mem_p = NULL; } }while(0)	// ??
//#define BITSET(var_v, bit_v) SET_BIT(var_v, bit_v)	//(var_v |= bit_v)
//#define BITCLR(var_v, bit_v) CLEAR_BIT(var_v, bit_v)//(var_v &= ~(bit_v))

#define BUFFER_DEFINITION(_name, _size) \
	uint8_t _name##_buf[_size]; \
	volatile uint16_t _name##_wr=0; \
    volatile uint16_t _name##_rd=0; \
    volatile uint16_t _name##_sz=_size;
#define BUFFER_DECLARATION(_name) \
	extern uint8_t _name##_buf[]; \
	extern uint16_t _name##_wr, _name##_rd, _name##_sz;
#define BUFFER_CLEAR(_name) \
	_name##_wr=0;\
	_name##_rd=0;

#define BUFFER_USED_SIZE(_name) ((_name##_sz + _name##_wr - _name##_rd) % _name##_sz)
#define BUFFER_FREE_SIZE(_name) ((_name##_sz + _name##_rd - _name##_wr - 1) % _name##_sz)
#define IS_BUFFER_EMPTY(_name) ( (_name##_rd) == (_name##_wr))
#define IS_BUFFER_FULL(_name) (BUFFER_FREE_SIZE(_name) == 0)	// I guess % calc takes time a lot, so...
//#define IS_BUFFER_FULL(_name) ((_name##_rd!=0 && _name##_wr==_name##_rd-1)||(_name##_rd==0 && _name##_wr==_name##_sz-1))

#define BUFFER_IN(_name) _name##_buf[_name##_wr]
#define BUFFER_IN_OFFSET(_name, _offset) _name##_buf[_name##_wr + _offset]
#define BUFFER_IN_MOVE(_name, _num) _name##_wr = (_name##_wr + _num) % _name##_sz
#define BUFFER_IN_1ST_SIZE(_name) (_name##_sz - _name##_wr - ((_name##_rd==0)?1:0))
#define BUFFER_IN_2ND_SIZE(_name) ((_name##_rd==0) ? 0 : _name##_rd-1)
#define IS_BUFFER_IN_SEPARATED(_name) (_name##_rd <= _name##_wr)

#define BUFFER_OUT(_name) _name##_buf[_name##_rd]
#define BUFFER_OUT_OFFSET(_name, _offset) _name##_buf[_name##_rd + _offset]
#define BUFFER_OUT_MOVE(_name, _num) _name##_rd = (_name##_rd + _num) % _name##_sz
#define BUFFER_OUT_1ST_SIZE(_name) (_name##_sz - _name##_rd)
#define BUFFER_OUT_2ND_SIZE(_name) (_name##_wr)
#define IS_BUFFER_OUT_SEPARATED(_name) (_name##_rd > _name##_wr)
