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

    //The vector to the viewer and vertex normal
    fE = (model_view * vPosition).xyz;
    fN = (model_view * LightPosition).xyz;

    //Fragment light vector
	fL = normalize(camera_mv*LightPosition).xyz;

    gl_Position = object_mv * vPosition;
}
