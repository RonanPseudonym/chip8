#include <stdexcept>

class Stack {
	private:
		unsigned short stack[256];

		int n;
		int top;
	public:
		Stack() {
			n = 256;
			top = -1;
		}

		void push(unsigned short val) {
			if (top >= n - 1) {
				throw std::overflow_error("Stack Overflow");
			} else {
				top ++;
				stack[top] = val;
			}
		}

		void pop() {
			if (top <= -1) {
				throw std::underflow_error("Stack Underflow");
			} else {
				top --;
			}
		}
};