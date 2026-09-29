# 2D Geometric Transformations — Lab Documentation

**M.Sc. (Computer Science) - Semester I Computer Graphics Laboratory**  
**Assignment No. 3: Basic Two-Dimensional Transformations (Translation, Scaling, Rotation, Reflection, and Shearing)**

---

## 1. Introduction & Theoretical Foundation

In 2D computer graphics, transformations are used to manipulate vertices and display objects in different positions, orientations, and sizes. Using standard Cartesian coordinates $(x, y)$, a linear transformation (scaling, rotation, shearing, reflection) can be represented by a $2 \times 2$ matrix:

$$\begin{bmatrix} x' \\ y' \end{bmatrix} = \begin{bmatrix} a & b \\ c & d \end{bmatrix} \begin{bmatrix} x \\ y \end{bmatrix}$$

However, translation is an affine transformation that involves vector addition ($x' = x + t_x, y' = y + t_y$) and **cannot** be expressed as a $2 \times 2$ matrix multiplication. To unify all affine transformations into a single matrix multiplication pipeline, **homogeneous coordinates** are introduced:

$$\begin{bmatrix} x \\ y \end{bmatrix} \implies \begin{bmatrix} x \\ y \\ 1 \end{bmatrix}$$

Each 2D transformation is represented as a $3 \times 3$ matrix:

$$\begin{bmatrix} x' \\ y' \\ 1 \end{bmatrix} = \begin{bmatrix} m_{11} & m_{12} & m_{13} \\ m_{21} & m_{22} & m_{23} \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} x \\ y \\ 1 \end{bmatrix}$$

This allows multiple successive transformations to be composed via matrix multiplication into a single composite matrix.

---

## 2. Test Objects

As specified in the assignment test data:

1. **Triangle** (Used for Translation, Scaling, Rotation, and Reflection):
   - Vertices: $A(20, 20)$, $B(60, 20)$, $C(40, 60)$
   - In homogeneous coordinates:
     $$\begin{bmatrix} 20 & 20 & 1 \\ 60 & 20 & 1 \\ 40 & 60 & 1 \end{bmatrix}$$

2. **Square** (Used for Shearing):
   - Vertices: $P(10, 10)$, $Q(50, 10)$, $R(50, 50)$, $S(10, 50)$
   - In homogeneous coordinates:
     $$\begin{bmatrix} 10 & 10 & 1 \\ 50 & 10 & 1 \\ 50 & 50 & 1 \\ 10 & 50 & 1 \end{bmatrix}$$

---

# Part 1: Basic Transformations (`basic_transformation.py`)

---

## Transformation 1: Translation

### 1. Parameters

- Horizontal translation: $t_x = 30$
- Vertical translation: $t_y = 25$
- Target Object: Triangle $A(20, 20)$, $B(60, 20)$, $C(40, 60)$

### 2. Homogeneous Transformation Matrix

$$T(t_x, t_y) = \begin{bmatrix} 1 & 0 & t_x \\ 0 & 1 & t_y \\ 0 & 0 & 1 \end{bmatrix} = \begin{bmatrix} 1 & 0 & 30 \\ 0 & 1 & 25 \\ 0 & 0 & 1 \end{bmatrix}$$

### 3. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ | Mathematical Formulation |
| :---: | :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(50, 45)$ | $x' = 20 + 30 = 50,\; y' = 20 + 25 = 45$ |
| **B** | $(60, 20)$ | $(90, 45)$ | $x' = 60 + 30 = 90,\; y' = 20 + 25 = 45$ |
| **C** | $(40, 60)$ | $(70, 85)$ | $x' = 40 + 30 = 70,\; y' = 60 + 25 = 85$ |

### 4. Console Output

```text
Transformation Matrix:------
 [[ 1  0 30]
 [ 0  1 25]
 [ 0  0  1]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[50 45  1]
 [90 45  1]
 [70 85  1]]
```

### 5. Output Figure

![1. Translation](1.%20translation.png)

> **Observation / Geometric Note:**  
> The translation transformation shifts every vertex rigidly by $+30$ units along the X-axis and $+25$ units along the Y-axis. The triangle retains its original size, internal angles, orientation, and perimeter/area (isometry/rigid motion).

