#pragma once

template <typename input, typename output>
output Copy(input src_begin, input src_end, output dest) {
  while (src_begin != src_end) {
    *dest = *src_begin;
    ++src_begin;
    ++dest;
  }
  return dest;
}

template <typename input, typename output>
output CopyBackward(input src_begin, input src_end, output dest_end) {
  while (src_end != src_begin) {
    --src_end;
    --dest_end;
    *dest_end = *src_end;
  }
  return dest_end;
}