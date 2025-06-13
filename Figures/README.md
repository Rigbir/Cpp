# Figures

`Figures` is an abstract base class for geometric shapes, providing a polymorphic interface for accessing core geometric properties and operations. Derived classes such as `Rectangle`, `Triangle`, and `Circle` implement methods for computing area, perimeter, scaling, angle information, centroid location, and point containment.

## Implemented Functionality

### Abstract Base Class: `Figures`

Defines the core interface for all geometric figures:

- `std::string name() const`  
  Returns the name of the figure (e.g., `"rectangle"`).

- `long double area() const`  
  Computes the area of the figure.

- `long double perimeter() const`  
  Computes the perimeter.

- `long double scale(double _scale)`  
  Scales the figure by a given factor.

- `std::string angles() const`  
  Returns a string representation of internal angles.

- `std::pair<long double, long double> centroid() const`  
  Returns the coordinates of the figure's centroid.

- `bool containsPointer(double x, double y) const`  
  Checks whether a given point lies within the figure. Default implementation returns `true`.

- `template <typename T> static long double pow(T value)`  
  Helper template method used internally for calculations.

- `virtual ~Figures() = default`  
  Virtual destructor to allow safe cleanup through base pointers.

---

### Derived Class: `Rectangle`

Represents a rectangle defined by its width and height.

- **Constructor**:  
  `explicit Rectangle(long double width, long double height)`

- **Area**:  
  `width * height`

- **Perimeter**:  
  `2 * (width + height)`

- **Centroid**:  
  Assumed to be at the center of the rectangle.

- **Angles**:  
  Always returns `90°, 90°, 90°, 90°`.

- **Point Containment**:  
  Checks if a given point lies within the rectangle (assuming axis-aligned rectangle centered at the origin).

---

### Derived Class: `Triangle`

Represents a triangle defined by three side lengths.

- **Constructor**:  
  `explicit Triangle(long double sideA, long double sideB, long double sideC)`

- **isValidTriangle() const**  
  Checks if triangle sides satisfy triangle inequality.

- **Area**:  
  Calculated using Heron's formula.

- **Perimeter**:  
  Sum of the three sides.

- **Angles**:  
  Computed using the Law of Cosines.

- **Centroid**:  
  Assumed to be the average of vertex coordinates.

---

### Derived Class: `Circle`

Represents a circle defined by its radius.

- **Constructor**:  
  `explicit Circle(long double radius)`

- **Area**:  
  `π * r²`

- **Perimeter**:  
  `2 * π * r`

- **Angles**:  
  Returns `"360°"`.

- **Centroid**:  
  Always at the center (origin).

- **Point Containment**:  
  Uses distance formula to check if a point lies within the radius.

---

### Factory Function: `createFigures`

Defined in `FiguresFactory.h`, it constructs a specific figure from an input stream.

Supported input:

```text
rectangle <width> <height>
triangle <sideA> <sideB> <sideC>
circle <radius>
```

Returns a `std::unique_ptr<Figures>`.

---

## Command-Line Interface

The main program includes an interactive text interface with the following commands:

| Command | Description |
|--------|-------------|
| `add` | Create a new figure using a supported type and parameters. |
| `print` | Display all figures and their properties. |
| `scale` | Scale all figures by user-defined factors. |
| `point` | Check whether a given point lies within any figure. |
| `end` | Exit the program. |

**Example usage:**

```text
add rectangle 3 5
add circle 2
add triangle 3 4 5
print
scale
point
end
```

---

