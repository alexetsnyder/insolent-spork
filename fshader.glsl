varying vec3 fE;
varying vec3 fN;
varying vec3 fL;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform float Shininess;

uniform vec4 LightPosition;


void main()
{
	//Normalize the input 
	vec3 E = normalize(fE);
	vec3 N = normalize(fN);
	vec3 L = normalize(fL);

	//If light is nearby calculate the direction per fragment
	if (LightPosition.w != 0.0)
	{
		L = normalize(L - E);
	}

	vec3 R = reflect(L, N);

	float kd = max(dot(L, N), 0.0);
	float ks = pow(max(dot(R, E), 0.0), Shininess);

	vec4 ambient = AmbientProduct;
	vec4 diffuse = kd*DiffuseProduct;
	vec4 specular = ks*SpecularProduct;

	//Discard specular light if the light is behind the vertex
	if (dot(fL, fN) < 0.0)
	{
		specular = vec4(0.0, 0.0, 0.0, 0.0);
	}

	gl_FragColor = ambient + diffuse + specular;
	gl_FragColor.a = 1.0;
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
