#include "toGraphics.hpp"

static std::vector<std::pair<float, float>> to_points(size_t x, size_t y) {
  std::vector<std::pair<float, float>> res;
  size_t m = ((x > y) ? x : y);
  float k = 1.0f / (float)m;
  for (size_t i = 0; i < (y + 1); ++i) {
    for (size_t j = 0; j < (x + 1); ++j) {
      float fx = (k * (j * 2)) - 1.0f;
      float fy = (k * (i * 2)) - 1.0f;
      res.push_back(std::make_pair(fx, fy)); // [0](x-1 ; y-1), [1](x-0.5, y-1)
    }
  }
  return res;
}

#if 0
struct rgb { float r; float g; float b; };
#endif

static rgb to_rgb(size_t a) {
  switch (a) {
    { case 0: return { 0.1f, 0.1f, 0.1f }; } // is a default field colour
    { case 1: return { 0.9f, 0.9f, 0.9f }; } // boarders
    { case 2: return { 0.1f, 0.97f, 0.1f }; } // apple
    { case 3: return { 0.64f, 0.64f, 0.1f }; } // tail 999900
    { case 4: return { 0.92f, 0.92f, 0.1f }; } // head CCCC00
    { default: std::cout << "Convertion Failed!\n"; }
  }
  return {1.0f, 0.0f, 0.0f};
}

static std::vector<rgb> to_color(std::vector<size_t>& field, size_t x, size_t y) {
  std::vector<rgb> res;
  size_t res_size = ((x + 1) * (y + 1));
  res.resize(res_size);
  for (size_t i = 0; i < y; ++i) {
    for (size_t j = 0; j < x; ++j) {
      size_t dotc = j + (i * x);
      size_t c = field[dotc];
      rgb z = to_rgb(c);
      res[dotc] = z;
      res[dotc + 1] = z;
      res[dotc + y + 2] = z;
      res[dotc + y + 1] = z;
    };
  };
  // z is color val; ij*x) - is a squre of snake
  return res;
}

static rgb gen_rgb() {
  float r = get_random();
  float g = get_random();
  float b = get_random();
  return { r, g ,b };
}

static std::vector<rgb> gen_color(size_t x, size_t y) {
  std::vector<rgb> res;
  res.resize(((x + 1) * (y + 1)));
  rgb color = gen_rgb();
  size_t ctr = 0;
  for (rgb& a : res) {
    if (!(ctr % x)) {
      color = gen_rgb();
    }
    a = color;
  }
  return res;
}

static std::vector<Vertex> to_vertices(std::vector<std::pair<float, float>>& dots, std::vector<rgb>& color) {
  if (dots.size() != color.size()) { dbgs << "Error | buffer | colour.size != dots.size \n"; }
  std::vector<Vertex> res;
  auto cb = color.begin();
  for (std::pair<float, float>& dot : dots) {
    float r = 0.1f, g = 0.1f, b = 0.1f;
    Vertex a = { {dot.first, dot.second}, { ((*cb).r), ((*cb).g), ((*cb).b) } };
    res.push_back(a);
    ++cb;
  }
  return res;
}

static void push_indic(std::vector<unsigned short>& res, unsigned i, unsigned x) {
  res.push_back(i);
  res.push_back(i + 1);
  res.push_back(i + x + 2);
  res.push_back(i + x + 2);
  res.push_back(i + x + 1);
  res.push_back(i);
}

static std::vector<unsigned short> to_indices(size_t x, size_t y) {
  std::vector<unsigned short> res;

#if 1
  size_t tmp = (x);
  push_indic(res, 0, x);
  for (unsigned i = 1; i < (x * (y + 1)); ++i) {
    if (!(i % tmp)) {
      tmp += (x + 1);
      continue;
    }
    push_indic(res, i, x);
  }
#endif

  return res;
}

static void prtv(std::vector<Vertex>& vert, std::vector<unsigned short>& ind) {
  size_t ctr = 0;
  for (Vertex& a : vert) {
    dbgs << ctr << " | " << a.pos.x << " ; " << a.pos.y
      // << " | " << " {" << a.color.r << ", " << a.color.g << ", " << a.color.b << " | "
      << "\n";
    ++ctr;
  };

  ctr = 0;
  for (auto x : ind) {
    if (!(ctr % 6)) { std::cout << "\n  "; }
    dbgs << x << " ";
    ++ctr;
  }
  std::cout << std::endl;
}

void setup_VaI(size_t size_x, size_t size_y, std::vector<size_t>& field) {
  // background in squares  
  auto indices = to_indices(size_x, size_y);
  auto points = to_points(size_x, size_y);
  auto colors = to_color(field, size_x, size_y); // gen_color(size_x, size_y));
  auto vertices = to_vertices(points, colors);
  // prtv(Vertices, Indices);
}