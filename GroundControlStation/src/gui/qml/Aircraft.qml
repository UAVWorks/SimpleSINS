import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0


Entity {
    property vector3d attitude: Qt.vector3d(0, 0, 0)

    PhongMaterial {
        id: material

        ambient: "blue"
        shininess: 0.5
    }

    CuboidMesh {
        id: plane
    }

    Transform {
        id: transform

        rotationX: -attitude.y + 90
        rotationY: attitude.x + 90
        rotationZ: -attitude.z
        scale3D: Qt.vector3d(4, 2, 1)
    }

    components: [ plane, material, transform ]
}