---

## Transformation 2: Scaling About the Origin

### 1. Parameters

- Scale factors: $s_x = 2.0$, $s_y = 1.5$
- Scaling Center: Origin $(0, 0)$
- Target Object: Triangle $A(20, 20)$, $B(60, 20)$, $C(40, 60)$

### 2. Homogeneous Transformation Matrix

$$S(s_x, s_y) = \begin{bmatrix} s_x & 0 & 0 \\ 0 & s_y & 0 \\ 0 & 0 & 1 \end{bmatrix} = \begin{bmatrix} 2.0 & 0 & 0 \\ 0 & 1.5 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

### 3. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ | Mathematical Formulation |
| :---: | :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(40.0, 30.0)$ | $x' = 20 \times 2.0 = 40,\; y' = 20 \times 1.5 = 30$ |
| **B** | $(60, 20)$ | $(120.0, 30.0)$ | $x' = 60 \times 2.0 = 120,\; y' = 20 \times 1.5 = 30$ |
| **C** | $(40, 60)$ | $(80.0, 90.0)$ | $x' = 40 \times 2.0 = 80,\; y' = 60 \times 1.5 = 90$ |

### 4. Console Output

```text
Transformation Matrix:------
 [[2.  0.  0. ]
 [0.  1.5 0. ]
 [0.  0.  1. ]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[ 40.  30.   1.]
 [120.  30.   1.]
 [ 80.  90.   1.]]
```

### 5. Output Figure

![2. Scaling](2.%20scaling.png)

> **Observation / Geometric Note:**  
> The object undergoes non-uniform scaling relative to the origin $(0, 0)$. The horizontal coordinates double ($s_x = 2.0$), while the vertical coordinates are multiplied by $1.5$ ($s_y = 1.5$). Because the fixed point is the origin rather than the triangle's centroid, the triangle also moves farther outward into the first quadrant.

---

## Transformation 3: Uniform vs. Differential Scaling

### 3.1 Uniform Scaling ($s_x = 2.0$, $s_y = 2.0$)

#### 1. Parameters & Matrix

$$S(2.0, 2.0) = \begin{bmatrix} 2.0 & 0 & 0 \\ 0 & 2.0 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ |
| :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(40.0, 40.0)$ |
| **B** | $(60, 20)$ | $(120.0, 40.0)$ |
| **C** | $(40, 60)$ | $(80.0, 120.0)$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[2. 0. 0.]
 [0. 2. 0.]
 [0. 0. 1.]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[ 40.  40.   1.]
 [120.  40.   1.]
 [ 80. 120.   1.]]
```

#### 4. Output Figure

![3.1 Uniform Scaling](3.1%20uniform%20scaling.png)

> **Observation / Geometric Note:**  
> Because $s_x = s_y = 2.0$, the triangle's aspect ratio and angles are strictly preserved. The transformed triangle is geometrically similar to the original triangle, with twice the edge lengths and four times the area ($A' = s_x s_y A = 4A$).

---

### 3.2 Differential Scaling ($s_x = 2.0$, $s_y = 0.5$)

#### 1. Parameters & Matrix

$$S(2.0, 0.5) = \begin{bmatrix} 2.0 & 0 & 0 \\ 0 & 0.5 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ |
| :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(40.0, 10.0)$ |
| **B** | $(60, 20)$ | $(120.0, 10.0)$ |
| **C** | $(40, 60)$ | $(80.0, 30.0)$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[2.  0.  0. ]
 [0.  0.5 0. ]
 [0.  0.  1. ]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[ 40.  10.   1.]
 [120.  10.   1.]
 [ 80.  30.   1.]]
```

#### 4. Output Figure

![3.2 Differential Scaling](3.2%20differential%20scaling.png)

> **Observation / Geometric Note:**  
> Differential scaling uses unequal scaling factors ($s_x = 2.0 \neq s_y = 0.5$). The triangle is stretched horizontally to twice its width while being compressed vertically to half its height. This alters internal angles and distorts the proportions of the original object.

---

## Transformation 4: Rotation About the Origin

### 4.1 Rotation by 45°

#### 1. Parameters & Matrix

- Rotation Angle: $\theta = 45^\circ$
- Center of rotation: $(0, 0)$

