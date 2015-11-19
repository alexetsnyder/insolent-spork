attribute vec4 vPosition;
attribute vec3 vNormal;

varying vec4 fColor;

/*uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 camera_mv;*/
uniform mat4 object_mv;
/*uniform mat4 projection;
uniform vec4 LightPosition;
uniform float Shininess;*/

void main()
{
    /* mat4 model_view = camera_mv * object_mv;


    // Transform vertex  position into eye coordinates
    vec3 pos = (model_view * vPosition).xyz;
	
    vec3 fL = normalize(camera_mv*LightPosition).xyz;

    vec3 L;
    if (LightPosition.w == 1.0) {
      L = normalize(fL - pos);
    } 
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);

    // Transform vertex normal into eye coordinates
    vec3 N = normalize(model_view*vec4(vNormal, 0.0)).xyz;

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max(dot(L, N), 0.0);
    vec4  diffuse = Kd*DiffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks * SpecularProduct;
    
    if(dot(L, N) < 0.0) {
	specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    gl_Position = projection*model_view*vPosition;

    fColor = ambient + diffuse + specular;
    fColor.a = 1.0;*/

    gl_Position = object_mv * vPosition;
    fColor = vec4(1.0, 0.0, 0.0, 1.0);
}
