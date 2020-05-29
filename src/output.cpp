#include <obs.h>

#include "muebtransmitter.h"

extern struct obs_output_info outputInfo;

struct outputData {
  obs_output_t *output;
  MuebTransmitter *transmitter;

  obs_hotkey_id stop_hotkey;
  obs_hotkey_id start_hotkey;
};

void start_hotkey(void *param, obs_hotkey_id id, obs_hotkey_t *hotkey,
                  bool pressed) {
  UNUSED_PARAMETER(id);
  UNUSED_PARAMETER(hotkey);

  auto data = static_cast<outputData *>(param);

  if (pressed && !obs_output_active(data->output))
    obs_output_start(data->output);
}

void stop_hotkey(void *param, obs_hotkey_id id, obs_hotkey_t *hotkey,
                 bool pressed) {
  UNUSED_PARAMETER(id);
  UNUSED_PARAMETER(hotkey);

  auto data = static_cast<outputData *>(param);

  if (pressed && obs_output_active(data->output)) obs_output_stop(data->output);
}

const char *get_name(void *type_data) {
  UNUSED_PARAMETER(type_data);

  return "matrix-obs-output";
}

void *create(obs_data_t *settings, obs_output_t *output) {
  UNUSED_PARAMETER(settings);

  auto data = static_cast<outputData *>(bzalloc(sizeof(outputData)));

  data->output = output;
  data->transmitter = new MuebTransmitter;

  data->start_hotkey =
      obs_hotkey_register_output(output, "matrix-obs-output.start",
                                 "Start Mátrix output", start_hotkey, data);
  data->stop_hotkey =
      obs_hotkey_register_output(output, "matrix-obs-output.stop",
                                 "Stop Mátrix output", stop_hotkey, data);

  video_scale_info scale_info = {
      .format = VIDEO_FORMAT_RGBA,
      .width = static_cast<uint32_t>(libmueb::defaults::width),
      .height = static_cast<uint32_t>(libmueb::defaults::height),
      .range = VIDEO_RANGE_DEFAULT,
      .colorspace = VIDEO_CS_DEFAULT};

  obs_output_set_video_conversion(data->output, &scale_info);
  obs_output_set_preferred_size(data->output, libmueb::defaults::width,
                                libmueb::defaults::height);

  obs_video_info video_info;
  obs_get_video_info(&video_info);
  video_info.base_width = video_info.output_width = libmueb::defaults::width;
  video_info.base_height = video_info.output_height = libmueb::defaults::height;

  obs_reset_video(&video_info);

  return data;
}

bool start(void *param) {
  auto data = static_cast<outputData *>(param);

  if (obs_output_active(data->output)) return false;

  if (obs_output_can_begin_data_capture(data->output, OBS_OUTPUT_VIDEO))
    obs_output_begin_data_capture(data->output, OBS_OUTPUT_VIDEO);

  return true;
}

void stop(void *param, uint64_t ts) {
  UNUSED_PARAMETER(ts);
  auto data = static_cast<outputData *>(param);

  if (!obs_output_active(data->output)) return;

  obs_output_end_data_capture(data->output);
}

void raw_video(void *param, struct video_data *frame) {
  auto data = static_cast<outputData *>(param);

  // RGBA AV plane is 0
  data->transmitter->sendFrame(
      QImage(frame->data[0], obs_output_get_width(data->output),
             obs_output_get_height(data->output), frame->linesize[0],
             QImage::Format_RGBA8888));
}

void destroy(void *param) {
  auto data = static_cast<outputData *>(param);
  auto output = data->output;

  obs_output_release(output);

  delete data->transmitter;

  bfree(data);
}

struct obs_output_info outputInfo = {
    .id = "matrix-obs-output",
    .flags = OBS_OUTPUT_VIDEO | OBS_OUTPUT_CAN_PAUSE,
    .get_name = get_name,
    .create = create,
    .destroy = destroy,
    .start = start,
    .stop = stop,
    .raw_video = raw_video};
