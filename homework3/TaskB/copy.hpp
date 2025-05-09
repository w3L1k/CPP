#pragma once

template <typename Input, typename Output>
Output Copy(Input src_begin, Input src_end, Output dest) {
  while (src_begin != src_end) {
    *dest = *src_begin;
    ++src_begin;
    ++dest;
  }
  return dest;
}

template <typename Input, typename Output>
Output CopyBackward(Input src_begin, Input src_end, Output dest_end) {
  while (src_end != src_begin) {
    --src_end;
    --dest_end;
    *dest_end = *src_end;
  }
  return dest_end;
}