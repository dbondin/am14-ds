#pragma once

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * Returns version/author of lzwy implementation
   */
  const char * lzwy_version();

  /**
   * Pack
   * - size - 9..16
   * - infile - input file
   * - outfile - output file (lzw)
   * Return value: 0 on success, not 0 on error
   */
  int lzwy_pack(int size, const char * infile, const char * outfile);

  /**
   * UnPack
   * - infile - input file (lzw)
   * - outfile - output file
   * Return value: 0 on success, not 0 on error
   */
  int lzwy_unpack(const char * infile, const char * outfile);

#ifdef __cplusplus
}
#endif
