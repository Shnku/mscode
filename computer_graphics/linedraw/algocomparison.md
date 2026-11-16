Test Case 1:

Starting point: (50, 50)

Ending point: (200, 130)

  -----------------------------------------------------------------------
  PARAMETER               DDA                     BRESENHAM
  ----------------------- ----------------------- -----------------------
  Number of points        151                     151

  Execution time          0.00000                 0.0000
  -----------------------------------------------------------------------

Point sequence comparison -

Bresenham produces a sequence such as:

(50,50), (51,51), (52,51), (53,52), (54,52), (55,53), ....... ,
(196,128), (197,128), (198,129), (199,129), (200,130).

The DDA output is:

(50,50), (51,50), (52,50), (53,50), (54,50), (55,50),\... (197,50),
(198,50), (199,50), (50,200)

DDA keeps the y-coordinate at 50 throughout the line instead of
gradually increasing it to 130.

Test case 2

Starting point: (50, 50)

Ending point: (130, 200)

  -----------------------------------------------------------------------
  PARAMETER               DDA                     BRESENHAM
  ----------------------- ----------------------- -----------------------
  Number of points        151                     151

  Execution time          0.00000                 0.0000
  -----------------------------------------------------------------------

Point sequence comparison --

Bresenham produces a sequence such as -

(50,50), (51,51), (52,52), (52,53), (53,54), (53,55), (54,56) ....
(130,198), (130,199), (131,200)

The DDA output is:

(50,50), (50,51), (50,52), (50,53), \... (50,200)

Here, the x-coordinate remains fixed at 50 while only y increases.

Test case 3 --

Starting point: (50, 100)

Ending point: (250, 100)

  -----------------------------------------------------------------------
  PARAMETER               DDA                     BRESENHAM
  ----------------------- ----------------------- -----------------------
  Number of points        201                     200

  Execution time          0.00000                 0.0000
  -----------------------------------------------------------------------

Point Sequence Comparison

DDA produces these points:

(50,100), (51,100), (52,100), \... (249,100), (250,100)

Bresenham produces these points:

(50,100), (51,100), (52,100), \... (248,100), (249,100)

Points generated are almost identical.
