import numpy as np

from transformation_lib import *

# Objects with homogeneous coordinate
triangle = np.array([(20, 20, 1), (60, 20, 1), (40, 60, 1)])
square = np.array([(10, 10, 1), (50, 10, 1), (50, 50, 1), (10, 50, 1)])
# letter_F = np.array([
#     (0, 0, 1), (0, 4, 1), (3, 4, 1), (3, 3, 1), (1, 3, 1), (1, 2.5, 1), (2, 2.5, 1), (2, 1.75, 1), (1, 1.75, 1), (1, 0, 1)
# ])


###########################################
# Apply Transformations..................

# 1. Translation
t_triangle = apply_transformation(triangle, get_translation_matrix(30, 25))
visualize_transformation(triangle, t_triangle, save_img=True, title="1. translation")

# 2. Scaling about the origin
s_triangle = apply_transformation(triangle, get_scaling_matrix(2.0, 1.5))
visualize_transformation(triangle, s_triangle, save_img=True, title="2. scaling")

# 3. Uniform vs differential scaling
# uniform x==y equal scale...
u_triangle = apply_transformation(triangle, get_scaling_matrix(2.0, 2.0))
# differential x!=y scale....
d_triangle = apply_transformation(triangle, get_scaling_matrix(2.0, 0.5))
visualize_transformation(
    triangle, u_triangle, save_img=True, title="3.1 uniform scaling"
)
visualize_transformation(
    triangle, d_triangle, save_img=True, title="3.2 differential scaling"
)

# 4. Rotation about the origin
# 45 degrees
r45_triangle = apply_transformation(triangle, get_rotation_matrix(45))
visualize_transformation(
    triangle, r45_triangle, save_img=True, title="4.1 rotate 45 degree"
)

# Multiple rotations on one figure (sequential)
r_seq1 = apply_transformation(triangle, get_rotation_matrix(30))
r_seq2 = apply_transformation(r_seq1, get_rotation_matrix(60))
r_seq3 = apply_transformation(r_seq2, get_rotation_matrix(90))
r_seq4 = apply_transformation(r_seq3, get_rotation_matrix(180))
visualize_multiple_transformation(
    triangle,
    [r_seq1, r_seq2, r_seq3, r_seq4],
    labels=["30 degree", "60 degree", "90 degree", "180 degree"],
    title="4.2 Multiple rotations 30-60-90-180",
    save_img=True,
)
