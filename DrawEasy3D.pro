#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T11:00:48
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrawEasy3D
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#   CONFIG += precompile_header
#   PRECOMPILED_HEADER = common/SFLDefine.h
INCLUDEPATH += $$PWD/library/glm
INCLUDEPATH += $$PWD/library/

macx {
    DISTFILES += \
        library/zlib/libzlibstatic.a \
        library/assimp/libassimp.3.3.1.dylib\
        library/sfl/libFaceBeautify.a

    LIBS += -L$$PWD/library/zlib/ -lzlibstatic
    LIBS += -L$$PWD/library/assimp/ -lassimp.3.3.1
    LIBS += -L$$PWD/library/sfl/ -lFaceBeautify
}

SOURCES += \
        main.cpp \
        MainWindow.cpp\
    views/SFLViewRender.cpp\
    views/SFLViewControl.cpp \
    views/SFLToolBar.cpp \
    views/SFLViewLight.cpp \
    views/SFLViewNoLight.cpp \
    common/SFLModelAbstract.cpp \
    common/SFLVec3Editor.cpp \
    common/SFLSelectorLayout.cpp \
    common/SFLVec1Editor.cpp \
    views/SFLViewMapping.cpp \
    views/SFLViewLoadModel.cpp \
    views/SFLViewPostprocessing.cpp \
    math/SGLMath.cpp

HEADERS += \
        MainWindow.h \
    views/SFLViewRender.h \
    views/SFLViewControl.h \
    views/SFLToolBar.h \
    views/SFLViewLight.h \
    common/SFLModelAbstract.h \
    models/SFLModelLight.h \
    views/SFLViewNoLight.h \
    common/SFLDefine.h \
    models/SFLModelNoLight.h \
    common/SFLToolBtn.h \
    common/SFLVec3Editor.h \
    common/SFLSelectorLayout.h \
    common/SFLViewAbstract.h \
    common/SFLVec1Editor.h \
    renders/SFLShaderProgram.h \
    renders/SFLCameraVirtual.h \
    renders/SFLTexture.h \
    renders/SFLVertexArray.h \
    models/SFLModelMapping.h \
    views/SFLViewMapping.h \
    models/SFLModelLoadModel.h \
    views/SFLViewLoadModel.h \
    models/SFLModelPostprocessing.h \
    views/SFLViewPostprocessing.h \
    renders/SFLMesh.h \
    renders/SFLModel.h \
    math/vec3.h \
    math/vec4.h \
    math/SGLMath.h \
    math/mat3x3.h \
    math/mat4x4.h \
    library/sfl/FaceBeautify.h

