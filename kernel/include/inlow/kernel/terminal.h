#ifndef KERNEL_TERMINAL_H
#define KERNEL_TERMINAL_H

#include <inlow/termios.h>
#include <inlow/kernel/keyboard.h>
#include <inlow/kernel/vnode.h>

#define TERMINAL_BUFFER_SIZE 4096

class TerminalBuffer
{
	public:
			TerminalBuffer();
			size_t available();
			bool backspace();
			char read();
			void reset();
			void write(char c, bool canonicalMode);
	private:
			char circularBuffer[TERMINAL_BUFFER_SIZE];
			volatile size_t readIndex;
			volatile size_t lineIndex;
			volatile size_t writeIndex;
};

class Terminal : public Vnode, public KeyboardListener
{
	public:
			Terminal();
			virtual ssize_t read(void* buffer, size_t size);
			virtual int tcgetattr(struct termios* result);
			virtual int tcsetattr(int flags, const struct termios* termios);
			virtual ssize_t write(const void* buffer, size_t size);
	private:
			virtual void onKeyboardEvent(int key);
	private:
			TerminalBuffer terminalBuffer;
			struct termios termio;
};

extern Terminal terminal;

#endif