$$R(45^\circ) = \begin{bmatrix} \cos 45^\circ & -\sin 45^\circ & 0 \\ \sin 45^\circ & \cos 45^\circ & 0 \\ 0 & 0 & 1 \end{bmatrix} = \begin{bmatrix} \frac{\sqrt{2}}{2} & -\frac{\sqrt{2}}{2} & 0 \\ \frac{\sqrt{2}}{2} & \frac{\sqrt{2}}{2} & 0 \\ 0 & 0 & 1 \end{bmatrix} \approx \begin{bmatrix} 0.707107 & -0.707107 & 0 \\ 0.707107 & 0.707107 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original $(x, y)$ | Transformed $(x', y')$ | Exact Expression |
| :---: | :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(0.0000, 28.2843)$ | $(20\cos 45^\circ - 20\sin 45^\circ,\; 20\sin 45^\circ + 20\cos 45^\circ) = (0, 20\sqrt{2})$ |
| **B** | $(60, 20)$ | $(28.2843, 56.5685)$ | $(60\cos 45^\circ - 20\sin 45^\circ,\; 60\sin 45^\circ + 20\cos 45^\circ) = (20\sqrt{2}, 40\sqrt{2})$ |
| **C** | $(40, 60)$ | $(-14.1421, 70.7107)$ | $(40\cos 45^\circ - 60\sin 45^\circ,\; 40\sin 45^\circ + 60\cos 45^\circ) = (-10\sqrt{2}, 50\sqrt{2})$ |

*(Note: Floating-point precision evaluates $20\cos 45^\circ - 20\sin 45^\circ$ as $\approx 1.78 \times 10^{-15} \approx 0.0$)*

#### 3. Console Output

```text
Transformation Matrix:------
 [[ 0.70710678 -0.70710678  0.        ]
 [ 0.70710678  0.70710678  0.        ]
 [ 0.          0.          1.        ]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[ 1.77635684e-15  2.82842712e+01  1.00000000e+00]
 [ 2.82842712e+01  5.65685425e+01  1.00000000e+00]
 [-1.41421356e+01  7.07106781e+01  1.00000000e+00]]
```

#### 4. Output Figure

![4.1 Rotate 45 Degree](4.1%20rotate%2045%20degree.png)

