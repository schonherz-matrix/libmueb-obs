#include <obs-module.h>
#include <util/base.h>

OBS_DECLARE_MODULE()

extern struct obs_output_info outputInfo;

bool obs_module_load(void) {
  blog(LOG_INFO, "[matrix-obs]: module_load");

  obs_register_output(&outputInfo);

  auto output = obs_output_create("matrix-obs-output", "matrix-obs-output",
                                  nullptr, nullptr);

  return true;
}