HEADERS += \
    library/glm/detail/_features.hpp \
    library/glm/detail/_fixes.hpp \
    library/glm/detail/_noise.hpp \
    library/glm/detail/_swizzle.hpp \
    library/glm/detail/_swizzle_func.hpp \
    library/glm/detail/_vectorize.hpp \
    library/glm/detail/compute_vector_relational.hpp \
    library/glm/detail/qualifier.hpp \
    library/glm/detail/setup.hpp \
    library/glm/detail/type_float.hpp \
    library/glm/detail/type_gentype.hpp \
    library/glm/detail/type_half.hpp \
    library/glm/detail/type_int.hpp \
    library/glm/detail/type_mat.hpp \
    library/glm/detail/type_mat2x2.hpp \
    library/glm/detail/type_mat2x3.hpp \
    library/glm/detail/type_mat2x4.hpp \
    library/glm/detail/type_mat3x2.hpp \
    library/glm/detail/type_mat3x3.hpp \
    library/glm/detail/type_mat3x4.hpp \
    library/glm/detail/type_mat4x2.hpp \
    library/glm/detail/type_mat4x3.hpp \
    library/glm/detail/type_mat4x4.hpp \
    library/glm/detail/type_vec.hpp \
    library/glm/detail/type_vec1.hpp \
    library/glm/detail/type_vec2.hpp \
    library/glm/detail/type_vec3.hpp \
    library/glm/detail/type_vec4.hpp \
    library/glm/ext/vec1.hpp \
    library/glm/ext/vector_relational.hpp \
    library/glm/gtc/bitfield.hpp \
    library/glm/gtc/color_space.hpp \
    library/glm/gtc/constants.hpp \
    library/glm/gtc/epsilon.hpp \
    library/glm/gtc/integer.hpp \
    library/glm/gtc/matrix_access.hpp \
    library/glm/gtc/matrix_integer.hpp \
    library/glm/gtc/matrix_inverse.hpp \
    library/glm/gtc/matrix_transform.hpp \
    library/glm/gtc/noise.hpp \
    library/glm/gtc/packing.hpp \
    library/glm/gtc/quaternion.hpp \
    library/glm/gtc/random.hpp \
    library/glm/gtc/reciprocal.hpp \
    library/glm/gtc/round.hpp \
    library/glm/gtc/type_aligned.hpp \
    library/glm/gtc/type_precision.hpp \
    library/glm/gtc/type_ptr.hpp \
    library/glm/gtc/ulp.hpp \
    library/glm/gtc/vec1.hpp \
    library/glm/gtx/associated_min_max.hpp \
    library/glm/gtx/bit.hpp \
    library/glm/gtx/closest_point.hpp \
    library/glm/gtx/color_encoding.hpp \
    library/glm/gtx/color_space.hpp \
    library/glm/gtx/color_space_YCoCg.hpp \
    library/glm/gtx/common.hpp \
    library/glm/gtx/compatibility.hpp \
    library/glm/gtx/component_wise.hpp \
    library/glm/gtx/dual_quaternion.hpp \
    library/glm/gtx/easing.hpp \
    library/glm/gtx/euler_angles.hpp \
    library/glm/gtx/extend.hpp \
    library/glm/gtx/extended_min_max.hpp \
    library/glm/gtx/exterior_product.hpp \
    library/glm/gtx/fast_exponential.hpp \
    library/glm/gtx/fast_square_root.hpp \
    library/glm/gtx/fast_trigonometry.hpp \
    library/glm/gtx/functions.hpp \
    library/glm/gtx/gradient_paint.hpp \
    library/glm/gtx/handed_coordinate_space.hpp \
    library/glm/gtx/hash.hpp \
    library/glm/gtx/integer.hpp \
    library/glm/gtx/intersect.hpp \
    library/glm/gtx/io.hpp \
    library/glm/gtx/log_base.hpp \
    library/glm/gtx/matrix_cross_product.hpp \
    library/glm/gtx/matrix_decompose.hpp \
    library/glm/gtx/matrix_factorisation.hpp \
    library/glm/gtx/matrix_interpolation.hpp \
    library/glm/gtx/matrix_major_storage.hpp \
    library/glm/gtx/matrix_operation.hpp \
    library/glm/gtx/matrix_query.hpp \
    library/glm/gtx/matrix_transform_2d.hpp \
    library/glm/gtx/mixed_product.hpp \
    library/glm/gtx/norm.hpp \
    library/glm/gtx/normal.hpp \
    library/glm/gtx/normalize_dot.hpp \
    library/glm/gtx/number_precision.hpp \
    library/glm/gtx/optimum_pow.hpp \
    library/glm/gtx/orthonormalize.hpp \
    library/glm/gtx/perpendicular.hpp \
    library/glm/gtx/polar_coordinates.hpp \
    library/glm/gtx/projection.hpp \
    library/glm/gtx/quaternion.hpp \
    library/glm/gtx/range.hpp \
    library/glm/gtx/raw_data.hpp \
    library/glm/gtx/rotate_normalized_axis.hpp \
    library/glm/gtx/rotate_vector.hpp \
    library/glm/gtx/scalar_multiplication.hpp \
    library/glm/gtx/scalar_relational.hpp \
    library/glm/gtx/spline.hpp \
    library/glm/gtx/std_based_type.hpp \
    library/glm/gtx/string_cast.hpp \
    library/glm/gtx/texture.hpp \
    library/glm/gtx/transform.hpp \
    library/glm/gtx/transform2.hpp \
    library/glm/gtx/type_aligned.hpp \
    library/glm/gtx/type_trait.hpp \
    library/glm/gtx/vec_swizzle.hpp \
    library/glm/gtx/vector_angle.hpp \
    library/glm/gtx/vector_query.hpp \
    library/glm/gtx/wrap.hpp \
    library/glm/simd/common.h \
    library/glm/simd/exponential.h \
    library/glm/simd/geometric.h \
    library/glm/simd/integer.h \
    library/glm/simd/matrix.h \
    library/glm/simd/packing.h \
    library/glm/simd/platform.h \
    library/glm/simd/trigonometric.h \
    library/glm/simd/vector_relational.h \
    library/glm/common.hpp \
    library/glm/exponential.hpp \
    library/glm/ext.hpp \
    library/glm/fwd.hpp \
    library/glm/geometric.hpp \
    library/glm/glm.hpp \
    library/glm/integer.hpp \
    library/glm/mat2x2.hpp \
    library/glm/mat2x3.hpp \
    library/glm/mat2x4.hpp \
    library/glm/mat3x2.hpp \
    library/glm/mat3x3.hpp \
    library/glm/mat3x4.hpp \
    library/glm/mat4x2.hpp \
    library/glm/mat4x3.hpp \
    library/glm/mat4x4.hpp \
    library/glm/matrix.hpp \
    library/glm/packing.hpp \
    library/glm/trigonometric.hpp \
    library/glm/vec2.hpp \
    library/glm/vec3.hpp \
    library/glm/vec4.hpp \
    library/glm/vector_relational.hpp \
    library/assimp/*.hpp \
    library/assimp/*.inl \
    library/assimp/*.h \
    library/assimp/Compiler/*.h

RESOURCES += \
    assets/assetInfo.qrc \
    shaders/shaders.qrc
