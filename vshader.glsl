attribute vec4 vPosition;
attribute vec3 vNormal;

//Per fragment shading 
varying vec3 fN;
varying vec3 fE;
varying vec3 fL;

uniform mat4 camera_mv;
uniform mat4 object_mv;
uniform mat4 projection;
uniform vec4 LightPosition;

void main()
{
    mat4 model_view = camera_mv * object_mv;

    vec4 vN = vec4(vNormal.x, vNormal.y, vNormal.z, 0.0);

    //The vector to the viewer and vertex normal
    fE = (model_view * vPosition).xyz;
    fN = (model_view * vN).xyz;

    //Fragment light vector
    fL = (camera_mv*LightPosition).xyz;

    gl_Position = projection * model_view * vPosition;
    //gl_Position = object_mv * vPosition;
}
