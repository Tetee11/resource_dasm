#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <deque>
#include <phosg/Encoding.hh>
#include <phosg/Filesystem.hh>
#include <phosg/Image.hh>
#include <phosg/Strings.hh>
#include <string>

#include "ImageSaver.hh"
#include "QuickDrawEngine.hh"
#include "ResourceFile.hh"

using namespace std;

enum ColorFormat {
  GRAY1 = 0,
  GRAY2,
  GRAY4,
  GRAY8,
  RGBX5551,
  XRGB1555,
  RGB565,
  RGB888,
  XRGB8888,
  ARGB8888,
  RGBX8888,
  RGBA8888,
  INDEXED,
};

ColorFormat color_format_for_name(const char* name) {
  if (!strcmp(name, "1")) {
    return ColorFormat::GRAY1;
  } else if (!strcmp(name, "grayscale1")) {
    return ColorFormat::GRAY1;
  } else if (!strcmp(name, "2")) {
    return ColorFormat::GRAY2;
  } else if (!strcmp(name, "grayscale2")) {
    return ColorFormat::GRAY2;
  } else if (!strcmp(name, "4")) {
    return ColorFormat::GRAY4;
  } else if (!strcmp(name, "grayscale4")) {
    return ColorFormat::GRAY4;
  } else if (!strcmp(name, "8")) {
    return ColorFormat::GRAY8;
  } else if (!strcmp(name, "grayscale8")) {
    return ColorFormat::GRAY8;
  } else if (!strcmp(name, "rgbx5551")) {
    return ColorFormat::RGBX5551;
  } else if (!strcmp(name, "xrgb1555")) {
    return ColorFormat::XRGB1555;
  } else if (!strcmp(name, "rgb565")) {
    return ColorFormat::RGB565;
  } else if (!strcmp(name, "rgb888")) {
    return ColorFormat::RGB888;
  } else if (!strcmp(name, "xrgb8888")) {
    return ColorFormat::XRGB8888;
  } else if (!strcmp(name, "argb8888")) {
    return ColorFormat::ARGB8888;
  } else if (!strcmp(name, "rgbx8888")) {
    return ColorFormat::RGBX8888;
  } else if (!strcmp(name, "rgba8888")) {
    return ColorFormat::RGBA8888;
  } else {
    throw out_of_range("invalid color format");
  }
}

size_t bits_for_format(ColorFormat format) {
  switch (format) {
    case ColorFormat::GRAY1:
      return 1;
    case ColorFormat::GRAY2:
      return 2;
    case ColorFormat::GRAY4:
      return 4;
    case ColorFormat::GRAY8:
      return 8;
    case ColorFormat::RGBX5551:
    case ColorFormat::XRGB1555:
    case ColorFormat::RGB565:
      return 16;
    case ColorFormat::RGB888:
      return 24;
    case ColorFormat::XRGB8888:
    case ColorFormat::ARGB8888:
    case ColorFormat::RGBX8888:
    case ColorFormat::RGBA8888:
      return 32;
    case ColorFormat::INDEXED:
      throw logic_error("indexed color format does not have a fixed width");
    default:
      throw out_of_range("invalid color format");
  }
}

bool color_format_has_alpha(ColorFormat format) {
  return (format == ColorFormat::ARGB8888) || (format == ColorFormat::RGBA8888);
}

static void print_usage() {
  fprintf(stderr, "\
Usage: render_bits [options] [input_filename [output_filename_without_extension]]\n\
\n\
If you actually want to run with all default options, give --bits=1.\n\
\n\
If no filenames are given, read from stdin and write to stdout. You should\n\
redirect stdout to a file because it will contain binary data which will\n\
probably goof up your terminal if it happens to contain escape codes.\n\
\n\
If an input filename is given but no output filename is given, render_bits will\n\
write to a file named <input_filename>.<image ext>.\n\
\n\
The output width and height will be automatically computed. You can override\n\
this by giving --width, --height, or both. Usually only --width is sufficient\n\
(and most useful by itself since most images are stored in row-major order).\n\
\n\
Options:\n\
  --width=N\n\
      Output an image with this many pixels per row.\n\
  --height=N\n\
      Output an image with this many pixels per column.\n\
  --bits=FORMAT\n\
      Specify the input data format. Formats are 1, 2, 4, or 8 (grayscale),\n\
      xrgb1555, rgbx5551, rgb565, rgb888, xrgb8888, argb8888, rgbx8888, and\n\
      rgba8888. Ignored if --clut-file is given.\n\
  --clut-file=FILENAME\n\
      Use this clut (.bin file exported by resource_dasm) to map channel values\n\
      to colors.\n\
  --default-clut\n\
      Use the Mac OS default 256-color clut.\n\
  --little-endian\n\
      For color formats larger than 8 bits per pixel, treat input values as\n\
      little-endian (the default is big-endian).\n\
  --offset=N\n\
      Ignore this many bytes at the beginning of the input. You can use this to\n\
      skip data that looks like the file\'s header.\n\
  --parse\n\
      Expect input in text format, and parse it using phosg\'s standard data\n\
      format. Use this if you have e.g. a hex string and you want to paste it\n\
      into your terminal.\n\
\n" IMAGE_SAVER_HELP);
}