> **Observation / Geometric Note:**  
> The triangle rotates counterclockwise around the origin $(0, 0)$ by $45^\circ$. Vertex $A(20, 20)$, which lies on the line $y = x$ at angle $45^\circ$, rotates to the positive Y-axis at $(0, 28.28)$. All distances from the origin to each vertex remain constant ($r' = r$).

---

### 4.2 Multiple Rotations (30°, 60°, 90°, 180°) on One Figure

In `basic_transformation.py`, multiple rotations are executed sequentially:

1. $r_{\text{seq1}} = R(30^\circ) \cdot \text{triangle}$
2. $r_{\text{seq2}} = R(60^\circ) \cdot r_{\text{seq1}}$ (Cumulative angle: $30^\circ + 60^\circ = 90^\circ$)
3. $r_{\text{seq3}} = R(90^\circ) \cdot r_{\text{seq2}}$ (Cumulative angle: $90^\circ + 90^\circ = 180^\circ$)
4. $r_{\text{seq4}} = R(180^\circ) \cdot r_{\text{seq3}}$ (Cumulative angle: $180^\circ + 180^\circ = 360^\circ \equiv 0^\circ$)

#### 1. Sequential Coordinate Table

| Transformation Stage | Input Points | Transformed Points | Net Cumulative Angle |
| :---: | :---: | :---: | :---: |
| **Step 1 ($30^\circ$)** | $(20, 20), (60, 20), (40, 60)$ | $(7.32, 27.32), (41.96, 47.32), (4.64, 71.96)$ | $30^\circ$ |
| **Step 2 ($+60^\circ$)** | $(7.32, 27.32), (41.96, 47.32), (4.64, 71.96)$ | $(-20.0, 20.0), (-20.0, 60.0), (-60.0, 40.0)$ | $90^\circ$ |
| **Step 3 ($+90^\circ$)** | $(-20.0, 20.0), (-20.0, 60.0), (-60.0, 40.0)$ | $(-20.0, -20.0), (-60.0, -20.0), (-40.0, -60.0)$ | $180^\circ$ |
| **Step 4 ($+180^\circ$)** | $(-20.0, -20.0), (-60.0, -20.0), (-40.0, -60.0)$ | $(20.0, 20.0), (60.0, 20.0), (40.0, 60.0)$ | $360^\circ \equiv 0^\circ$ |

*(Note: If each angle is evaluated independently from the original triangle as listed in `transformation_docs.docx`: at $60^\circ$, vertices are $(-7.32, 27.32), (12.68, 61.96), (-31.96, 64.64)$).*

#### 2. Console Output

```text
Transformation Matrix:------
 [[ 0.8660254 -0.5        0.       ]
 [ 0.5        0.8660254  0.       ]
 [ 0.         0.         1.       ]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[ 7.32050808 27.32050808  1.        ]
 [41.96152423 47.32050808  1.        ]
 [ 4.64101615 71.96152423  1.        ]]

Transformation Matrix:------
 [[ 0.5       -0.8660254  0.       ]
 [ 0.8660254  0.5        0.       ]
 [ 0.         0.         1.       ]]
Original points:------
 [[ 7.32050808 27.32050808  1.        ]
 [41.96152423 47.32050808  1.        ]
 [ 4.64101615 71.96152423  1.        ]]
Transformed points:------
 [[-20.  20.   1.]
 [-20.  60.   1.]
 [-60.  40.   1.]]

Transformation Matrix:------
 [[ 6.123234e-17 -1.000000e+00  0.000000e+00]
 [ 1.000000e+00  6.123234e-17  0.000000e+00]
 [ 0.000000e+00  0.000000e+00  1.000000e+00]]
Original points:------
 [[-20.  20.   1.]
 [-20.  60.   1.]
 [-60.  40.   1.]]
Transformed points:------
 [[-20. -20.   1.]
 [-60. -20.   1.]
 [-40. -60.   1.]]

Transformation Matrix:------
 [[-1.0000000e+00 -1.2246468e-16  0.0000000e+00]
 [ 1.2246468e-16 -1.0000000e+00  0.0000000e+00]
 [ 0.0000000e+00  0.0000000e+00  1.0000000e+00]]
Original points:------
 [[-20. -20.   1.]
 [-60. -20.   1.]
 [-40. -60.   1.]]
Transformed points:------
 [[20. 20.  1.]
 [60. 20.  1.]
 [40. 60.  1.]]
```

#### 3. Output Figure

![4.2 Multiple Rotations](4.2%20Multiple%20rotations%2030-60-90-180.png)

> **Observation / Geometric Note:**  
> The combined plot demonstrates the additive nature of rotation matrices:
> $$R(\theta_1) \cdot R(\theta_2) = R(\theta_1 + \theta_2)$$
> The successive rotations sweep the triangle across Quadrant I ($30^\circ$), Quadrant II ($90^\circ$), Quadrant III ($180^\circ$), and finally complete a full circle back to Quadrant I ($360^\circ \equiv 0^\circ$).

---

# Part 2: Reflection & Shearing (`reflection_shearing.py`)

---

## Transformation 5: Reflection

Target Object: Triangle $A(20, 20)$, $B(60, 20)$, $C(40, 60)$

### 5.1 Reflection About the X-Axis ($y \to -y$)

#### 1. Homogeneous Matrix

$$R_x = \begin{bmatrix} 1 & 0 & 0 \\ 0 & -1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ |
| :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(20, -20)$ |
| **B** | $(60, 20)$ | $(60, -20)$ |
| **C** | $(40, 60)$ | $(40, -60)$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[ 1  0  0]
 [ 0 -1  0]
 [ 0  0  1]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[ 20 -20   1]
 [ 60 -20   1]
 [ 40 -60   1]]
