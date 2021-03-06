#include <inlow/kernel/filedescription.h>

FileDescription::FileDescription(Vnode* vnode)
{
	this->vnode = vnode;
	offset = 0;
}

FileDescription* FileDescription::openat(const char* path, int flags, mode_t mode)
{
	Vnode* node = vnode->openat(path, flags, mode);
	if (!node)
			return nullptr;
	return new FileDescription(node);
}

ssize_t FileDescription::read(void* buffer, size_t size)
{
		if (vnode->isSeekable())
		{
			ssize_t result = vnode->pread(buffer, size, offset);

			if (result != -1)
					offset += result;
			return result;
		}
	return vnode->read(buffer, size);
}

ssize_t FileDescription::readdir(unsigned long offset, void* buffer, size_t size)
{
	return vnode->readdir(offset, buffer, size);
}

int FileDescription::tcgetattr(struct termios* result)
{
	return vnode->tcgetattr(result);
}

int FileDescription::tcsetattr(int flags, const struct termios* termio)
{
	return vnode->tcsetattr(flags, termio);
}

ssize_t FileDescription::write(const void* buffer, size_t size)
{
	return vnode->write(buffer, size);
}
