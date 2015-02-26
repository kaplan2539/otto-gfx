#pragma once

#include <VG/openvg.h>

#include <string>

#include "nanosvg.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat3x3.hpp"

namespace otto {

enum Align {
  // Horizontal
  ALIGN_LEFT   = 1 << 0,
  ALIGN_CENTER = 1 << 1,
  ALIGN_RIGHT  = 1 << 2,

  // Vertical
  ALIGN_TOP      = 1 << 3,
  ALIGN_MIDDLE   = 1 << 4,
  ALIGN_BOTTOM   = 1 << 5,
  ALIGN_BASELINE = 1 << 6
};

struct Rect {
  glm::vec2 pos, size;
};

using Svg = NSVGimage;

void strokePaint(const NSVGpaint &svgPaint, float opacity = 1.0f);
void fillPaint(const NSVGpaint &svgPaint, float opacity = 1.0f);

void strokeColor(float r, float g, float b, float a = 1.0f);
void strokeColor(const glm::vec4 &color);
void strokeColor(const glm::vec3 &color);
void strokeColor(uint32_t color);
void fillColor(float r, float g, float b, float a = 1.0f);
void fillColor(const glm::vec4 &color);
void fillColor(const glm::vec3 &color);
void fillColor(uint32_t color);

void strokeWidth(VGfloat width);
void strokeCap(VGCapStyle cap);
void strokeJoin(VGJoinStyle join);

void moveTo(VGPath path, float x, float y);
void lineTo(VGPath path, float x, float y);
void cubicTo(VGPath path, float x1, float y1, float x2, float y2, float x3, float y3);
void arc(VGPath path, float x, float y, float w, float h, float startAngle, float endAngle);
void rect(VGPath path, float x, float y, float width, float height);
void roundRect(VGPath path, float x, float y, float width, float height, float radius);

void beginPath();

void moveTo(float x, float y);
void moveTo(const glm::vec2 &pos);
void lineTo(float x, float y);
void lineTo(const glm::vec2 &pos);
void cubicTo(float x1, float y1, float x2, float y2, float x3, float y3);
void cubicTo(const glm::vec2 &p1, const glm::vec2 p2, const glm::vec2 &p3);
void arc(float cx, float cy, float w, float h, float angleStart, float angleEnd);
void arc(const glm::vec2 &ctr, const glm::vec2 &size, float angleStart, float angleEnd);
void circle(float cx, float cy, float radius);
void circle(const glm::vec2 &ctr, float radius);
void rect(float x, float y, float width, float height);
void rect(const glm::vec2 &pos, const glm::vec2 &size);
void rect(const Rect &r);
void roundRect(float x, float y, float width, float height, float radius);
void roundRect(const glm::vec2 &pos, const glm::vec2 &size, float radius);
void roundRect(const Rect &r, float radius);

void fillRuleEvenOdd();
void fillRuleNonZero();

void fill();
void stroke();
void fillAndStroke();

void clearColor(float r, float g, float b, float a = 1.0f);
void clearColor(const glm::vec4 &color);
void clearColor(const glm::vec3 &color);
void clear(int x, int y, int w, int h);

void draw(const Svg &svg, bool flipY = true);
void draw(const Svg *svg, bool flipY = true);

void setColorTransform(float sr, float sg, float sb, float sa,
                       float br, float bg, float bb, float ba);
void setColorTransform(const glm::vec4 &scale, const glm::vec4 &bias);
void enableColorTransform();
void disableColorTransform();

void pushMask(int width, int height);
void popMask();
void beginMask();
void endMask();
void enableMask();
void disableMask();
void fillMask(int x, int y, int width, int height);
void clearMask(int x, int y, int width, int height);
void maskOperation(VGMaskOperation operation);

void pushTransform();
void popTransform();
void setTransform(const glm::mat3 &xf);
void setTransformIdentity();
const glm::mat3 getTransform();

void translate(const glm::vec2 &vec);
void translate(float x, float y);
void rotate(float radians);
void scale(const glm::vec2 &vec);
void scale(float x, float y);
void scale(float s);

Svg *loadSvg(const std::string &path, const std::string &units = "px", float dpi = 96);
void loadFont(const std::string &path);

void fontSize(float size);
void textAlign(uint32_t align);
void fillText(const std::string &text);

Rect getTextBounds(const std::string &text);

struct Noncopyable {
protected:
  Noncopyable() = default;
  ~Noncopyable() = default;

  Noncopyable(const Noncopyable &) = delete;
  Noncopyable &operator=(const Noncopyable &) = delete;
};

struct ScopedTransform : private Noncopyable {
  ScopedTransform() { pushTransform(); }
  ~ScopedTransform() { popTransform(); }
};

struct ScopedMask : private Noncopyable {
  ScopedMask(int width, int height) { pushMask(width, height); }
  ~ScopedMask() { popMask(); }
};

} // otto