```

#### 4. Output Figure

![5.1 Reflection about x](5.1%20Reflection%20about%20x.png)

> **Observation / Geometric Note:**  
> Reflecting across the horizontal X-axis ($y = 0$) leaves X coordinates unaltered while inverting the sign of Y ($x' = x, y' = -y$). The triangle flips upside down into the fourth quadrant, reversing its geometric vertex winding order from counterclockwise to clockwise.

---

### 5.2 Reflection About the Y-Axis ($x \to -x$)

#### 1. Homogeneous Matrix

$$R_y = \begin{bmatrix} -1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ |
| :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(-20, 20)$ |
| **B** | $(60, 20)$ | $(-60, 20)$ |
| **C** | $(40, 60)$ | $(-40, 60)$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[-1  0  0]
 [ 0  1  0]
 [ 0  0  1]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[-20  20   1]
 [-60  20   1]
 [-40  60   1]]
```

#### 4. Output Figure

![5.2 Reflection about y](5.2%20Reflection%20about%20y.png)

> **Observation / Geometric Note:**  
> Reflecting across the vertical Y-axis ($x = 0$) negates the X coordinates while preserving Y coordinates ($x' = -x, y' = y$). The object flips across the axis into the second quadrant as a mirror image.

---

### 5.3 Reflection About the Origin ($x \to -x, y \to -y$)

#### 1. Homogeneous Matrix

$$R_{\text{origin}} = \begin{bmatrix} -1 & 0 & 0 \\ 0 & -1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ |
| :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(-20, -20)$ |
| **B** | $(60, 20)$ | $(-60, -20)$ |
| **C** | $(40, 60)$ | $(-40, -60)$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[-1  0  0]
 [ 0 -1  0]
 [ 0  0  1]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[-20 -20   1]
 [-60 -20   1]
 [-40 -60   1]]
```

#### 4. Output Figure

![5.3 Reflection about origin](5.3%20Reflection%20about%20origin.png)

> **Observation / Geometric Note:**  
> Origin reflection inverts the signs of both coordinates ($x' = -x, y' = -y$). This is geometrically equivalent to a point reflection through $(0, 0)$ or a $180^\circ$ rotation about the origin, placing the triangle into the third quadrant.

---

### 5.4 Reflection About the Line $y = x$

#### 1. Homogeneous Matrix

$$R_{y=x} = \begin{bmatrix} 0 & 1 & 0 \\ 1 & 0 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ |
| :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(20, 20)$ |
| **B** | $(60, 20)$ | $(20, 60)$ |
| **C** | $(40, 60)$ | $(60, 40)$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[0 1 0]
 [1 0 0]
 [0 0 1]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[20 20  1]
 [20 60  1]
 [60 40  1]]
```

#### 4. Output Figure

![5.4 Reflection about y=x](5.4%20Reflection%20about%20y=x.png)

> **Observation / Geometric Note:**  
> Reflection across the line $y = x$ transposes coordinate values ($x' = y, y' = x$). Any point lying directly on the reflection axis $y = x$ remains invariant; here, vertex $A(20, 20)$ is invariant ($A' = A$). Edge $AB$ (initially horizontal) reflects to become vertical edge $A'B'$.

---

### 5.5 Reflection About the Line $y = -x$

#### 1. Homogeneous Matrix

$$R_{y=-x} = \begin{bmatrix} 0 & -1 & 0 \\ -1 & 0 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original Coordinates $(x, y)$ | Transformed Coordinates $(x', y')$ |
| :---: | :---: | :---: |
| **A** | $(20, 20)$ | $(-20, -20)$ |
| **B** | $(60, 20)$ | $(-20, -60)$ |
| **C** | $(40, 60)$ | $(-60, -40)$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[ 0 -1  0]
 [-1  0  0]
 [ 0  0  1]]
Original points:------
 [[20 20  1]
 [60 20  1]
 [40 60  1]]
Transformed points:------
 [[-20 -20   1]
 [-20 -60   1]
 [-60 -40   1]]
