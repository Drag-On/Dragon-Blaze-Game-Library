varying vec3 var_v_color;
varying vec3 var_v_normal;
varying vec2 var_v_uv;
uniform sampler2D texDiffuse;
uniform bool texDiffuseFlag;


void main(void)
{
	vec4 texColor = texture2D(texDiffuse, var_v_uv);
	if(!texDiffuseFlag)
		texColor = vec4(0, 0, 0, 0);
		
	vec4 finalColor = vec4(texColor + vec4(var_v_color * (1 - texColor.a), 1.0));
	
	// calculate diffuse
	float variance = max(0.0, dot(vec3(0, 0, 1), var_v_normal));
	
	gl_FragColor = vec4(finalColor.r * variance, finalColor.g * variance,
		finalColor.b * variance, finalColor.a);
}