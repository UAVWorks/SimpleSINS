import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import sim.AerialVehicle 1.0

import QtQuick 2.0

Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, 20.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )

        aspectRatio: width / height
    }

    FirstPersonCameraController { camera: camera }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: Qt.rgba(0.5, 0.7, 1, 1)
            }
        },
        InputSettings { }
    ]

    Aircraft {
        id: av

        Component.onCompleted: {
            console.log("Aircraft created");
        }
    }
}
