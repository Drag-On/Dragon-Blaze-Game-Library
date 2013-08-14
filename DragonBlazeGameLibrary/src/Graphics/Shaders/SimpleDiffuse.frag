varying vec3 var_v_color;
varying vec3 var_v_normal;

void main(void)
{
	float variance = max(0.0, dot(vec3(0, 0, 1), var_v_normal));
	gl_FragColor = vec4(var_v_color.r * variance, var_v_color.g * variance, var_v_color.b * variance, 1.0);
}