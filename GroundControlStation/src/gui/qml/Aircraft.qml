import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0


Entity {
    property vector3d position: Qt.vector3d(0, 0, 0)

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
        property real userAngle: 50
        matrix: {
            var m = Qt.matrix4x4();
            m.rotate(userAngle, Qt.vector3d(0, 1, 0))
            m.rotate(userAngle, Qt.vector3d(1, 0, 0))
            m.translate(position);
            return m;
        }
    }

    components: [ plane, material, transform ]
}
