varying vec3 var_v_color;
varying vec3 var_v_normal;
varying vec2 var_v_uv;
uniform sampler2D texDiffuse;

void main(void)
{
	float variance = max(0.0, dot(vec3(0, 0, 1), var_v_normal));
	vec4 finalColor = texture2D(texDiffuse, var_v_uv);
	gl_FragColor = vec4(finalColor.r + var_v_color.r * variance, finalColor.g + var_v_color.g * variance,
		finalColor.b + var_v_color.b * variance, finalColor.a);
}