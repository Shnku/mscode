import numpy as np

from transformation_lib import *

# Objects with homogeneous coordinate

triangle = np.array([(20, 20, 1), (60, 20, 1), (40, 60, 1)])
square = np.array([(10, 10, 1), (50, 10, 1), (50, 50, 1), (10, 50, 1)])
# letter_F = np.array([
#     (0, 0, 1), (0, 4, 1), (3, 4, 1), (3, 3, 1), (1, 3, 1), (1, 2.5, 1), (2, 2.5, 1), (2, 1.75, 1), (1, 1.75, 1), (1, 0, 1)
# ])


##########################################
# Apply Transformations..................

# 5. Reflection
ref_x = apply_transformation(triangle, get_reflection_matrix("x"))
ref_y = apply_transformation(triangle, get_reflection_matrix("y"))
ref_o = apply_transformation(triangle, get_reflection_matrix("origin"))
ref_yx = apply_transformation(triangle, get_reflection_matrix("y=x"))
ref_ynx = apply_transformation(triangle, get_reflection_matrix("y=-x"))

visualize_transformation(triangle, ref_x, save_img=True, title="5.1 Reflection about x")
visualize_transformation(triangle, ref_y, save_img=True, title="5.2 Reflection about y")
visualize_transformation(
    triangle, ref_o, save_img=True, title="5.3 Reflection about origin"
)
visualize_transformation(
    triangle, ref_yx, save_img=True, title="5.4 Reflection about y=x"
)
visualize_transformation(
    triangle, ref_ynx, save_img=True, title="5.5 Reflection about y=-x"
)

# 6. Shearing (using the square)
shx_pos = apply_transformation(square, get_shearing_matrix(shx=2.0))
shx_neg = apply_transformation(square, get_shearing_matrix(shx=-1.0))
shy_pos = apply_transformation(square, get_shearing_matrix(shy=1.5))
shy_neg = apply_transformation(square, get_shearing_matrix(shy=-0.5))

visualize_transformation(square, shx_pos, save_img=True, title="6. Shear 2x")
visualize_transformation(square, shx_neg, save_img=True, title="6. Shear -1x")
visualize_transformation(square, shy_pos, save_img=True, title="6. Shear 1.5y")
visualize_transformation(square, shy_neg, save_img=True, title="6. Shear -0.5y")
