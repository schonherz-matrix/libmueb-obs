#include <obs-module.h>
#include <util/base.h>

#include "output.h"

OBS_DECLARE_MODULE()

bool obs_module_load(void) {
  blog(LOG_INFO, "[matrix-obs]: module_load");

  if (!create_output()) return false;

  return true;
}
