# Qt Oscillogram Viewer – Interactive Signal Visualization

This project is a Qt-based GUI application that displays a vertical bar chart (oscillogram-style) of signal amplitudes. It features interactive selection using the mouse and renders dynamically added data points.

## 🎯 Features

- Displays a real-time-like **bar graph** of up to 450 data points
- Enables **click-and-drag selection** using the mouse
- Custom coordinate system with centered origin and scalable viewport
- Optimized painting using `QPainter` and `QPen`
- Differentiates selected data with alternate color
- Built with **Qt Widgets** (no OpenGL or QML required)

## 🧱 Core Concepts

- Custom `paintEvent()` rendering logic using Qt’s painting API
- Manipulation of painter’s **viewport**, **window**, and **clipping region**
- Selection rendering based on mouse events and coordinate mapping
- Properties for `selectionStart` and `selectionEnd`, using Qt's `Q_PROPERTY` and `signals`

## 🛠️ How It Works

1. **Points Generation**:
   - The `main.cpp` populates 450 pseudo-random data points via `addPoint()`

2. **Rendering**:
   - A rounded black border is drawn using `drawRoundedRect`
   - Red baseline is drawn at the vertical midpoint
   - Blue bars represent amplitude; selected bars are highlighted in white

3. **Interaction**:
   - Mouse press sets the starting index of the selection
   - Mouse drag updates the end of the selection in real time
   - Selections are handled and drawn with `drawSelection()`

## 📦 File Structure

- `widget.h/.cpp`: Contains the custom QWidget with drawing and event logic
- `main.cpp`: Launches the application and feeds in initial data

## 📸 Screenshot (optional)

> _Include a screenshot here of the rendered chart with a selection highlighted._

## 🧪 Use Cases

- Simple signal or audio visualization
- Teaching basic data plotting and user interaction in Qt
- Custom data editors or graph-based dashboards

## 🛠️ Requirements

- Qt 5.7+ (compatible with other Qt 5.x versions)
- C++11 or newer
- Compiles on Windows, Linux, or macOS

## 📄 License

No restrictions

---

> Designed for clarity, responsiveness, and hands-on graphics programming with Qt.