```

#### 4. Output Figure

![5.5 Reflection about y=-x](5.5%20Reflection%20about%20y=-x.png)

> **Observation / Geometric Note:**  
> Reflection across the line $y = -x$ swaps and negates both coordinates ($x' = -y, y' = -x$). The triangle reflects across the second diagonal into the third quadrant.

---

## Transformation 6: Shearing

Target Object: Square $P(10, 10)$, $Q(50, 10)$, $R(50, 50)$, $S(10, 50)$

### 6.1 X-Direction Shear with Positive Factor ($sh_x = 2.0$)

#### 1. Homogeneous Matrix

$$Sh_x(2.0) = \begin{bmatrix} 1 & sh_x & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix} = \begin{bmatrix} 1 & 2.0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original $(x, y)$ | Transformed $(x', y')$ | Computation ($x' = x + 2y, y' = y$) |
| :---: | :---: | :---: | :---: |
| **P** | $(10, 10)$ | $(30.0, 10.0)$ | $x' = 10 + 2(10) = 30,\; y' = 10$ |
| **Q** | $(50, 10)$ | $(70.0, 10.0)$ | $x' = 50 + 2(10) = 70,\; y' = 10$ |
| **R** | $(50, 50)$ | $(150.0, 50.0)$ | $x' = 50 + 2(50) = 150,\; y' = 50$ |
| **S** | $(10, 50)$ | $(110.0, 50.0)$ | $x' = 10 + 2(50) = 110,\; y' = 50$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[1. 2. 0.]
 [0. 1. 0.]
 [0. 0. 1.]]
Original points:------
 [[10 10  1]
 [50 10  1]
 [50 50  1]
 [10 50  1]]
Transformed points:------
 [[ 30.  10.   1.]
 [ 70.  10.   1.]
 [150.  50.   1.]
 [110.  50.   1.]]
```

#### 4. Output Figure

![6. Shear 2x](6.%20Shear%202x.png)

> **Observation / Geometric Note:**  
> In X-shear, points shift rightward parallel to the X-axis by an amount proportional to their vertical distance $y$. Vertices at $y = 50$ undergo a displacement of $+100$ units, whereas vertices at $y = 10$ shift by only $+20$ units. The square deforms into an elongated parallelogram with unchanged vertical height ($40$) and equal area.

---

### 6.2 X-Direction Shear with Negative Factor ($sh_x = -1.0$)

#### 1. Homogeneous Matrix

$$Sh_x(-1.0) = \begin{bmatrix} 1 & -1.0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original $(x, y)$ | Transformed $(x', y')$ | Computation ($x' = x - y, y' = y$) |
| :---: | :---: | :---: | :---: |
| **P** | $(10, 10)$ | $(0.0, 10.0)$ | $x' = 10 - 10 = 0,\; y' = 10$ |
| **Q** | $(50, 10)$ | $(40.0, 10.0)$ | $x' = 50 - 10 = 40,\; y' = 10$ |
| **R** | $(50, 50)$ | $(0.0, 50.0)$ | $x' = 50 - 50 = 0,\; y' = 50$ |
| **S** | $(10, 50)$ | $(-40.0, 50.0)$ | $x' = 10 - 50 = -40,\; y' = 50$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[ 1. -1.  0.]
 [ 0.  1.  0.]
 [ 0.  0.  1.]]
Original points:------
 [[10 10  1]
 [50 10  1]
 [50 50  1]
 [10 50  1]]
Transformed points:------
 [[  0.  10.   1.]
 [ 40.  10.   1.]
 [  0.  50.   1.]
 [-40.  50.   1.]]
```

#### 4. Output Figure

![6. Shear -1x](6.%20Shear%20-1x.png)

> **Observation / Geometric Note:**  
> A negative shear factor shifts vertices leftward ($x' = x - y$). Top edge vertices ($y = 50$) shift left by 50 units, pulling vertex $S$ into the negative X-halfplane at $x = -40$.

---

### 6.3 Y-Direction Shear with Positive Factor ($sh_y = 1.5$)

#### 1. Homogeneous Matrix

$$Sh_y(1.5) = \begin{bmatrix} 1 & 0 & 0 \\ sh_y & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix} = \begin{bmatrix} 1 & 0 & 0 \\ 1.5 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original $(x, y)$ | Transformed $(x', y')$ | Computation ($x' = x, y' = y + 1.5x$) |
| :---: | :---: | :---: | :---: |
| **P** | $(10, 10)$ | $(10.0, 25.0)$ | $x' = 10,\; y' = 10 + 1.5(10) = 25$ |
| **Q** | $(50, 10)$ | $(50.0, 85.0)$ | $x' = 50,\; y' = 10 + 1.5(50) = 85$ |
| **R** | $(50, 50)$ | $(50.0, 125.0)$ | $x' = 50,\; y' = 50 + 1.5(50) = 125$ |
| **S** | $(10, 50)$ | $(10.0, 65.0)$ | $x' = 10,\; y' = 50 + 1.5(10) = 65$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[1.  0.  0. ]
 [1.5 1.  0. ]
 [0.  0.  1. ]]
Original points:------
 [[10 10  1]
 [50 10  1]
 [50 50  1]
 [10 50  1]]
Transformed points:------
 [[ 10.  25.   1.]
 [ 50.  85.   1.]
 [ 50. 125.   1.]
 [ 10.  65.   1.]]
```

