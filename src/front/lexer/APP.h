#ifndef _APP_H_
#define _APP_H_

#define SAFE_DELETE(x) { delete x; x = nullptr; }
#define SAFE_DELETEA(x) { delete[] x; x = nullptr; }

#endif
