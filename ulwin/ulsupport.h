#ifndef ULSUPPORT_H
#define ULSUPPORT_H

#include "../ulPlatform.h"
#include "../uldiscover.h"
#include "../MvErrorMap.h"

#ifdef MV_WINDOWS
#include "../ulenumwindows.h"
#include "../ulutilitieswindows.h"
#else
#include "../ulenumlinux.h"
#endif //MV_WINDOWS

#endif // ULSUPPORT_H