#### 4. Output Figure

![6. Shear 1.5y](6.%20Shear%201.5y.png)

> **Observation / Geometric Note:**  
> In Y-shear, X coordinates are held constant while Y coordinates shift vertically by $sh_y \cdot x$. Vertices on the right side ($x = 50$) undergo an upward displacement of $+75$ units, whereas vertices on the left ($x = 10$) shift up by $+15$ units, slanting horizontal edges upwards into vertical parallelogram lines.

---

### 6.4 Y-Direction Shear with Negative Factor ($sh_y = -0.5$)

#### 1. Homogeneous Matrix

$$Sh_y(-0.5) = \begin{bmatrix} 1 & 0 & 0 \\ -0.5 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

#### 2. Coordinate Table

| Vertex | Original $(x, y)$ | Transformed $(x', y')$ | Computation ($x' = x, y' = y - 0.5x$) |
| :---: | :---: | :---: | :---: |
| **P** | $(10, 10)$ | $(10.0, 5.0)$ | $x' = 10,\; y' = 10 - 0.5(10) = 5$ |
| **Q** | $(50, 10)$ | $(50.0, -15.0)$ | $x' = 50,\; y' = 10 - 0.5(50) = -15$ |
| **R** | $(50, 50)$ | $(50.0, 25.0)$ | $x' = 50,\; y' = 50 - 0.5(50) = 25$ |
| **S** | $(10, 50)$ | $(10.0, 45.0)$ | $x' = 10,\; y' = 50 - 0.5(10) = 45$ |

#### 3. Console Output

```text
Transformation Matrix:------
 [[ 1.   0.   0. ]
 [-0.5  1.   0. ]
 [ 0.   0.   1. ]]
Original points:------
 [[10 10  1]
 [50 10  1]
 [50 50  1]
 [10 50  1]]
Transformed points:------
 [[ 10.   5.   1.]
 [ 50. -15.   1.]
 [ 50.  25.   1.]
 [ 10.  45.   1.]]
```

#### 4. Output Figure

![6. Shear -0.5y](6.%20Shear%20-0.5y.png)

> **Observation / Geometric Note:**  
> The negative vertical shear shifts points downward proportional to their distance from the Y-axis ($y' = y - 0.5x$). Point $Q(50, 10)$ is pulled down by 25 units into negative Y coordinates ($y' = -15$), tilting the bottom edge downward across the X-axis into the fourth quadrant.

---

## 3. Summary of Compliance with Assignment Specifications

| Requirement / Objective | Specified in Assignment | Implemented & Verified |
| :--- | :--- | :---: |
| **Homogeneous Coordinates Representation** | Use $3 \times 3$ matrices derived from first principles; no black-box affine transformation libraries | **Yes** (`transformation_lib.py`) |
| **Task 1: Basic Transformations** | Translation, Scaling (uniform & differential), Rotation ($45^\circ$, and multiple angles) | **Yes** (`basic_transformation.py`) |
| **Task 2: Reflection & Shearing** | 5 Reflections (x, y, origin, $y=x$, $y=-x$) & 4 Shears (pos/neg $sh_x$, pos/neg $sh_y$) | **Yes** (`reflection_shearing.py`) |
| **Strict Aspect Ratio & Visuals** | 1:1 aspect ratio (`plt.axis("equal")`), axes lines at $x=0, y=0$, grid, dashed/solid lines | **Yes** (All figures saved with 1:1 scale) |
| **Documentation Requirements** | Theoretical matrix, coordinate table, console output, numbered figure, geometric note | **Yes** (Complete lab report provided) |
