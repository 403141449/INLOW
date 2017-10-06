#ifndef KERNEL_PROCESS_H
#define KERNEL_PROCESS_H

#include <inlow/kernel/addressspace.h>
#include <inlow/kernel/interrupts.h>

class Process
{
	public:
			Process();
	private:
			AddressSpace* addressSpace;
			InterruptContext* interruptContext;
			Process* next;
			void* stack;

	public:
			static void initialize();
			static InterruptContext* schedule(InterruptContext* context);
			static Process* startProcess(void* entry);
};


#endif
