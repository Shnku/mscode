# **Assignment : Sutherland–Hodgman Polygon Clipping Algorithm**

## **Aim**

To implement the Sutherland–Hodgman polygon clipping algorithm in Python, and to clip a given set of polygons  against a given rectangular window.

### **Input Data**

**Your Own Input Polygon**

Let a \= the second-last digit of your roll number, and b \= the last digit.

 Polygon Q3 : (140 \+ a, 20 \+ b) (230 \+ a, 20 \+ b)

 (230 \+ a, 110 \+ b) (140 \+ a, 110 \+ b)

For example, a roll number ending in 47 gives a \= 4 and b \= 7, so Q3 is the square (144, 27), (234, 27), (234, 117),  (144, 117). Write your own a, b and Q3 at the top of your answer sheet before you begin.

Clipping window: lower-left corner (50, 50), upper-right corner (200, 150\) — the same window as in the previous  assignment.

Clip each of the following three polygons against this window. The vertices are listed in order around the  polygon.

| Polygon | Vertices, in order |
| ----- | ----- |
| Q1 | (80, 70\) (150, 70\) (115, 130\) |
| Q2 | (20, 20\) (250, 20\) (135, 200\) |
| Q3 | (140 \+ a, 20 \+ b) (230 \+ a, 20 \+ b) (230 \+ a, 110 \+ b) (140 \+ a, 110 \+ b) |

*Work out for yourself what happens to each polygon. Do not assume — let the four clipping stages decide.*

### **Tasks**

Write ONE Python program (polygon\_clip\_\<your roll no\>.py) that does the following.

**Task 1 — Clip against one boundary**

Write a function that takes a list of vertices and one boundary of the window, and returns the new list of vertices.  For each edge of the polygon, from the previous vertex to the current vertex, apply the four cases taught in the  theory class.

**Task 2 — Clip against the whole window**

Call the function of Task 1 four times, once for each boundary, in the order left, right, bottom, top. The list  returned by one stage becomes the input to the next stage.

**Task 3 — Print the result**

For each of the three polygons, print the input vertex list, the vertex list after each of the four stages, and the  final clipped vertex list. Print the number of vertices alongside each list.  

**Task 4 — Draw the figure**

For each polygon, draw the clipping window as a rectangle, the original polygon as a dashed outline, and the  clipped polygon as a solid filled shape. Use a 1 : 1 aspect ratio and save the figure as a PNG file.

### **Expected Output**

Your figures should look like these. The dashed outline is the input polygon and the filled shape is what survives  the clipping.

![][image1]*Q3 is drawn for a roll number ending in 47\. Your Q3 will be in a slightly different position.*

### **Questions to Answer**

Answer in your own words, two or three sentences each.

1\. Which polygon came out of the algorithm unchanged? What was true of all of its vertices that made this  happen?

2\. Q2 goes in with 3 vertices and comes out with more. Write down the number of vertices after each of the  four stages, and explain where the extra vertices come from.

3\. For your own polygon Q3, which boundaries of the window actually removed anything, and what are the  final clipped vertices?

4\. For one edge of a polygon, going from the previous vertex to the current vertex, there are four possible  cases. List all four, and state what each case adds to the output list.

### **Instructions**

1\. Write the clipping function yourself, from the steps taught in the theory class. Do not use any ready-made  polygon clipping routine such as shapely, Path.clip\_to\_bbox or OpenCV.

2\. Clip against the four boundaries one at a time, in the given order. Do not try to test a vertex against all four  boundaries at once — that is not this algorithm, and it gives the wrong answer at the corners.

3\. All three polygons given here are convex, so each one produces a single clipped polygon.

4\. Print the vertex coordinates to three decimal places. Some of them are not whole numbers.

5\. Matplotlib is to be used only to draw the window and the vertex lists you have already computed. Use a 1  : 1 aspect ratio.