int main(int argc, char* argv[]) {
  bool parse = false;
  size_t offset = 0;
  size_t w = 0, h = 0;
  ColorFormat color_format = ColorFormat::GRAY1;
  bool little_endian = false;
  bool column_major = false;
  bool use_default_clut = false;
  const char* input_filename = nullptr;
  const char* output_filename = nullptr;
  const char* clut_filename = nullptr;
  ImageSaver image_saver;
  for (int x = 1; x < argc; x++) {
    if (!strcmp(argv[x], "--help")) {
      print_usage();
      return 0;
    } else if (!strncmp(argv[x], "--width=", 8)) {
      w = strtoull(&argv[x][8], nullptr, 0);
    } else if (!strncmp(argv[x], "--height=", 9)) {
      h = strtoull(&argv[x][9], nullptr, 0);
    } else if (!strncmp(argv[x], "--bits=", 7)) {
      color_format = color_format_for_name(&argv[x][7]);
    } else if (!strncmp(argv[x], "--clut-file=", 12)) {
      clut_filename = &argv[x][12];
      color_format = ColorFormat::INDEXED;
    } else if (!strcmp(argv[x], "--default-clut")) {
      use_default_clut = true;
      color_format = ColorFormat::INDEXED;
    } else if (!strcmp(argv[x], "--little-endian")) {
      little_endian = true;
    } else if (!strcmp(argv[x], "--column-major")) {
      column_major = true;
    } else if (!strncmp(argv[x], "--offset=", 9)) {
      offset = strtoull(&argv[x][9], nullptr, 0);
    } else if (!strcmp(argv[x], "--parse")) {
      parse = true;
    } else if (image_saver.process_cli_arg(argv[x])) {
      // Nothing
    } else if (!input_filename) {
      input_filename = argv[x];
    } else if (!output_filename) {
      output_filename = argv[x];
    } else {
      fprintf(stderr, "invalid or excessive option: %s\n", argv[x]);
      print_usage();
      return 2;
    }
  }

  string in_data = input_filename ? load_file(input_filename) : read_all(stdin);
  if (parse) {
    in_data = parse_data_string(in_data);
  }
  if (offset) {
    in_data = in_data.substr(offset);
  }

  vector<ColorTableEntry> clut;
  size_t pixel_bits;
  if (use_default_clut) {
    clut = create_default_clut();
    pixel_bits = 8;
  } else if (clut_filename) {
    string clut_data = load_file(clut_filename);
    clut = ResourceFile::decode_clut(clut_data.data(), clut_data.size());
    if (clut.empty()) {
      throw invalid_argument("clut is empty");
    }
    if (clut.size() & (clut.size() - 1)) {
      fprintf(stderr, "warning: clut size is not a power of 2; extending with black\n");
      while (clut.size() & (clut.size() - 1)) {
        auto entry = clut.emplace_back();
        entry.color_num = clut.size() - 1;
        entry.c = Color(0, 0, 0);
      }
    }
    for (pixel_bits = 0;
         clut.size() != static_cast<size_t>(1 << pixel_bits);
         pixel_bits++) {
    }
  } else {
    pixel_bits = bits_for_format(color_format);
  }
  size_t pixel_count = (in_data.size() * 8) / pixel_bits;

  if (w == 0 && h == 0) {
    double z = sqrt(pixel_count);
    if (z != floor(z)) {
      w = z + 1;
    } else {
      w = z;
    }
    h = w;

  } else if (h == 0) {
    h = pixel_count / w;
    if (h * w < pixel_count) {
      h++;
    }

  } else if (w == 0) {
    w = pixel_count / h;
    if (h * w < pixel_count) {
      w++;
    }
  }

  BitReader br(in_data);
  StringReader sr(in_data);
  deque<uint32_t> pixel_stream;
  for (size_t z = 0; z < pixel_count; z++) {
    switch (color_format) {
      case ColorFormat::GRAY1:
        // Note: This is the opposite of what you'd expect for other formats
        // (1 is black, 0 is white). We do this because it seems to be the
        // common behavior on old Mac OS.
        pixel_stream.emplace_back(br.read(1) ? 0x000000FF : 0xFFFFFFFF);
        break;

      case ColorFormat::GRAY2: {
        static const uint32_t colors[4] = {
            0x000000FF, 0x555555FF, 0xAAAAAAFF, 0xFFFFFFFF};
        pixel_stream.emplace_back(colors[br.read(2)]);
        break;
      }

      case ColorFormat::GRAY4: {
        static const uint32_t colors[16] = {
            0x000000FF,
            0x111111FF,
            0x222222FF,
            0x333333FF,
            0x444444FF,
            0x555555FF,
            0x666666FF,
            0x777777FF,
            0x888888FF,
            0x999999FF,
            0xAAAAAAFF,
            0xBBBBBBFF,
            0xCCCCCCFF,
            0xDDDDDDFF,
            0xEEEEEEFF,
            0xFFFFFFFF,
        };
        pixel_stream.emplace_back(colors[br.read(4)]);
        break;
      }

      case ColorFormat::GRAY8: {
        uint8_t v = sr.get_u8();
        pixel_stream.emplace_back((v << 24) | (v << 16) | (v << 8) | 0xFF);
        break;
      }

      case ColorFormat::INDEXED: {
        Color8 c = clut.at(br.read(pixel_bits)).c.as8();
        pixel_stream.emplace_back((c.r << 24) | (c.g << 16) | (c.b << 8) | 0xFF);
        break;
      }

      case ColorFormat::RGBX5551: {
        uint16_t pixel = little_endian ? sr.get_u16l() : sr.get_u16b();
        uint8_t r = ((pixel >> 8) & 0xF8) | ((pixel >> 13) & 0x07);
        uint8_t g = ((pixel >> 3) & 0xF8) | ((pixel >> 8) & 0x07);
        uint8_t b = ((pixel << 2) & 0xF8) | ((pixel >> 3) & 0x07);
        pixel_stream.emplace_back((r << 24) | (g << 16) | (b << 8) | 0xFF);
        break;
      }

      case ColorFormat::XRGB1555: {
        uint16_t pixel = little_endian ? sr.get_u16l() : sr.get_u16b();
        uint8_t r = ((pixel >> 7) & 0xF8) | ((pixel >> 12) & 0x07);
        uint8_t g = ((pixel >> 2) & 0xF8) | ((pixel >> 7) & 0x07);
        uint8_t b = ((pixel << 3) & 0xF8) | ((pixel >> 2) & 0x07);
        pixel_stream.emplace_back((r << 24) | (g << 16) | (b << 8) | 0xFF);
        break;
      }

      case ColorFormat::RGB565: {
        uint16_t pixel = little_endian ? sr.get_u16l() : sr.get_u16b();
        uint8_t r = ((pixel >> 8) & 0xF8) | ((pixel >> 13) & 0x07);
        uint8_t g = ((pixel >> 3) & 0xFC) | ((pixel >> 9) & 0x03);
        uint8_t b = ((pixel << 2) & 0xF8) | ((pixel >> 2) & 0x07);
        pixel_stream.emplace_back((r << 24) | (g << 16) | (b << 8) | 0xFF);
        break;
      }

      case ColorFormat::RGB888: {
        uint16_t pixel = little_endian ? sr.get_u24l() : sr.get_u24b();
        pixel_stream.emplace_back((pixel << 8) | 0xFF);
        break;
      }

      case ColorFormat::XRGB8888: {
        uint16_t pixel = little_endian ? sr.get_u32l() : sr.get_u32b();
        pixel_stream.emplace_back((pixel << 8) | 0xFF);
        break;
      }

      case ColorFormat::ARGB8888: {
        uint16_t pixel = little_endian ? sr.get_u32l() : sr.get_u32b();
        pixel_stream.emplace_back(((pixel << 8) & 0xFFFFFF00) | ((pixel >> 24) & 0xFF));
        break;
      }

      case ColorFormat::RGBX8888: {
        uint16_t pixel = little_endian ? sr.get_u32l() : sr.get_u32b();
        pixel_stream.emplace_back(pixel | 0xFF);
        break;
      }

      case ColorFormat::RGBA8888: {
        uint16_t pixel = little_endian ? sr.get_u32l() : sr.get_u32b();
        pixel_stream.emplace_back(pixel);
        break;
      }

      default:
        fprintf(stderr, "invalid color format");
        return 1;
    }
  }

  if (pixel_stream.size() < w * h) {
    fprintf(stderr, "warning: not enough pixels (%zu) to fill %zux%zu image (%zu required)", pixel_stream.size(), w, h, w * h);
  }

  Image img;
  if (column_major) {
    img = Image(w, h, color_format_has_alpha(color_format));
    for (size_t x = 0; x < w && !pixel_stream.empty(); x++) {
      for (size_t y = 0; y < h && !pixel_stream.empty(); y++) {
        img.write_pixel(x, y, pixel_stream.front());
        pixel_stream.pop_front();
      }
    }
  } else {
    img = Image(w, h, color_format_has_alpha(color_format));
    for (size_t y = 0; y < h && !pixel_stream.empty(); y++) {
      for (size_t x = 0; x < w && !pixel_stream.empty(); x++) {
        img.write_pixel(x, y, pixel_stream.front());
        pixel_stream.pop_front();
      }
    }
  }

  if (output_filename) {
    (void)image_saver.save_image(img, output_filename);
  } else if (input_filename) {
    (void)image_saver.save_image(img, input_filename);
  } else {
    image_saver.save_image(img, stdout);
  }

  return 0;
}
