# Assignment No. 3

**M.Sc. (Computer Science) - Semester I Computer Graphics Laboratory**  
**Basic Two-Dimensional Transformations (Translation, Scaling, Rotation, Reflection and Shearing)**

-----

## Aim

To represent the basic two-dimensional geometric transformations - translation, scaling, rotation, reflection and shearing as $3\times3$ matrices in homogeneous coordinates, to implement them in Python, and to display the original and the transformed object using matplotlib.

-----

## Objectives

* Write each basic transformation as a $3\times3$ homogeneous matrix, exactly as derived in the theory class.
* Understand why a $2\times2$ matrix cannot represent a translation, and how homogeneous coordinates solve the problem.
* Apply a transformation to an object by a single matrix multiplication.
* Plot the original and the transformed object on the same axes using matplotlib.
* Observe the difference between uniform and differential scaling, and between positive and negative shear.

-----

## Software Required

Python 3.x with the NumPy and Matplotlib libraries. Any editor or IDE may be used - IDLE, VS Code, PyCharm, Spyder, Jupyter Notebook, or an online environment such as Google Colab.

> [!IMPORTANT]  
> You must construct every transformation matrix yourself, exactly as derived in the theory class. Ready-made transformation facilities `matplotlib.transforms`, the `Affine2D` class, `scipy.ndimage`, OpenCV `warpAffine`, or any similar library routine must **NOT** be used to perform the transformation. NumPy is to be used only for storing arrays and for multiplying matrices. Matplotlib is to be used only for plotting points you have already computed. Using a library transformation routine will lead to loss of marks even if the picture is correct.

-----

## Tasks

### Task 1: Translation, Scaling and Rotation (`basic_transformations.py`)

Write a Python program that applies translation, scaling and rotation to the given test object. For each transformation the program must:

* Print the $3\times3$ homogeneous transformation matrices;
* Print the original and the transformed vertex coordinates;
* Plot the original object (dashed) and the transformed object (solid) on the same axes, and save the figure as a PNG file.

The program must also produce one figure comparing uniform scaling with differential scaling, and one figure showing the object rotated through several different angles.

### Task 2: Reflection and Shearing (`reflection_shear.py`)

Write a second program, with the same structure as Task 1, that reflects the test object about the x-axis, the y-axis, the origin, the line $y=x$ and the line $y=-x$, and that shears the square in the x-direction and in the y-direction using both a positive and a negative shear factor.

Print the matrix and the transformed coordinates in every case, and save a figure for each result.

### Task 3: Output Document

Prepare a Word document containing, for every transformation: the transformation matrix, the table of original and transformed coordinates, the console output, and the corresponding figure. Add a short note in your own words below each figure describing what the transformation has done to the object.

-----

## Sample Test Data

### A. Test Objects

| Object       | Used for                         | Vertices                               |
| :----------- | :------------------------------- | :------------------------------------- |
| **Triangle** | Task 1, and reflection in Task 2 | (20, 20), (60, 20), (40, 60)           |
| **Square**   | Shearing in Task 2               | (10, 10), (50, 10), (50, 50), (10, 50) |

*You may add one extra object or one extra parameter set of your own choice in addition to these.*

### B. Transformation Parameters

| No.   | Transformation                  | Parameters                                                                             |
| :---- | :------------------------------ | :------------------------------------------------------------------------------------- |
| **1** | Translation                     | $t_x=30$, $t_y=25$                                                                   |
| **2** | Scaling about the origin        | $s_x=2.0$, $s_y=1.5$                                                                 |
| **3** | Uniform vs differential scaling | (2.0, 2.0) and (2.0, 0.5)                                                              |
| **4** | Rotation about the origin       | $45^\circ$; then $30^\circ$, $60^\circ$, $90^\circ$ and $180^\circ$ on one figure |
| **5** | Reflection                      | About the x-axis, the y-axis, the origin, $y = x$ and $y = -x$                         |
| **6** | Shearing (use the square)       | $sh_x=2.0$ and $-1.0$; $sh_y=1.5$ and $-0.5$                                         |

-----

## Instructions

1. This is a group assignment (Group of 3). Work should be divided among group members, but every member must be able to explain all the matrices and both programs at the time of evaluation.
2. Derive and write the matrices independently from the steps taught in the theory class; do not copy from the internet or AI tools.
3. Keep all the transformation matrices together in one Python file and import it into both programs, so that both tasks use exactly the same definitions.
4. Both programs must use the same test objects and the same parameters given above.
5. Every figure must use a 1:1 aspect ratio. If the aspect ratio is not equal, a rotation will appear to distort the object and the figure is wrong.
6. Show the coordinate axes and a grid on every figure, and label the original and transformed objects in a legend.
7. Add comments in the code explaining each matrix and each major step.
8. If the figures are saved into a folder, create that folder before running the program, or the program will stop with a file-not-found error.
9. Take clear screenshots (or copy-paste) of the console output for each task.

-----

## Suggested Division of Work (Group of 3)

* **Member A:** The common file containing all the transformation matrices.
* **Member B:** `basic_transformations.py` - translation, scaling and rotation (Task 1).
* **Member C:** `reflection_shear.py` - reflection and shearing (Task 2).
* **All three members together:** The output document (Task 3).

-----

## Submission

Submit a single **ZIP file** (named as per your group number) containing:

* The Python file containing all the transformation matrices, well commented.
* `basic_transformations.py` - translation, scaling and rotation, with plotting.
* `reflection_shear.py` - reflection and shearing, with plotting.
* A `figures` folder containing every PNG file generated by the programs.
* One Word (`.docx`) file containing the matrices, the coordinate tables, the console output and all the figures.
