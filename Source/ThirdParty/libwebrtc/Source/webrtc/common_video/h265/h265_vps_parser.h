/*
 *  Copyright (c) 2023 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef COMMON_VIDEO_H265_H265_VPS_PARSER_H_
#define COMMON_VIDEO_H265_H265_VPS_PARSER_H_

#include "absl/types/optional.h"
#include "api/array_view.h"

namespace webrtc {

// A class for parsing out video parameter set (VPS) data from an H265 NALU.
class H265VpsParser {
 public:
#if WEBRTC_WEBKIT_BUILD
    static constexpr uint32_t kMaxSubLayers = 7;
#endif

  // The parsed state of the VPS. Only some select values are stored.
  // Add more as they are actually needed.
  struct VpsState {
    VpsState();

    uint32_t id = 0;
#if WEBRTC_WEBKIT_BUILD
    uint32_t vps_max_sub_layers_minus1 = 0;
    uint32_t vps_max_num_reorder_pics[kMaxSubLayers] = {};
#endif
  };

  // Unpack RBSP and parse VPS state from the supplied buffer.
  static absl::optional<VpsState> ParseVps(const uint8_t* data, size_t length);

 protected:
  // Parse the VPS state, for a bit buffer where RBSP decoding has already been
  // performed.
  static absl::optional<VpsState> ParseInternal(
      rtc::ArrayView<const uint8_t> buffer);
};

}  // namespace webrtc
#endif  // COMMON_VIDEO_H265_H265_VPS_PARSER_H_
