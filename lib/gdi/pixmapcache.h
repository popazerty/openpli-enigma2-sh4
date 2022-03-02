#ifndef __pixmapcache_h
#define __pixmapcache_h

#include <lib/gdi/gpixmap.h>

<<<<<<< HEAD
=======
#ifndef __GLIBC__
#include <sys/types.h>
#endif

>>>>>>> 4cf2ad3c93680791dc065098aeaec5f28fef9daf
#ifndef SWIG

class PixmapCache
{
private:
	static uint MaximumSize;
public:
	static void PixmapDisposed(gPixmap *pixmap);
	static gPixmap* Get(const char *filename);
	static void Set(const char *filename, gPixmap *pixmap);
};

#endif

#endif
